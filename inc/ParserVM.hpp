#ifndef PARSER_V_M_HPP
# define PARSER_V_M_HPP

# include "avm.h"
# include "CommandVM.hpp"

class ParserVM
{
public:
	ParserVM(CommandVM *command_vm);
	~ParserVM();

	void	fread(char *path_file);
	void	iread();


private:
	int 		_hendl_line(std::string line);
	void		_add_command(int command, std::string str_val);
	void		_hendl_error();

	CommandVM	*_command_vm;
	int			_nbr_line;
	int			_error;

	std::vector<std::string>	_split(const std::string& s,
			char delim);
	std::string					_check_line(std::string line);
	int							_isdigit(std::string str, int type);
};

#endif
