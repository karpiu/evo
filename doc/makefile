output = presentation.pdf

tests = 001.res 002.res 003.res 004.res 005.res

001.res:
	../src/evo.e -r < ../in/001.in > 001.res

002.res:
	../src/evo.e -r < ../in/002.in > 002.res

003.res:
	../src/evo.e -r < ../in/003.in > 003.res

004.res:
	../src/evo.e -e < ../in/004.in > 004.res

005.res:
	../src/evo.e -e < ../in/005.in > 005.res

tests: $(tests)
clear_tests:
	rm -f $(tests)


graphs = 004.pdf 005.pdf
graphs: $(graphs)
clear_graphs:
	rm -f $(graphs)

%.pdf: %.res graph.gnuplot
	gnuplot graph.gnuplot < $< > tmp.eps
	epstopdf tmp.eps --outfile=$@
	rm tmp.eps

all: $(output)

$(output): presentation.tex $(tests) $(graphs)
	pdflatex presentation.tex

clear: clear_tests clear_graphs
	rm -f $(output) presentation.aux presentation.log presentation.nav presentation.out presentation.snm presentation.toc
