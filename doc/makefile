program = ../src/evo.e
in = ../in

# here specify tests
# note: up to 3 graphs in one image
# more than one graph is created using ./joinN.sh script (same amount
# of rows needed)

004.res: $(in)/004.in
	$(program) -e avg -i 500 < $< > $@

005.res: $(in)/005.in
	$(program) -e best -i 500 < $< > $@

006a.res: $(in)/006.in
	$(program) -e avg -i 50 -x pmx < $< > $@

006b.res: $(in)/006.in
	$(program) -e avg -i 50 -x cx < $< > $@

006c.res: $(in)/006.in
	$(program) -e avg -i 50 -x ox < $< > $@

006.res: 006a.res 006b.res 006c.res
	./joinN.sh 006a.res 006b.res 006c.res > $@

010a.res: $(in)/010.in
	$(program) -e avg -i 2000 -x pmx < $< > $@

010b.res: $(in)/010.in
	$(program) -e avg -i 2000 -x ox < $< > $@

010c.res: $(in)/010.in
	$(program) -e avg -i 2000 -x cx < $< > $@

010.res: 010a.res 010b.res 010c.res
	./joinN.sh 010a.res 010b.res 010c.res > $@

# here list tests which will be converted into graphs

graphs = 010.pdf

# internals of automatic graph creation

graphs: $(graphs)

gnuplot = graph1.gnuplot graph2.gnuplot graph3.gnuplot 
%.pdf: %.res $(gnuplot)
	./plot_graph.sh $< $@

# compilation of presentation

presentation: presentation.pdf
all: presentation.pdf
presentation.pdf: presentation.tex $(graphs)
	pdflatex presentation.tex

# clearing part

clear_presentation:
	rm -f presentation.pdf
	rm -f presentation.aux
	rm -f presentation.log
	rm -f presentation.nav
	rm -f presentation.out
	rm -f presentation.snm
	rm -f presentation.toc

clear_graphs:
	rm -f $(graphs)
clear_tests:
	rm -f *.res

clear: clear_tests clear_graphs clear_presentation

# helper for setting execution permission

used_scripts = count_graphs.sh joinN.sh plot_graph.sh
script_permissions:
	chmod +x $(used_scripts)

