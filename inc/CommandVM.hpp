#ifndef COMMAND_V_M_HPP
# define COMMAND_V_M_HPP

#include "avm.h"
#include "IOperand.hpp"
#include "Int8.hpp"
#include "Int16.hpp"
#include "Int32.hpp"
#include "Float.hpp"
#include "Double.hpp"

typedef struct 		s_stack
{
	IOperand const	*operand;
	struct s_stack	*next;
}					t_stack;

class CommandVM
{
public:
	CommandVM();
	CommandVM(CommandVM const & ref);
	~CommandVM();

	void					start();
	std::vector<t_command>	command;

	t_stack					*get_stack() const;

	CommandVM				& operator=(CommandVM const & ref);

	class	CommandException : public std::exception
	{
	public:
		CommandException() throw();
		CommandException(CommandException const & ref) throw();
		CommandException(int comm) throw();
		~CommandException() throw();

		virtual const char			*what() const throw();

		int							comm;
	
		CommandVM::CommandException	& operator=(CommandVM::CommandException const & ref) throw ();
	};

private:
	t_stack	*_stack;
	void	_add_to_stack(IOperand const *operand);
	void	_remove_from_stack();
	void	_free_stack();

	void	_push(t_command & command);
	void	_pop(t_command & command);
	void	_dump(t_command & command);
	void	_assert(t_command & command);
	void	_add(t_command & command);
	void	_sub(t_command & command);
	void	_mul(t_command & command);
	void	_div(t_command & command);
	void	_mod(t_command & command);
	void	_print(t_command & command);
	void	_exit(t_command & command);
};

#endif