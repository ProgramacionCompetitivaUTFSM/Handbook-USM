import os
from re import sub, match
path = "src/"

file_latex = open("header.tex", "r")
file_new_latex = open("handbook.tex", "w")

for line in file_latex:
    file_new_latex.write(line)
file_latex.close()
file_new_latex.write("\n")

for file in os.listdir(path):

    print(file)
    file_text = open(f"{path}/{file}", "r")

    # Spaces between capital letters
    name_w = sub("([a-z])([A-Z])", "\g<1> \g<2>", file)
    name_w = name_w.split(".cpp")[0]

    file_new_latex.write("\\begin{tikzpicture}\n")
    file_new_latex.write("\\node [mybox] (box){\n\\begin{minipage}{0.3\\textwidth}")
    file_new_latex.write("\\begin{lstlisting}\n")
    
    for line in file_text:
        file_new_latex.write(line)

    file_new_latex.write("\\end{lstlisting}\n")
    file_new_latex.write("\\end{minipage}\n")
    file_new_latex.write("};")
    file_new_latex.write("\\node[fancytitle, right=10pt] at (box.north west) {\\footnotesize " + name_w + "};\n")
    file_new_latex.write("\\end{tikzpicture}\n")
    file_text.close()

file_new_latex.write("\\end{multicols*}\n\\end{document}\n")
file_new_latex.close()

