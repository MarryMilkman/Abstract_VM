#include "ParserVM.hpp"
#include "CommandVM.hpp"

ParserVM::ParserVM(CommandVM *command_vm)
{
	this->_command_vm = command_vm;
	this->_nbr_line = 0;
	this->_error = 0;
	this->_countExit = 0;
	this->_isInput = false;
}

ParserVM::~ParserVM()
{
	this->_command_vm = 0;
}

void	ParserVM::fread(char *path_file)
{
	std::fstream	fd;
	std::string		line;
	std::string		t_line;

	try
	{
		fd.open(path_file, std::fstream::in);
		if (!fd.is_open())
			throw ParserVM::ParseException(0, path_file, OPEN_ERROR);
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
		fd.close();
		exit(0);
	}
	while (std::getline(fd, line))
	{
		try
		{
			this->_nbr_line++;
			t_line = this->_check_line(line);
			if (t_line.empty())
			{
				line.clear();
				continue;
			}
			if (this->_hendl_line(t_line))
			{
				line.clear();
				break ;
			}
		}
		catch (std::exception & e)
		{
			std::cerr << e.what() << std::endl;
		}
		line.clear();
	}
	this->_hendl_error();
}

void	ParserVM::iread()
{
	std::string		line;
	std::string		t_line;

	this->_isInput = true;
	while (std::getline(std::cin, line))
	{
		try
		{
			this->_nbr_line++;
			t_line = this->_check_line(line);
			if (t_line.empty())
			{
				line.clear();
				continue;
			}
			if (this->_hendl_line(t_line))
			{
				line.clear();
				break ;
			}
		}
		catch (std::exception & e)
		{
			std::cerr << e.what() << std::endl;
			exit(0);
		}
		line.clear();
	}
	this->_hendl_error();
}

void			ParserVM::_hendl_error()
{
	if (this->_error)
		exit (0);
}

int		ParserVM::_hendl_line(std::string const line)
{
	std::istringstream			iss(line);
	std::string					command;
	std::vector<std::string>	arr_comm = {"push",
	"pop", "dump", "assert", "add", "sub",
	"mul", "div", "mod", "print", "exit", ""};
	int							i = -1;

	iss >> command;
	if (command.empty())
		return (0);
	while (++i < 11)
		if (command == arr_comm[i])
			break ;
	if (command == ";;" && this->_isInput == true)
		return (1);
	if (arr_comm[i] == "")
	{
		this->_error++;
		throw ParserVM::ParseException(this->_nbr_line, 0, PARS_ERROR_COMM);
	}
	command = "";
	if (!iss.eof())
		iss >> command;
	this->_add_command(i, command);
	return (0);
}

void	ParserVM::_add_command(int comm, std::string str)
{
	t_command					n_comm;
	std::vector<std::string>	vect;

	n_comm.comm = comm;
	n_comm.value = "";
	n_comm.type = NIL;
	if (comm != PUSH && comm != ASSERT && str != "")
	{
		this->_error++;
		throw ParserVM::ParseException(this->_nbr_line, 0, PARS_ERROR_COMM);
	}
	if ((comm == PUSH || comm == ASSERT) && !str.empty())
	{
		vect = this->_split(str, '(');
		vect[0] == "int8" ? n_comm.type = INT8 : 0;
		vect[0] == "int16" ? n_comm.type = INT16 : 0;
		vect[0] == "int32" ? n_comm.type = INT32 : 0;
		vect[0] == "float" ? n_comm.type = FLOAT : 0;
		vect[0] == "double" ? n_comm.type = DOUBLE : 0;
		if (vect.size() > 1)
		{
			if (this->_count_c(vect[1], ')') != 1)
			{
				this->_error++;
				throw ParserVM::ParseException(this->_nbr_line, 0, PARS_ERROR_ARG);
			}
			vect = this->_split(vect[1], ')');
		}
		n_comm.value = vect[0];
		if (!n_comm.type || !this->_isdigit(vect[0], n_comm.type))
		{
			this->_error++;
			throw ParserVM::ParseException(this->_nbr_line, 0, PARS_ERROR_ARG);
		}
	}
	else if ((comm == PUSH || comm == ASSERT))
	{
		this->_error++;
		throw ParserVM::ParseException(this->_nbr_line, 0, PARS_ERROR_COMM);
	}
	if (comm == EXIT)
	{
		this->_countExit++;
	}
	this->_command_vm->command.push_back(n_comm);
}

// Exception

ParserVM::ParseException::ParseException() throw()
{
}

ParserVM::ParseException::ParseException(int line, char *file, int type_error) throw() : 
				line(line), file(file), type_error(type_error)
{
}

ParserVM::ParseException::ParseException(ParserVM::ParseException const & ref) throw()
{
	*this = ref;
}

ParserVM::ParseException::~ParseException() throw()
{
}

const char	*ParserVM::ParseException::what() const throw()
{
	std::string		str;

	if (this->type_error == OPEN_ERROR)
	{
		str = file;
		str = "Error: no such file: " + str;
		return (str.c_str());
	}
	if (this->type_error == PARS_ERROR_ARG)
	{
		str = "Line " + std::to_string(this->line) + ": Pars Error: illigal argument";
	}
	if (this->type_error == PARS_ERROR_COMM)
	{
		str = "Line " + std::to_string(this->line) + ": Pars Error: illigal command";
	}
	return (str.c_str());
}

ParserVM::ParseException	& ParserVM::ParseException::operator=(
					ParserVM::ParseException const & ref) throw()
{
	this->type_error = ref.type_error;
	this->file = ref.file;
	this->line = ref.line;
	return (*this);	
}


// Helpful obj -----------------------

int							ParserVM::_count_c(std::string const &str, char c)
{
	size_t i = 0;
	int count = 0;

	while (i < str.size())
	{
		if (str[i++] == c)
			count++;
	}
	return (count);
}

std::vector<std::string>	ParserVM::_split(const std::string& s,
									char delim)
{
	std::stringstream			ss(s);
	std::string					item;
	std::vector<std::string>	elems;

	while (std::getline(ss, item, delim))
		elems.push_back(item);
	return (elems);
}

std::string					ParserVM::_check_line(std::string line)
{
	std::vector<std::string>	vect;
	std::stringstream			ss(line);
	std::string					str;

	ss >> str;
	if (str == ";;" && this->_isInput == true)
		return (str);
	if (line.empty() || (line[0] == ';'))
		return ("");
	vect = this->_split(line, ';');
	return (vect[0]);
}

int							ParserVM::_isdigit(std::string str, int type)
{
	int		i;
	int		count_dot;
	int		count_digit_after_dot;

	i = -1;
	count_dot = 0;
	count_digit_after_dot = 0;
	while (str[++i])
	{
		if (str[i] == '-' && i != 0)
			return (0);
		if ((str[i] < '0' || str[i] > '9') && str[i] != '.' && str[i] != '-')
			return (0);
		count_dot > 0 ? count_digit_after_dot++ : 0;
		if ((str[i] == '.'
				&& type != FLOAT && type != DOUBLE)
				|| (str[i] == '.' && (count_dot++ || !i || (i == 1 && str[0] == '-'))))
			return (0);
	}
	if (i == 0 || (count_digit_after_dot == 0 && count_dot))
		return (0);
	return (1);
}