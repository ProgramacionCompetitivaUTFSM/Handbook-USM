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
  code-above: 1.5em,
  subcategory-spacing-below: 1.2em,
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

// Index: only folders and subfolders
#text(weight: "bold", size: 9pt)[Index]
#v(0.2em)
#line(length: 100%, stroke: 0.6pt)
#v(0.3em)
#let idx-data = yaml("tracker-wf.yaml")
#context {
  let cat-anchors = query(<category-anchor>)
  let sub-anchors = query(<subcategory-anchor>)
  let get-page(anchors, title) = {
    let m = anchors.filter(a => a.value == title)
    if m.len() > 0 { str(counter(page).at(m.first().location()).first()) } else { "" }
  }
  for x in idx-data {
    let content-list = x.at(1)
    for topic-entry in content-list {
      for (topic-name, items) in topic-entry {
        let cat = title-case(topic-name.split("-").join(" "))
        let cat-page = get-page(cat-anchors, cat)
        let subtopics = items.filter(i => type(i) == dictionary).map(i => {
          let (name, _) = i.pairs().first()
          let sub-name = title-case(name.split("-").join(" "))
          (name: sub-name, page: get-page(sub-anchors, sub-name))
        })
        grid(columns: (1fr, auto), gutter: 0pt,
          text(weight: "bold")[#cat],
          text(weight: "bold")[#cat-page]
        )
        for sub in subtopics {
          grid(columns: (auto, 1fr, auto), gutter: 0pt,
            h(0.8em),
            text(fill: rgb("#555"))[#sub.name],
            text(fill: rgb("#555"))[#sub.page]
          )
        }
      }
    }
  }
}
#v(0.3em)
#line(length: 100%, stroke: 0.6pt)
#v(0.8em)

#render-from-tracker("tracker-wf.yaml", wf-config)
