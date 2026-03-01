#set page(paper: "a4", flipped: true, margin: 1.5cm)
#set text(font: "New Computer Modern", size: 11pt)

// Cover page
#align(center + horizon)[
  #image(width: 65%, "img/logo-usm.png")
  #v(1.5em)
  #text(size: 2em, weight: "bold")[La CASneta]
  #v(0.8em)
  #text(size: 1.2em)[Abner Vidal · Carlos Lagos · Sebastián Torrealba]
]

#pagebreak()

// Content
#let content-file = read("content-wf.typ")
#eval(content-file, mode: "markup")
