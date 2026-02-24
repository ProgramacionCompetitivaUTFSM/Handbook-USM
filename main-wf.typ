#set page(paper: "a4", flipped: true, margin: 1.5cm)
#set text(font: "New Computer Modern", size: 11pt)

#grid(
  columns: (1fr, 1.5fr),
  column-gutter: 1.5cm,
  align(center + horizon)[
    #image(width: 90%, "img/utfsm_cp.png")
    #v(0.5em)
    #text(size: 1.8em, weight: "bold")[Handbook USM]
    #v(0.2em)
    #text(size: 1.2em)[World Finals]
    #v(1em)
    #set text(size: 10pt)
    #table(
      columns: 2,
      stroke: none,
      align: (left, left),
      [*Team:*], [La CASneta],
      [*University:*], [UTFSM],
    )
  ],
  [
    #text(size: 1.2em, weight: "bold")[Contents]
    #v(0.5em)
    #set text(size: 8pt)
    #let data = yaml("tracker-wf.yaml")
    #for x in data {
      let content-list = x.at(1)
      for topic-entry in content-list {
        for (topic-name, items) in topic-entry {
          let cat = topic-name.split("-").join(" ")
          let cat = upper(cat.first()) + cat.slice(1)
          [*#cat:* ]
          let all-files = ()
          for item in items {
            if type(item) == str {
              all-files.push(item.split(".").at(0).split("-").join(" "))
            } else if type(item) == dictionary {
              for (_, files) in item {
                for f in files {
                  all-files.push(f.split(".").at(0).split("-").join(" "))
                }
              }
            }
          }
          [#all-files.join(", ")]
          linebreak()
          v(0.3em)
        }
      }
    }
  ],
)

// Content
#let content-file = read("content-wf.typ")
#eval(content-file, mode: "markup")
