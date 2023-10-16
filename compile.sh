#!/bin/bash

rm copypaste.txt

echo "Generating TeX code..."
python generate_latex.py
echo "Generated code!"

# List LaTeX files and store them in tex_files.txt
ls -1 generated_tex > tex_files.txt

tex_files="tex_files.txt"
while IFS= read -r file; do
    file="${file%.*}"
    file=$(printf "%q" "$file")
    echo "pdflatex -shell-escape -interaction=nonstopmode generated_tex/$file.tex" >> copypaste.txt
done < "$tex_files"

# Clean up
rm "$tex_files"

echo "rm *.aux" >> copypaste.txt
echo "rm *.log" >> copypaste.txt
echo "mkdir compiled" >> copypaste.txt
echo "mv *.pdf compiled/" >> copypaste.txt
echo "pdftk compiled/*.pdf cat output handbook.pdf" >> copypaste.txt
echo "rm compiled/*.pdf" >> copypaste.txt
echo "rm -rf generated_tex" >> copypaste.txt
echo "rm -rf compiled" >> copypaste.txt