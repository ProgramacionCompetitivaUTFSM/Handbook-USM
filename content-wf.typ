#import "lib/render.typ": *

#let university = "UTFSM"
#let team-name = "Team Name"

#let wf-config = (
  code-text-size: 6.5pt,
  code-small-text-size: 5pt,
  code-small-threshold: 90,
  category-size: 10pt,
  subcategory-size: 8pt,
  section-size: 9pt,
  description-size: 7pt,
  category-spacing: 0.8em,
  subcategory-spacing: 0.5em,
  category-line-stroke: 1pt,
  pagebreak-between-topics: false,
  breakable: true,
)

#set page(
  paper: "a4",
  flipped: true,
  columns: 3,
  margin: (x: 0.5cm, top: 1.2cm, bottom: 0.5cm),
  numbering: "1",
  number-align: right + top,
  header: [
    #set text(size: 8pt)
    #university — #team-name
    #h(1fr)
    #context counter(page).display("1")
  ],
)

#set columns(gutter: 0.3cm)
#set text(font: "New Computer Modern", size: 8pt)

#render-from-tracker("tracker-wf.yaml", wf-config)
