output = presentation.pdf

all: $(output)

$(output): presentation.tex
	pdflatex presentation.tex

clear:
	rm $(output) presentation.aux presentation.log presentation.nav presentation.out presentation.snm presentation.toc
