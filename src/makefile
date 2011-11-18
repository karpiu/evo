error_flags = -Wall -Werror
std_flag = -std=c++0x
compiler = g++-4.4

modules = random.o permutation.o mutation.o crossover.o sga.o

out = evo.e

all: $(out)

random.o: random.cpp random.hpp
	$(compiler) $(error_flags) $(std_flag) -c random.cpp -o random.o

permutation.o: permutation.cpp permutation.hpp
	$(compiler) $(error_flags) $(std_flag) -c permutation.cpp -o permutation.o

mutation.o: mutation.cpp mutation.hpp
	$(compiler) $(error_flags) $(std_flag) -c mutation.cpp -o mutation.o

crossover.o: crossover.cpp crossover.hpp
	$(compiler) $(error_flags) $(std_flag) -c crossover.cpp -o crossover.o

sga.o: sga.cpp sga.hpp
	$(compiler) $(error_flags) $(std_flag) -c sga.cpp -o sga.o

evo.e: main.cpp $(modules)
	$(compiler) $(error_flags) $(std_flag) main.cpp $(modules) -o evo.e

clear:
	rm $(out) $(modules)