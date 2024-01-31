import os
from re import sub
path = "src/"

typst_file = open("handbook.typ", "w")

sorted_path = os.listdir(path)
sorted_path.sort()

typst_headers = """
#set page(
  paper: "a4",
  columns: 2,
  margin: (x: 2em, y: 2em)
)

#set text(
  font: "New Computer Modern",
  size: 7pt
)

#let template-code(title: [], body) = {
  block(
    breakable: false,
    radius: 5pt,
    inset: 1em,
    stroke: 0.9pt,
    spacing: 1.5em,
    width: 100%
  )[

  #place(dy: -15pt)[
    #block(
      fill: black,
      inset: 3pt
    )[
      #text(fill: white, weight: "semibold")[
        #title
      ]
    ]
  ]
  #body
  ]
}
"""

typst_file.write(typst_headers)

for dir in sorted_path:
    typst_file.write(f"= {dir}\n")
    typst_file.write(f"#v(1.5em)\n")
    for file in os.listdir(path + "/" + dir):
        print(f"{dir}/{file}")
        file_text = open(f"{path}/{dir}/{file}", "r")

        # Spaces between capital letters
        name_w = sub("([a-z])([A-Z])", "\g<1> \g<2>", file)
        name_w = name_w.split(".cpp")[0]

        typst_file.write(f'#template-code(title: "{name_w}")[\n')
        typst_file.write("```cpp\n")
        for line in file_text:
            typst_file.write(line)
        typst_file.write("```\n")
        typst_file.write("]\n\n")
        file_text.close()
    typst_file.write("#pagebreak()\n\n")
typst_file.close()
