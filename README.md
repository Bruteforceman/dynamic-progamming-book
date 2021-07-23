# Dynamic Programming Book
Here, you can keep track with the latest version of the book. The book can be found at main.pdf. You do not need to download anything else.

This book is written with the help of LatexBangla. Also, huge shoutout to AngryPascal for letting us use his [book template](https://github.com/AnglyPascal/book_template).

# Usage

## Bibliography
For initial generation of bibliography, run:

```
xelatex main
bibtex main
```

after that, just run `xelatex main` once (or twice if you add new references).

### Syntax
See [this](https://www.overleaf.com/learn/latex/Bibliography_management_with_bibtex#The_bibliography_file). Append entry in `bibliography.bib`. Cite using `\cite{label}`.

## Available environments (for now)

  - `reducedproblem`: just a box (for now)
  - `bigcondition`: just a box (for now)
  - `diybox` (depricated)
  - `theorem(*)`: parent=`chapter`
  - `corollary(*)`: sibling=`theorem`
  - `proposition(*)`: sibling=`theorem`
  - `claim(*)`: sibling=`theorem`
  - `definition(*)`: parent=`chapter`
  - `problem(*)`: parent=`chapter`
  - `exercise(*)`: parent=`chapter`
  - `example(*)`: parent=`chapter`
  - `observation(*)`: parent=`exmaple`; should only be used inside `example` environment
  - `optimization(*)`: parent=`example`; should only be used inside `example` environment
  - `lemma(*)`: sibling=`theorem` (todo: parent=`theorem`)
  - `note*`
  - `hint`:
```
\begin{exercise}
statement
\end{exercise}
\begin{hint}
hints
\end{hint}
```

## Macros and Commands
- `\cbra{x}`: puts curly braces around `x`
- `\bbra{x}`: boxed brackets
- `\pbra{x}`: parentheses
- `\floor{x}`
- `\ceil{x}`
- `\one{x}`: `[x]`
- `\two{x}{y}`: `[x, y]`
- `\three{x}{y}{z}`: `[x, y, z]`
- `\four{x}{y}{z}{a}`: `[x, y, z, a]`
- `\DP`: text for dp
- `\compl{x}`: complement set of {x}, currently set to overbar
- `\ora{x}`: overrightarrow
- `\abs{x}`: vertical bars around x i.e. `|x|`
- `\downmapsto`: depricated; use `\rotatebox` each time
