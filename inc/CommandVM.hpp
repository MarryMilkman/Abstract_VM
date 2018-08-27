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
	~CommandVM();

	void	start();
	std::vector<t_command>	command;
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

	typedef	void(CommandVM::*ComFunc)(t_command &);
	static	ComFunc arr_func[12];
};

#endif