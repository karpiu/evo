output = presentation.pdf

program = ../src/evo.e
in = ../in

tests = 001.res 002.res 003.res 004.res 005.res

001.res:
	$(program) -r -i 5 < $(in)/001.in > 001.res

002.res:
	$(program) -r -i 5 < $(in)/002.in > 002.res

003.res:
	$(program) -r -i 5 < $(in)/003.in > 003.res

004.res:
	$(program) -e avg -i 1000 < $(in)/004.in > 004.res

005.res:
	$(program) -e avg -i 1000 < $(in)/005.in > 005.res

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
