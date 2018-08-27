#ifndef AVM_H
# define AVM_H

# include <iterator>
# include <vector>
# include <iostream>
# include <fstream>
# include <sstream>
# include <algorithm>
# include <stdlib.h> 

// command
# define PUSH 0
# define POP 1
# define DUMP 2
# define ASSERT 3
# define ADD 4
# define SUB 5
# define MUL 6
# define DIV 7
# define MOD 8
# define PRINT 9
# define EXIT 10

// enum
# define INT8 1
# define INT16 2
# define INT32 3
# define FLOAT 4
# define DOUBLE 5


typedef int eOperandType;

typedef struct 			s_commad
{
	int					comm;
	eOperandType		type;
	std::string			value;
}						t_command;

#endif