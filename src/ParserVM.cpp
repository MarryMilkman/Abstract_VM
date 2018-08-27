#include "ParserVM.hpp"
#include "CommandVM.hpp"

ParserVM::ParserVM(CommandVM *command_vm)
{
	this->_command_vm = command_vm;
	this->_nbr_line = 0;
	this->_error = 0;
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

	fd.open(path_file, std::fstream::in);
	if (fd.is_open())
		while (std::getline(fd, line))
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
			line.clear();
		}
	else
	{
		std::cout << "Error open file: " << path_file
			<< std::endl;
		fd.close();
		exit(0);
	}
	this->_hendl_error();
}

void	ParserVM::iread()
{
	std::string		line;
	std::string		t_line;

	while (std::getline(std::cin, line))
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
	if (command == ";;")
		return (1);
	if (arr_comm[i] == "")
	{
		std::cout << "Pars Error: line "
			<< this->_nbr_line << ": illigal command"
			<< command << std::endl;
		this->_error++;
		return (0);
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
	n_comm.type = 0;
	if ((comm == PUSH || comm == ASSERT) && !str.empty())
	{
		vect = this->_split(str, '(');
		vect[0] == "Int8" ? n_comm.type = INT8 : 0;
		vect[0] == "Int16" ? n_comm.type = INT16 : 0;
		vect[0] == "Int32" ? n_comm.type = INT32 : 0;
		vect[0] == "Float" ? n_comm.type = FLOAT : 0;
		vect[0] == "Double" ? n_comm.type = DOUBLE : 0;
		if (vect.size() > 1)
			vect = this->_split(vect[1], ')');
		n_comm.value = vect[0];
		if (!n_comm.type || !this->_isdigit(vect[0], n_comm.type))
		{
			std::cout << "Pars Error: line "
					<< this->_nbr_line << ": illigaql argument\n";
			this->_error++;
			return ;
		}
	}
	else if ((comm == PUSH || comm == ASSERT))
	{
		std::cout << "Pars Error: line "
				<< this->_nbr_line << ": illigaql argument\n";
		this->_error++;
		return ;
	}
	this->_command_vm->command.push_back(n_comm);
}

// Helpful obj -----------------------



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
	if (str == ";;")
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

	i = -1;
	count_dot = 0;
	while (str[++i])
	{
		if (i > 9)
			return (0);
		if ((str[i] < '0' || str[i] > '9') && str[i] != '.')
			return (0);
		if ((str[i] == '.'
			&& type != FLOAT && type != DOUBLE)
			|| (str[i] == '.' && (count_dot++ || !i)))
		{
			std::cout << str[i] << "---a cacogo baras::\n";
			return (0);
		}
	}
	return (1);
}