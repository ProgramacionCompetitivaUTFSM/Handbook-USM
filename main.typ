
#set page(
  paper: "a4"
)

#set text(
  font: "New Computer Modern",
  size: 13pt
)

// Cover
#align(center)[
  #image(width: 150%, "img/utfsm_cp.png")
]

#align(center)[
  #text(size: 2.5em)[Handbook USM]
]

*Maintainers:*
- Gabriel Carmona (MrYhatoh)
- Carlos Lagos (CharlesLakes)
- Sebastián Torrealba (storrealbac)
- Abner Vidal (abner_vidal)

*Contributors:*
- Javier Oliva (JOliva)
- Marcelo Lemus (MarceloL)

// Content
#let content-file = read("content.typ")
#eval(content-file, mode: "markup")
