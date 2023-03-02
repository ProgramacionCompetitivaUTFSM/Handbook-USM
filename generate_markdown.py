import os
from re import sub
path = "src/"

markdown_file = open("handbook.md", "w")


sorted_path = os.listdir(path)
sorted_path.sort()

for dir in sorted_path:
    markdown_file.write(f"## {dir}\n")
    for file in os.listdir(path + "/" + dir):
        print(f"{dir}/{file}")
        file_text = open(f"{path}/{dir}/{file}", "r")

        # Spaces between capital letters
        name_w = sub("([a-z])([A-Z])", "\g<1> \g<2>", file)
        name_w = name_w.split(".cpp")[0]

        markdown_file.write(f"### {name_w}\n\n")
        markdown_file.write("```cpp\n")
        for line in file_text:
            markdown_file.write(line)

        markdown_file.write("\n```\n\n")
        file_text.close()
