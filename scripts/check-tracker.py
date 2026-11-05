import argparse
import os
import sys

import yaml


def files_on_disk(content_dir):
    return {
        os.path.relpath(os.path.join(root, name), content_dir)
        for root, _, names in os.walk(content_dir)
        for name in names
    }


def files_in_tracker(tracker_path):
    with open(tracker_path) as f:
        tree = yaml.safe_load(f)["content"]

    files = []

    def walk(items, path):
        for item in items:
            if isinstance(item, str):
                files.append(os.path.join(*path, item))
            else:
                for folder, children in item.items():
                    walk(children, path + [folder])

    walk(tree, [])
    return files


def main():
    parser = argparse.ArgumentParser(description="Check that a tracker matches the content directory.")
    parser.add_argument("tracker")
    parser.add_argument("content_dir")
    parser.add_argument(
        "--subset",
        action="store_true",
        help="the tracker lists only some files, so skip the untracked-file check",
    )
    args = parser.parse_args()

    on_disk = files_on_disk(args.content_dir)
    tracked = files_in_tracker(args.tracker)

    missing = sorted(set(tracked) - on_disk)
    untracked = [] if args.subset else sorted(on_disk - set(tracked))
    duplicated = sorted({f for f in tracked if tracked.count(f) > 1})

    problems = [
        ("Tracked but missing from disk", missing),
        ("On disk but not tracked", untracked),
        ("Tracked more than once", duplicated),
    ]
    failed = False
    for title, files in problems:
        if files:
            failed = True
            print(f"{args.tracker}: {title}:")
            for f in files:
                print(f"  {f}")

    if failed:
        sys.exit(1)
    print(f"{args.tracker}: OK ({len(tracked)} files)")


if __name__ == "__main__":
    main()
