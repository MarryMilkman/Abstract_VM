#include "CommandVM.hpp"
#include "Creator.hpp"

CommandVM::CommandVM()
{
	this->_stack = 0;
}

CommandVM::~CommandVM()
{
	this->_free_stack();
}

void		CommandVM::start()
{
	int		i = -1;

	while (++i < this->command.size())
		(this->*CommandVM::arr_func[this->command[i].comm])(this->command[i]);
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

	operand = creator.createOperand(command.type, command.value);
	this->_add_to_stack(operand);
}

void		CommandVM::_pop(t_command & command)
{
	this->_remove_from_stack();
}

void		CommandVM::_dump(t_command & command)
{
	std::cout << "dump: \n";
	t_stack		*stack = this->_stack;

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

	if (value != stack_value)
	{
		std::cout << "Here mast be exeption: ASSERT error\n";
		this->_free_stack();
		exit(0);
	}
}

void		CommandVM::_add(t_command & command)
{
	if (!this->_stack || !this->_stack->next)
	{
		std::cout << "Here mast be exeption: ADD error\n";
		this->_free_stack();
		exit(0);
	}
	IOperand const	*o1 = this->_stack->operand;
	IOperand const	*o2 = this->_stack->next->operand;
	IOperand const	*r_operand = *o1 + *o2;

	this->_remove_from_stack();
	this->_remove_from_stack();
	this->_add_to_stack(r_operand);
}

void		CommandVM::_sub(t_command & command)
{
	if (!this->_stack || !this->_stack->next)
	{
		std::cout << "Here mast be exeption: SUB error\n";
		this->_free_stack();
		exit(0);
	}
	IOperand const	*o1 = this->_stack->operand;
	IOperand const	*o2 = this->_stack->next->operand;
	IOperand const	*r_operand = *o1 - *o2;

	this->_remove_from_stack();
	this->_remove_from_stack();
	this->_add_to_stack(r_operand);
}

void		CommandVM::_mul(t_command & command)
{
	if (!this->_stack || !this->_stack->next)
	{
		std::cout << "Here mast be exeption: MUL error\n";
		this->_free_stack();
		exit(0);
	}
	IOperand const	*o1 = this->_stack->operand;
	IOperand const	*o2 = this->_stack->next->operand;
	IOperand const	*r_operand = *o1 * *o2;

	this->_remove_from_stack();
	this->_remove_from_stack();
	this->_add_to_stack(r_operand);
}

void		CommandVM::_div(t_command & command)
{
	if (!this->_stack || !this->_stack->next)
	{
		std::cout << "Here mast be exeption: DIV error\n";
		this->_free_stack();
		exit(0);
	}
	IOperand const	*o1 = this->_stack->operand;
	IOperand const	*o2 = this->_stack->next->operand;
	IOperand const	*r_operand = *o1 / *o2;

	this->_remove_from_stack();
	this->_remove_from_stack();
	this->_add_to_stack(r_operand);
}

void		CommandVM::_mod(t_command & command)
{
	if (!this->_stack || !this->_stack->next)
	{
		std::cout << "Here mast be exeption: MOD error\n";
		this->_free_stack();
		exit(0);
	}
	IOperand const	*o1 = this->_stack->operand;
	IOperand const	*o2 = this->_stack->next->operand;
	IOperand const	*r_operand = *o1 % *o2;

	this->_remove_from_stack();
	this->_remove_from_stack();
	this->_add_to_stack(r_operand);
}

void		CommandVM::_print(t_command & command)
{
	if (!this->_stack || this->_stack->operand->getType() != INT8)
	{
		std::cout << "Here mast be exeption: PRINT error\n";
		this->_free_stack();
		exit(0);
	}
	char	c = static_cast<char>(std::stoi(this->_stack->operand->toString()));
	std::cout << c << "\n";
}

void		CommandVM::_exit(t_command & command)
{
	this->_free_stack();
	exit(0);
}

CommandVM::ComFunc CommandVM::arr_func[12] = {CommandVM::_push, CommandVM::_pop,
		CommandVM::_dump, CommandVM::_assert, CommandVM::_add, CommandVM::_sub,
		CommandVM::_mul, CommandVM::_div, CommandVM::_mod,
		CommandVM::_print, CommandVM::_exit};
		
