#include "CommandVM.hpp"
#include "Creator.hpp"

CommandVM::CommandVM()
{
	this->_operandStack = std::stack<IOperand const *>();
}

CommandVM::CommandVM(CommandVM const & ref)
{
	*this = ref;
}

CommandVM::~CommandVM()
{
}

void		CommandVM::start()
{
	std::cout << "AVM: v1.0\n";
	size_t	i = -1;
	void (CommandVM::*arr_func[12])(t_command &) = 
	{
		&CommandVM::_push,
		&CommandVM::_pop,
		&CommandVM::_dump,
		&CommandVM::_assert,
		&CommandVM::_add,
		&CommandVM::_sub,
		&CommandVM::_mul,
		&CommandVM::_div,
		&CommandVM::_mod,
		&CommandVM::_print,
		&CommandVM::_exit
	};

	while (++i < this->command.size())
	{
		try
		{
			(this->*arr_func[this->command[i].comm])(this->command[i]);
		}
		catch (std::exception & e)
		{
			std::cerr << e.what() << "\n";
			exit(0);
		}
	}
	try
	{
		throw CommandVM::CommandException(ERROR_NO_EXIT);
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
}

std::stack<IOperand const *>	CommandVM::get_operandStack() const
{
	return (this->_operandStack);
}

// Command 			-------------------------

void		CommandVM::_push(t_command & command)
{
	IOperand const	*operand;
	Creator			creator;

	if (command.comm != PUSH)
		return ;
	operand = creator.createOperand(command.type, command.value);
	this->_operandStack.push(operand);
}

void		CommandVM::_pop(t_command & command)
{
	if (command.comm != POP)
		return ;
	if (!this->_operandStack.size())
		throw CommandVM::CommandException(command.comm);
	this->_operandStack.pop();
}

void		CommandVM::_dump(t_command & command)
{
	std::stack<IOperand const *>	dumpStack = this->_operandStack;

	std::cout << "dump:\n";
	if (command.comm != DUMP)
		return ;
	if (!this->_operandStack.size())
		std::cout << "Warning: stack is empty\n";
	while(dumpStack.size())
	{
		std::cout << dumpStack.top()->toString() << std::endl;
		dumpStack.pop();
	}
}

void		CommandVM::_assert(t_command & command)
{
	double	value = std::stod(command.value);
	double	stack_value = std::stod(this->_operandStack.top()->toString());
	if (command.comm != ASSERT)
		return ;
	if (value != stack_value || this->_operandStack.top()->getType() != command.type)
		throw CommandVM::CommandException(command.comm);	
}

void		CommandVM::_add(t_command & command)
{
	if (command.comm != ADD)
		return ;
	if (this->_operandStack.size() < 2)
		throw CommandVM::CommandException(command.comm);
	IOperand const	*o1 = this->_operandStack.top();
	this->_operandStack.pop();
	IOperand const	*o2 = this->_operandStack.top();
	this->_operandStack.pop();
	IOperand const	*r_operand = *o1 + *o2;

	this->_operandStack.push(r_operand);
}

void		CommandVM::_sub(t_command & command)
{
	if (command.comm != SUB)
		return ;
	if (this->_operandStack.size() < 2)
		throw CommandVM::CommandException(command.comm);
	IOperand const	*o1 = this->_operandStack.top();
	this->_operandStack.pop();
	IOperand const	*o2 = this->_operandStack.top();
	this->_operandStack.pop();
	IOperand const	*r_operand = *o1 - *o2;

	this->_operandStack.push(r_operand);
}

void		CommandVM::_mul(t_command & command)
{
	if (command.comm != MUL)
		return ;
	if (this->_operandStack.size() < 2)
		throw CommandVM::CommandException(command.comm);
	IOperand const	*o1 = this->_operandStack.top();
	this->_operandStack.pop();
	IOperand const	*o2 = this->_operandStack.top();
	this->_operandStack.pop();
	IOperand const	*r_operand = *o1 * *o2;

	this->_operandStack.push(r_operand);
}

void		CommandVM::_div(t_command & command)
{
	if (command.comm != DIV)
		return ;
	if (this->_operandStack.size() < 2)
		throw CommandVM::CommandException(command.comm);
	IOperand const	*o1 = this->_operandStack.top();
	this->_operandStack.pop();
	IOperand const	*o2 = this->_operandStack.top();
	this->_operandStack.pop();
	if (std::stod(o1->toString()) == 0)
		throw CommandVM::CommandException(DIV_BY_ZERO);
	IOperand const	*r_operand = *o1 / *o2;

	this->_operandStack.push(r_operand);
}

void		CommandVM::_mod(t_command & command)
{
	if (command.comm != MOD)
		return ;
	if (this->_operandStack.size() < 2)
		throw CommandVM::CommandException(command.comm);
	IOperand const	*o1 = this->_operandStack.top();
	this->_operandStack.pop();
	IOperand const	*o2 = this->_operandStack.top();
	this->_operandStack.pop();
	if (std::stod(o1->toString()) == 0)
		throw CommandVM::CommandException(MOD_BY_ZERO);
	IOperand const	*r_operand = *o1 % *o2;

	this->_operandStack.push(r_operand);
}

void		CommandVM::_print(t_command & command)
{
	if (command.comm != PRINT)
		return ;
	if (!this->_operandStack.size() || this->_operandStack.top()->getType() != INT8)
		throw CommandVM::CommandException(command.comm);
	char	c = static_cast<char>(std::stoi(this->_operandStack.top()->toString()));
	std::cout << c << "\n";
}

void		CommandVM::_exit(t_command & command)
{
	if (command.comm != EXIT)
		return ;
	exit(0);
}

// Exeption

CommandVM::CommandException::CommandException() throw()
{
}

CommandVM::CommandException::CommandException(CommandException const & ref) throw()
{
	*this = ref;
}

CommandVM::CommandException::CommandException(int comm) throw() : comm(comm)
{	
}

CommandVM::CommandException::~CommandException() throw()
{
}

const char*	CommandVM::CommandException::what() const throw()
{
	if (this->comm == PRINT)
		return ("Error: print");
	if (this->comm == MOD)
		return ("Error: mod");
	if (this->comm == DIV)
		return ("Error: div");
	if (this->comm == MUL)
		return ("Error: mul");
	if (this->comm == SUB)
		return ("Error: sub");
	if (this->comm == ADD)
		return ("Error: add");
	if (this->comm == ASSERT)
		return ("Error: assert");
	if (this->comm == POP)
		return ("Error: pop");
	if (this->comm == DIV_BY_ZERO)
		return ("Error: div by zero is not supported");
	if (this->comm == MOD_BY_ZERO)
		return ("Error: mod by zero is not supported");
	if (this->comm == ERROR_NO_EXIT)
		return ("Error: no exit command");
	return ("Error");
}

CommandVM::CommandException	& CommandVM::CommandException::operator=(
	CommandVM::CommandException const & ref) throw ()
{
	this->comm = ref.comm;
	return *this;
}

// Operator

CommandVM			& CommandVM::operator=(CommandVM const & ref)
{
	this->_operandStack = ref.get_operandStack();
	this->command = ref.command;
	return (*this);
}
