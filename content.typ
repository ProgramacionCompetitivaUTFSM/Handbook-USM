#import "lib/render.typ": *

#set page(paper: "a4", columns: 2, margin: (x: 2em, y: 2em), numbering: "1/1")
#set text(font: "New Computer Modern", size: 7pt)

#render-from-tracker("tracker.yaml", default-config)
