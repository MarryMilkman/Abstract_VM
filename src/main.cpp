#include "avm.h"

#include "CommandVM.hpp"
#include "ParserVM.hpp"

int main(int ac, char **av)  
{
	CommandVM		command_vm;
	ParserVM		parser_vm(&command_vm);

	if (ac > 1)
		parser_vm.fread(av[1]);
	else
		parser_vm.iread();
	command_vm.start();
	return (0);
}
