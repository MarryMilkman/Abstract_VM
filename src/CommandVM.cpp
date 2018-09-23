#include "CommandVM.hpp"
#include "Creator.hpp"

CommandVM::CommandVM()
{
	this->_stack = 0;
}

CommandVM::CommandVM(CommandVM const & ref)
{
	*this = ref;
}

CommandVM::~CommandVM()
{
	this->_free_stack();
}

void		CommandVM::start()
{
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
			this->_free_stack();
			exit(0);
		}
	}
}

t_stack		*CommandVM::get_stack() const
{
	return (this->_stack);
}

// Work with stack	-------------------------

void		CommandVM::_add_to_stack(IOperand const *operand)
{
	t_stack	*n_stack;

	n_stack = new t_stack;
	n_stack->operand = operand;
	n_stack->next = 0;
	if (!this->_stack)
		this->_stack = n_stack;
	else
	{
		n_stack->next = this->_stack;
		this->_stack = n_stack;
	}
}

void		CommandVM::_remove_from_stack()
{
	t_stack		*d_stack;

	if (!(d_stack = this->_stack))
		return ;
	this->_stack = this->_stack->next;
	delete d_stack->operand;
	delete d_stack;
}

void		CommandVM::_free_stack()
{
	t_stack		*d_stack;

	while ((d_stack = this->_stack))
	{
		this->_stack = this->_stack->next;
		delete d_stack;
	}
}

// Command 			-------------------------

void		CommandVM::_push(t_command & command)
{
	IOperand const	*operand;
	Creator			creator;

	if (command.comm != PUSH)
		return ;
	operand = creator.createOperand(command.type, command.value);
	this->_add_to_stack(operand);
}

void		CommandVM::_pop(t_command & command)
{
	t_stack		*stack = this->_stack;

	if (command.comm != POP)
		return ;
	if (!stack)
		throw CommandVM::CommandException(command.comm);
	this->_remove_from_stack();
}

void		CommandVM::_dump(t_command & command)
{
	std::cout << "dump:\n";
	t_stack		*stack = this->_stack;

	if (command.comm != DUMP)
		return ;
	if (!stack)
		std::cout << "Warning: stack is empty\n";
	while (stack)
	{
		std::cout << stack->operand->toString() << std::endl;
		stack = stack->next;
	}
}

void		CommandVM::_assert(t_command & command)
{
	double	value = std::stod(command.value);
	double	stack_value = std::stod(this->_stack->operand->toString());

	if (command.comm != ASSERT)
		return ;
	if (value != stack_value)
		throw CommandVM::CommandException(command.comm);
}

void		CommandVM::_add(t_command & command)
{
	if (command.comm != ADD)
		return ;
	if (!this->_stack || !this->_stack->next)
		throw CommandVM::CommandException(command.comm);
	IOperand const	*o1 = this->_stack->operand;
	IOperand const	*o2 = this->_stack->next->operand;
	IOperand const	*r_operand = *o1 + *o2;

	this->_remove_from_stack();
	this->_remove_from_stack();
	this->_add_to_stack(r_operand);
}

void		CommandVM::_sub(t_command & command)
{
	if (command.comm != SUB)
		return ;
	if (!this->_stack || !this->_stack->next)
		throw CommandVM::CommandException(command.comm);
	IOperand const	*o1 = this->_stack->operand;
	IOperand const	*o2 = this->_stack->next->operand;
	IOperand const	*r_operand = *o1 - *o2;

	this->_remove_from_stack();
	this->_remove_from_stack();
	this->_add_to_stack(r_operand);
}

void		CommandVM::_mul(t_command & command)
{
	if (command.comm != MUL)
		return ;
	if (!this->_stack || !this->_stack->next)
		throw CommandVM::CommandException(command.comm);
	IOperand const	*o1 = this->_stack->operand;
	IOperand const	*o2 = this->_stack->next->operand;
	IOperand const	*r_operand = *o1 * *o2;

	this->_remove_from_stack();
	this->_remove_from_stack();
	this->_add_to_stack(r_operand);
}

void		CommandVM::_div(t_command & command)
{
	if (command.comm != DIV)
		return ;
	if (!this->_stack || !this->_stack->next)
		throw CommandVM::CommandException(command.comm);
	IOperand const	*o1 = this->_stack->operand;
	IOperand const	*o2 = this->_stack->next->operand;
	if (std::stod(o2->toString()) == 0)
		throw CommandVM::CommandException(DIV_BY_ZERO);
	IOperand const	*r_operand = *o1 / *o2;

	this->_remove_from_stack();
	this->_remove_from_stack();
	this->_add_to_stack(r_operand);
}

void		CommandVM::_mod(t_command & command)
{
	if (command.comm != MOD)
		return ;
	if (!this->_stack || !this->_stack->next)
		throw CommandVM::CommandException(command.comm);
	IOperand const	*o1 = this->_stack->operand;
	IOperand const	*o2 = this->_stack->next->operand;
	if (std::stod(o2->toString()) == 0)
		throw CommandVM::CommandException(MOD_BY_ZERO);
	IOperand const	*r_operand = *o1 % *o2;

	this->_remove_from_stack();
	this->_remove_from_stack();
	this->_add_to_stack(r_operand);
}

void		CommandVM::_print(t_command & command)
{
	if (command.comm != PRINT)
		return ;
	if (!this->_stack || this->_stack->operand->getType() != INT8)
		throw CommandVM::CommandException(command.comm);
	char	c = static_cast<char>(std::stoi(this->_stack->operand->toString()));
	std::cout << c << "\n";
}

void		CommandVM::_exit(t_command & command)
{
	if (command.comm != EXIT)
		return ;
	this->_free_stack();
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
	return ("Error");
}

CommandVM::CommandException	& CommandVM::CommandException::operator=(CommandVM::CommandException const & ref) throw ()
{
	this->comm = ref.comm;
	return *this;
}

// Operator

CommandVM			& CommandVM::operator=(CommandVM const & ref)
{
	this->_stack = ref.get_stack();
	this->command = ref.command;
	return (*this);
}
