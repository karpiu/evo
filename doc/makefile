output = presentation.pdf

tests = 001.res 002.res 003.res

001.res:
	../src/evo.e -r < ../in/001.in > 001.res

002.res:
	../src/evo.e -r < ../in/002.in > 002.res

003.res:
	../src/evo.e -r < ../in/003.in > 003.res

all: $(output)

$(output): presentation.tex $(tests)
	pdflatex presentation.tex

tests: $(tests)
clear_tests:
	rm $(tests)

clear:
	rm $(output) presentation.aux presentation.log presentation.nav presentation.out presentation.snm presentation.toc
