# Handbook USM

Algorithms and data structures for competitive programming, maintained by
students of Universidad Técnica Federico Santa María (UTFSM).

The repository builds two PDFs:

| File          | Source        | Layout                                        |
| ------------- | ------------- | --------------------------------------------- |
| `main.pdf`    | `main.typ`    | Full handbook, A4 portrait, two columns.      |
| `main-wf.pdf` | `main-wf.typ` | Team notebook for contests, A4 landscape, four columns, with an index. |

## Download

Every push to `master` publishes both PDFs as a
[GitHub release](https://github.com/ProgramacionCompetitivaUTFSM/Handbook-USM/releases/latest).

## Build locally

Install [Typst](https://typst.app/) 0.14.2, the version CI uses. Then run:

```bash
typst compile main.typ      # main.pdf
typst compile main-wf.typ   # main-wf.pdf
```

## Repository layout

```
content/      One file per algorithm, grouped as <category>/<subcategory>/<file>
lib/          Typst rendering code (render.typ) and the MD5 plugin for code hashes
scripts/      check-tracker.py and the page-count optimizer (annealing.py)
tracker.yaml      Order and contents of main.pdf
tracker-wf.yaml   Order and contents of main-wf.pdf, a subset of content/
```

Only files listed in a tracker appear in its PDF. The tracker order is the
order of the PDF.

## Add an algorithm

1. Create the file in the right folder under `content/`. Use `.cpp`, `.py`
   or `.typ`.
2. Start a `.cpp` file with a block comment. The renderer removes the first
   and last line of the comment and renders the rest as Typst markup above
   the code:

   ```cpp
   /*
    *Description:* Range minimum queries in $O(1)$ after $O(n log n)$ build.
    *Status:* Tested on CSES
   */
   ```

   A `.py` file uses a `"""` docstring in the same way.
3. Add the file name to `tracker.yaml` under its category and subcategory.
4. If the file belongs in the contest notebook, also add it to
   `tracker-wf.yaml`.
5. Run the tracker check:

   ```bash
   python scripts/check-tracker.py tracker.yaml content
   python scripts/check-tracker.py tracker-wf.yaml content --subset
   ```

## Naming rules

- Use lowercase words separated by hyphens: `segment-tree-lazy.cpp`.
- The file name becomes the section title. `fenwick-tree-2d.cpp` renders as
  "Fenwick Tree 2D".
- Acronyms render in uppercase only if they are in the `title-words` table
  in `lib/render.typ`. Add a new acronym there.
- Prefer a descriptive name over an abbreviation that is not in that table.
- Put one algorithm or data structure in each file.

## Code style

- Indent with two spaces. Do not use tabs.
- Do not use contest macros such as `rep` or `repx`.
- Assume the template in `content/general/templates/template.cpp`.

## Continuous integration

Every pull request runs `.github/workflows/ci.yml`:

- `check-tracker` fails if a tracker lists a file that does not exist, lists
  a file twice, or if `tracker.yaml` misses a file in `content/`.
- `compile` builds both PDFs and attaches them to the run as artifacts, so
  you can review the output of a pull request without building it.

Pushes to `master` also run `release-new-version.yml`, which tags the commit
as `YYYY.MM.DD-<sha>` and publishes both PDFs.

## Team

**Maintainers:** Gabriel Carmona (MrYhatoh), Carlos Lagos (CharlesLakes),
Sebastián Torrealba (storrealbac), Abner Vidal (abner_vidal).

**Contributors:** Javier Oliva (JOliva), Marcelo Lemus (MarceloL), Bastián
Jiménez (FreddyTurbins), Christian Mauch (TooMuchGames).

## License

MIT. See [LICENSE](LICENSE).
