import yaml
import sys
import os

# TODO: show files tracked but not existing
# TODO: implement auto-fix option

def dfs_files(base_directory):
    file_list = []
    for root, dirs, files in os.walk(base_directory):
        for file in files:
            file_list.append(os.path.relpath(os.path.join(root, file), base_directory))
    return file_list

def files_tracked(tracker_dict):
    path = []
    files = []
    def dfs(current_dict):
        for element in current_dict:
            if isinstance(element, str):
                files.append(os.path.join(*path, element))
            else:
                for key in element:
                    path.append(key)
                    dfs(element[key])
                    path.pop()
    dfs(tracker_dict["content"])
    return files

def main(tracker, content_directory):
    with open(tracker, 'r') as file:
        tracked_files = yaml.safe_load(file)

    existing_files = set(dfs_files(content_directory))

    tracked_files = files_tracked(tracked_files)

    for file in tracked_files:
        existing_files.discard(file)
    
    if len(existing_files) == 0:
        print("All files are tracked.")
    else:
        print("Untracked files:")
        for file in existing_files:
            print(file)
        exit(1)

if __name__ == "__main__":
    arguments = sys.argv

    if len(arguments) != 3:
        print("Usage: python check-tracker.py <tracker-file> <base-directory>")
        sys.exit(1)

    tracker_file = arguments[1]
    base_directory = arguments[2]
    main(tracker_file, base_directory)