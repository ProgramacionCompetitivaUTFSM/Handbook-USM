import os

path = "src/"

for file in os.listdir(path):
    print(file)
    file_text = open(f"{path}/{file}", "r");
    for line in file_text:
        print(line)
    file_text.close()
