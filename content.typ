#import "lib/hash.typ": md5, hex

#set page(
  paper: "a4",
  columns: 2,
  margin: (x: 2em, y: 2em),
  numbering: "1/1"
)

#set text(
  font: "New Computer Modern",
  size: 7pt
)

#let title-case(string) = {
  if string.len() <= 3 {
    return upper(string)
  }

  return string.replace(
    regex("[A-Za-z]+('[A-Za-z]+)?"),
    word => upper(word.text.first()) + lower(word.text.slice(1))
  )
}

#let content-to-string(content) = {
  if content.has("text") {
    content.text
  } else if content.has("children") {
    content.children.map(content-to-string).join("")
  } else if content.has("body") {
    content-to-string(content.body)
  } else if content == [ ] {
    " "
  }
}

#let get-code-hash(string) = {
  string = string.replace(regex("[\n\t\s]"), "")
  hex(md5(string)).slice(0, 6)
}

#let comments-regex = regex("\/\*[\s\S]*?\*\/")

#let get-description-from-code(string) = {
  let comments = string.find(comments-regex)

  if type(comments) != str or string.trim().at(0) != "/" {
    return text(red)[*You must provide a description for each template code!*]
  }

  let lines = comments.split("\n")
  lines.slice(1, lines.len() - 1).join("\\").trim()
}

#let remove-description-from-code(string) = {
  if string.trim().at(0) != "/" {
    return string
  }
  string.replace(comments-regex, "", count: 1).trim()
}

#let template-code(title: [], only-code: [], body) = {
  let code-lines = only-code.split("\n").len()
  let text-size = if code-lines > 90 { 5.3pt } else { 7pt }
  
  block(
    breakable: false,
    radius: 5pt,
    inset: 1em,
    stroke: 0.9pt,
    spacing: 1.5em,
    width: 100%
  )[
    #place(dy: -15pt, dx: 220pt)[
      #block(
        fill: black,
        inset: 3pt,
      )[
        #text(fill: green)[\#]
        #text(fill: white, weight: "semibold")[
          #get-code-hash(only-code)
        ]
      ]
    ]

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

    #set text(size: text-size)
    #body
  ]
}

#let template-section-title(title) = {
  text(weight: "black", size: 15pt)[#title]
}

#let typst-section(title: [], content: []) = {
  block(
    breakable: false,
    inset: 1em,
    stroke: 0.9pt,
    spacing: 2em,
    width: 100%
  )[
    #align(center)[#text(size: 10pt, weight: "bold")[#title]]
    #eval(content, mode: "markup")
  ]
}

#for x in yaml("tracker.yaml") {
  let content-list = x.at(1)
  for i in range(0, content-list.len()) {
    for (folder-name, files) in content-list.at(i) {
      let title-section = title-case(folder-name.split("-").join(" "))
      template-section-title(title-section)
      
      for file-name in files {
        let path = "content/" + folder-name + "/" + file-name
        let file-extension = path.split(".").at(-1)
        let template-title = title-case(file-name.split(".").at(0).split("-").join(" "))
        let file = read(path)
        
        if file-extension == "typ" {
          typst-section(title: template-title, content: file)
        } else if file-extension == "cpp" {
          let all-code = raw(file, lang: "cpp")
          let comments = get-description-from-code(content-to-string(all-code))
          let without-comments = remove-description-from-code(content-to-string(all-code))
          
          template-code(title: template-title, only-code: without-comments)[
            #eval(comments, mode: "markup")
            #line(length: 100%)
            #raw(without-comments, lang: "cpp")
          ]
        }
      }
    }
    if i != content-list.len() - 1 {
      pagebreak()
    }
  }
}
