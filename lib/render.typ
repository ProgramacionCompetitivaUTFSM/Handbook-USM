#import "hash.typ": md5, hex

#let current-category = state("current-category", none)
#let current-subcategory = state("current-subcategory", none)

#let default-config = (
  code-text-size: 7pt,
  code-small-text-size: 5.3pt,
  code-small-threshold: 90,
  category-size: 18pt,
  subcategory-size: 12pt,
  section-size: 15pt,
  description-size: 10pt,
  category-spacing: 1.5em,
  subcategory-spacing: 1em,
  category-line-stroke: 1.5pt,
  pagebreak-between-topics: true,
  breakable: false,
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

// Language configuration: extension -> (syntax-highlight-name, comment-regex, comment-start-pattern)
#let lang-config = (
  "cpp": ("cpp", regex("\/\*[\s\S]*?\*\/"), "/"),
  "py": ("python", regex("\"\"\"[\s\S]*?\"\"\""), "\"\"\""),
)

#let get-description-from-code(string, comment-regex, start-pattern) = {
  let comments = string.find(comment-regex)

  if type(comments) != str or not string.trim().starts-with(start-pattern) {
    return text(red)[*You must provide a description for each template code!*]
  }

  let lines = comments.split("\n")
  lines.slice(1, lines.len() - 1).join("\\").trim()
}

#let remove-description-from-code(string, comment-regex, start-pattern) = {
  if not string.trim().starts-with(start-pattern) {
    return string
  }
  string.replace(comment-regex, "", count: 1).trim()
}

#let template-code(config, title: [], only-code: [], description: none, body) = {
  let code-lines = only-code.split("\n").len()
  let text-size = if code-lines > config.code-small-threshold { config.code-small-text-size } else { config.code-text-size }

  if config.breakable {
    block(
      breakable: true,
      inset: 0pt,
      stroke: (left: 0.9pt, right: 0.9pt),
      above: 0.6em,
      width: 100%
    )[
      #block(breakable: false, width: 100%)[
        #line(length: 100%, stroke: 0.9pt)
        #pad(x: 1em, top: 0.4em)[
          #place(top + right, dy: -0.4em - 15pt)[
            #block(fill: black, inset: 3pt)[
              #text(fill: green)[\#]
              #text(fill: white, weight: "semibold")[#get-code-hash(only-code)]
            ]
          ]
          #place(dy: -0.4em - 15pt)[
            #block(fill: black, inset: 3pt)[
              #text(fill: white, weight: "semibold")[#title]
            ]
          ]
          #if description != none {
            set text(size: text-size)
            description
            line(length: 100%)
          }
        ]
      ]
      #pad(x: 1em)[
        #set text(size: text-size)
        #body
      ]
      #line(length: 100%, stroke: 0.9pt)
    ]
  } else {
    block(
      breakable: false,
      radius: 5pt,
      inset: 1em,
      stroke: 0.9pt,
      spacing: 1.5em,
      width: 100%
    )[
      #place(top + right, dy: -15pt)[
        #block(fill: black, inset: 3pt)[
          #text(fill: green)[\#]
          #text(fill: white, weight: "semibold")[#get-code-hash(only-code)]
        ]
      ]
      #place(dy: -15pt)[
        #block(fill: black, inset: 3pt)[
          #text(fill: white, weight: "semibold")[#title]
        ]
      ]
      #set text(size: text-size)
      #if description != none {
        description
        line(length: 100%)
      }
      #body
    ]
  }
}

#let template-category-title(config, title) = {
  current-category.update(title)
  current-subcategory.update(none)
  block(spacing: config.category-spacing)[
    #text(weight: "black", size: config.category-size)[#title]
    #v(-0.5em)
    #line(length: 100%, stroke: config.category-line-stroke)
  ]
}

#let template-subcategory-title(config, title) = {
  current-subcategory.update(title)
  block(spacing: config.subcategory-spacing)[
    #text(weight: "bold", size: config.subcategory-size, fill: rgb("#444"))[#sym.triangle.filled.r #title]
  ]
}

#let template-section-title(config, title) = {
  text(weight: "black", size: config.section-size)[#title]
}

#let typst-section(config, title: [], content: []) = {
  if config.breakable {
    block(
      breakable: true,
      inset: 0pt,
      stroke: (left: 0.9pt, right: 0.9pt),
      above: 0.6em,
      width: 100%
    )[
      #block(breakable: false, width: 100%)[
        #line(length: 100%, stroke: 0.9pt)
        #pad(x: 1em)[
          #place(dy: -15pt)[
            #block(fill: black, inset: 3pt)[
              #text(fill: white, weight: "semibold")[#title]
            ]
          ]
        ]
      ]
      #pad(x: 1em, bottom: 1em)[
        #eval(content, mode: "markup")
      ]
      #line(length: 100%, stroke: 0.9pt)
    ]
  } else {
    block(
      breakable: false,
      inset: 1em,
      stroke: 0.9pt,
      spacing: 2em,
      width: 100%
    )[
      #align(center)[#text(size: config.description-size, weight: "bold")[#title]]
      #eval(content, mode: "markup")
    ]
  }
}

#let render-file(config, path, file-name) = {
  let file-extension = path.split(".").at(-1)
  let template-title = title-case(file-name.split(".").at(0).split("-").join(" "))
  let file = read(path)

  [#metadata(template-title) <section-title>]

  if file-extension == "typ" {
    typst-section(config, title: template-title, content: file)
  } else if file-extension in lang-config {
    let (lang-name, comment-regex, start-pattern) = lang-config.at(file-extension)
    let all-code = raw(file, lang: lang-name)
    let comments = get-description-from-code(content-to-string(all-code), comment-regex, start-pattern)
    let without-comments = remove-description-from-code(content-to-string(all-code), comment-regex, start-pattern).trim()

    let desc = [#eval(comments, mode: "markup")]
    template-code(config, title: template-title, only-code: without-comments, description: desc)[
      #raw(without-comments, lang: lang-name)
    ]
  }
}

#let render-from-tracker(tracker-path, config) = {
  for x in yaml("../" + tracker-path) {
    let content-list = x.at(1)
    for i in range(0, content-list.len()) {
      let topic-entry = content-list.at(i)
      for (topic-name, items) in topic-entry {
        // Show main category title
        let category-title = title-case(topic-name.split("-").join(" "))
        template-category-title(config, category-title)

        for item in items {
          if type(item) == str {
            // Direct file in topic (no subtopic)
            let path = "../content/" + topic-name + "/" + item
            render-file(config, path, item)
          } else if type(item) == dictionary {
            // Subtopic with files
            for (subtopic-name, files) in item {
              let subcategory-title = title-case(subtopic-name.split("-").join(" "))
              template-subcategory-title(config, subcategory-title)
              for file-name in files {
                let path = "../content/" + topic-name + "/" + subtopic-name + "/" + file-name
                render-file(config, path, file-name)
              }
            }
          }
        }
      }
      if config.pagebreak-between-topics and i != content-list.len() - 1 {
        pagebreak()
      }
    }
  }
}
