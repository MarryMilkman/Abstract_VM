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



// class Virt
// {
// public:
// 	Virt() {}
// 	~Virt() {}
	
// 	virtual int zorro(std::string str) const = 0;
// };

// class Child : Virt
// {
// public:
// 	Child() {}
// 	~Child() {}

// 	zorro(std::string str) const override;
// };

// int Child::zorro(std::string str) const
// {
// 	std::cout << str << std::endl;
// 	return (1);
// }

// Virt * tst(void)
// {
// 	Child *test = new Child();

// 	return((Virt *)test);
// }