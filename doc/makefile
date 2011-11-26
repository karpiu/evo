output = presentation.pdf

tests = 001.res 002.res 003.res

001.res:
	../src/evo.e -r < ../in/001.in > 001.res

002.res:
	../src/evo.e -r < ../in/002.in > 002.res

003.res:
	../src/evo.e -r < ../in/003.in > 003.res

graphs = 004.pdf
graphs: $(graphs)

004.res:
	../src/evo.e -e < ../in/004.in > 004.res

004.pdf: 004.res graph.gnuplot
	gnuplot graph.gnuplot < 004.res > 004.eps
	epstopdf 004.eps

all: $(output)

$(output): presentation.tex $(tests) $(graphs)
	pdflatex presentation.tex

tests: $(tests)
clear_tests:
	rm $(tests)

clear:
	rm $(output) presentation.aux presentation.log presentation.nav presentation.out presentation.snm presentation.toc
