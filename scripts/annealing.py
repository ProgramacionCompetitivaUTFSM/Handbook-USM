#!/usr/bin/env python3
"""
Simulated Annealing optimizer for tracker.yaml ordering.
Minimizes the number of pages in the compiled PDF.
Multi-threaded evaluation of neighbors.
"""

import yaml
import subprocess
import random
import math
import copy
import sys
import os
import tempfile
import shutil
from pathlib import Path
from concurrent.futures import ProcessPoolExecutor, as_completed
from multiprocessing import cpu_count

# Configuration
INITIAL_TEMP = 100.0
COOLING_RATE = 0.92
MIN_TEMP = 0.1
PARALLEL_NEIGHBORS = cpu_count()  # Evaluate this many neighbors in parallel


def load_tracker(path: str) -> dict:
    with open(path, 'r') as f:
        return yaml.safe_load(f)


def save_tracker(data: dict, path: str):
    with open(path, 'w') as f:
        yaml.dump(data, f, default_flow_style=False, allow_unicode=True, sort_keys=False)


def compile_and_count(work_dir: str) -> int:
    """Compile PDF and return page count"""
    try:
        result = subprocess.run(
            ['typst', 'compile', 'main.typ'],
            cwd=work_dir,
            capture_output=True,
            timeout=60
        )
        if result.returncode != 0:
            return 999

        pdf_path = os.path.join(work_dir, 'main.pdf')

        # Try pdfinfo
        try:
            result = subprocess.run(['pdfinfo', pdf_path], capture_output=True, text=True, timeout=10)
            for line in result.stdout.split('\n'):
                if line.startswith('Pages:'):
                    return int(line.split(':')[1].strip())
        except:
            pass

        # Try qpdf
        try:
            result = subprocess.run(['qpdf', '--show-npages', pdf_path], capture_output=True, text=True, timeout=10)
            return int(result.stdout.strip())
        except:
            pass

        return 999
    except:
        return 999


def evaluate_neighbor(args) -> tuple:
    """Evaluate a single neighbor in its own temp directory"""
    base_dir, tracker_data, move_desc, idx = args

    # Create temp directory INSIDE base_dir (typst sandboxing blocks /tmp)
    tmp_dir = os.path.join(base_dir, f'.tmp_eval_{idx}_{os.getpid()}')
    try:
        os.makedirs(tmp_dir, exist_ok=True)

        # Copy necessary files
        shutil.copy(os.path.join(base_dir, 'main.typ'), tmp_dir)
        shutil.copy(os.path.join(base_dir, 'content.typ'), tmp_dir)
        for subdir in ['lib', 'content', 'img']:
            src = os.path.join(base_dir, subdir)
            dst = os.path.join(tmp_dir, subdir)
            if os.path.exists(dst):
                shutil.rmtree(dst)
            if os.path.exists(src):
                shutil.copytree(src, dst)

        # Save the tracker variant
        save_tracker(tracker_data, os.path.join(tmp_dir, 'tracker.yaml'))

        # Compile and count
        pages = compile_and_count(tmp_dir)
    finally:
        # Cleanup
        if os.path.exists(tmp_dir):
            shutil.rmtree(tmp_dir)

    return idx, pages, move_desc, tracker_data


def reverse_categories(tracker: dict, i: int, j: int) -> dict:
    new_tracker = copy.deepcopy(tracker)
    content = new_tracker['content']
    content[i:j+1] = content[i:j+1][::-1]
    return new_tracker


def reverse_subcategories(tracker: dict, cat_idx: int, i: int, j: int) -> dict:
    new_tracker = copy.deepcopy(tracker)
    category = new_tracker['content'][cat_idx]
    for cat_name, items in category.items():
        items[i:j+1] = items[i:j+1][::-1]
        break
    return new_tracker


def insert_category(tracker: dict, from_idx: int, to_idx: int) -> dict:
    """Move category from from_idx to to_idx"""
    new_tracker = copy.deepcopy(tracker)
    content = new_tracker['content']
    item = content.pop(from_idx)
    content.insert(to_idx, item)
    return new_tracker


def insert_subcategory(tracker: dict, cat_idx: int, from_idx: int, to_idx: int) -> dict:
    """Move subcategory within a category"""
    new_tracker = copy.deepcopy(tracker)
    category = new_tracker['content'][cat_idx]
    for cat_name, items in category.items():
        item = items.pop(from_idx)
        items.insert(to_idx, item)
        break
    return new_tracker


def generate_neighbors(tracker: dict, n: int) -> list:
    """Generate n random neighbors with different move types"""
    neighbors = []
    content = tracker['content']
    num_categories = len(content)

    for _ in range(n):
        move_type = random.choice(['reverse_cat', 'reverse_sub', 'insert_cat', 'insert_sub'])

        if move_type == 'reverse_cat' and num_categories > 1:
            i = random.randint(0, num_categories - 2)
            j = random.randint(i + 1, num_categories - 1)
            neighbors.append((reverse_categories(tracker, i, j), f"rev_cat[{i}:{j}]"))

        elif move_type == 'insert_cat' and num_categories > 1:
            from_idx = random.randint(0, num_categories - 1)
            to_idx = random.randint(0, num_categories - 1)
            if from_idx != to_idx:
                neighbors.append((insert_category(tracker, from_idx, to_idx), f"ins_cat {from_idx}->{to_idx}"))
            else:
                neighbors.append((copy.deepcopy(tracker), "noop"))

        elif move_type in ['reverse_sub', 'insert_sub']:
            # Find valid category
            valid_cats = []
            for idx, cat in enumerate(content):
                for cat_name, items in cat.items():
                    if len(items) >= 2:
                        valid_cats.append((idx, cat_name, len(items)))
                    break

            if valid_cats:
                cat_idx, cat_name, num_items = random.choice(valid_cats)

                if move_type == 'reverse_sub':
                    i = random.randint(0, num_items - 2)
                    j = random.randint(i + 1, num_items - 1)
                    short_name = cat_name[:8]
                    neighbors.append((reverse_subcategories(tracker, cat_idx, i, j), f"rev_{short_name}[{i}:{j}]"))
                else:
                    from_idx = random.randint(0, num_items - 1)
                    to_idx = random.randint(0, num_items - 1)
                    if from_idx != to_idx:
                        short_name = cat_name[:8]
                        neighbors.append((insert_subcategory(tracker, cat_idx, from_idx, to_idx), f"ins_{short_name} {from_idx}->{to_idx}"))
                    else:
                        neighbors.append((copy.deepcopy(tracker), "noop"))
            else:
                # Fallback
                if num_categories > 1:
                    i = random.randint(0, num_categories - 2)
                    j = random.randint(i + 1, num_categories - 1)
                    neighbors.append((reverse_categories(tracker, i, j), f"rev_cat[{i}:{j}]"))
                else:
                    neighbors.append((copy.deepcopy(tracker), "noop"))
        else:
            neighbors.append((copy.deepcopy(tracker), "noop"))

    return neighbors


def acceptance_probability(old_cost: int, new_cost: int, temperature: float) -> float:
    if new_cost < old_cost:
        return 1.0
    return math.exp((old_cost - new_cost) / temperature)


def simulated_annealing(base_dir: str, tracker_path: str, max_iterations: int = None):
    print("=" * 70)
    print(f"Simulated Annealing - PDF Page Optimizer (parallel={PARALLEL_NEIGHBORS})")
    print("=" * 70)

    current = load_tracker(tracker_path)

    # Backup
    backup_path = tracker_path + '.backup'
    save_tracker(current, backup_path)
    print(f"Backup: {backup_path}")

    # Initial evaluation
    print("\nEvaluating initial configuration...")
    save_tracker(current, tracker_path)
    current_cost = compile_and_count(base_dir)
    print(f"Initial pages: {current_cost}")

    best = copy.deepcopy(current)
    best_cost = current_cost

    temperature = INITIAL_TEMP
    iteration = 0
    no_improvement = 0

    print(f"\nStarting (T={INITIAL_TEMP}, cooling={COOLING_RATE}, parallel={PARALLEL_NEIGHBORS})")
    print("-" * 70)

    with ProcessPoolExecutor(max_workers=PARALLEL_NEIGHBORS) as executor:
        while temperature > MIN_TEMP:
            if max_iterations and iteration >= max_iterations:
                break

            # Generate multiple neighbors
            neighbors = generate_neighbors(current, PARALLEL_NEIGHBORS)

            # Prepare evaluation tasks
            tasks = [
                (base_dir, neighbor, desc, idx)
                for idx, (neighbor, desc) in enumerate(neighbors)
            ]

            # Evaluate in parallel
            futures = [executor.submit(evaluate_neighbor, task) for task in tasks]
            results = [f.result() for f in futures]

            # Find best neighbor
            results.sort(key=lambda x: x[1])  # Sort by page count
            best_neighbor_idx, best_neighbor_pages, best_move, best_neighbor_data = results[0]

            # Print all results for this batch
            iteration += 1
            print(f"[{iteration:3d}] T={temperature:6.2f} | Evaluated {len(results)} neighbors:")
            for idx, pages, desc, _ in results:
                marker = " <--" if pages == best_neighbor_pages and pages < current_cost else ""
                print(f"       {desc:25s} -> {pages:2d}p{marker}")

            # Accept best neighbor if it improves or by probability
            ap = acceptance_probability(current_cost, best_neighbor_pages, temperature)

            if random.random() < ap:
                current = best_neighbor_data
                current_cost = best_neighbor_pages

                if best_neighbor_pages < best_cost:
                    best = copy.deepcopy(best_neighbor_data)
                    best_cost = best_neighbor_pages
                    no_improvement = 0
                    print(f"       >>> NEW BEST: {best_cost} pages <<<")
                else:
                    no_improvement += 1
                    print(f"       Accepted (current={current_cost}, best={best_cost})")
            else:
                no_improvement += 1
                print(f"       Rejected (current={current_cost}, best={best_cost})")

            print()

            if no_improvement > 20:
                print(f"Early stopping: no improvement for {no_improvement} rounds")
                break

            temperature *= COOLING_RATE

    # Save best
    save_tracker(best, tracker_path)
    compile_and_count(base_dir)

    print("=" * 70)
    print("COMPLETE")
    print("=" * 70)
    print(f"Best: {best_cost} pages")
    print(f"Backup: {backup_path}")


def main():
    script_dir = Path(__file__).parent
    base_dir = script_dir.parent
    tracker_path = base_dir / 'tracker.yaml'

    print(f"Directory: {base_dir}")
    print(f"CPUs: {cpu_count()}")

    max_iter = int(sys.argv[1]) if len(sys.argv) > 1 else None
    simulated_annealing(str(base_dir), str(tracker_path), max_iter)


if __name__ == "__main__":
    main()
