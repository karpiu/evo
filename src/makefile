error_flags = -Wall -Werror
std_flag = -std=c++0x
compiler = g++-4.4

modules = random.o permutation.o

output = evo.e

all: $(output)

random.o: random.cpp random.hpp
	$(compiler) $(error_flags) $(std_flag) -c random.cpp

permutation.o: permutation.cpp permutation.hpp
	$(compiler) $(error_flags) $(std_flag) -c permutation.cpp

$(output): main.cpp $(modules)
	$(compiler) $(error_flags) $(std_flag) $? -o $@

clear:
	rm $(output) $(modules)