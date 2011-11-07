error_flags = -Wall -Werror
std_flag = -std=c++0x
compiler = g++-4.4

modules =

output = evo.e

all: $(output)

$(output): main.cpp $(modules)
	$(compiler) $(error_flags) $(std_flag) $? -o $@

clear:
	rm $(output) $(modules)