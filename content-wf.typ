#import "lib/render.typ": *

#let university = "UTFSM"
#let team-name = "La CASneta"

#let wf-config = (
  code-text-size: 6.5pt,
  code-small-text-size: 6.5pt,
  code-small-threshold: 90,
  category-size: 10pt,
  subcategory-size: 8pt,
  section-size: 9pt,
  description-size: 7pt,
  category-spacing: 0.5em,
  subcategory-spacing: 0.5em,
  category-line-stroke: 1pt,
  pagebreak-between-topics: false,
  breakable: true,
)

#set page(
  paper: "a4",
  flipped: true,
  columns: 4,
  margin: (x: 0.3cm, top: 1.2cm, bottom: 0.3cm),
  numbering: "1",
  number-align: right + top,
  header: context {
    pad(top: 0.3cm)[
      #set text(size: 8pt)
      #[#university — #team-name]
      #let current-page = counter(page).at(here()).first()
      #let all-titles = query(<section-title>)
      #let page-titles = all-titles.filter(m =>
        counter(page).at(m.location()).first() == current-page
      ).map(m => m.value)
      #place(center + top)[
        #block(width: 70%, align(center)[
          #text(weight: "bold", size: 7pt)[
            #page-titles.dedup().join(", ")
          ]
        ])
      ]
      #place(right + top)[
        #counter(page).display("1")
      ]
    ]
  },
)

#set columns(gutter: 0.2cm)
#set text(font: "New Computer Modern", size: 6.5pt)

#render-from-tracker("tracker-wf.yaml", wf-config)
