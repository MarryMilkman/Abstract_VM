#ifndef AVM_H
# define AVM_H

# include <iterator>
# include <vector>
# include <iostream>
# include <fstream>
# include <sstream>
# include <algorithm>
# include <stdlib.h> 
# include <cmath>
# include <stack>

// Error messeges

# define DIV_BY_ZERO -1
# define MOD_BY_ZERO -2
# define OPEN_ERROR -3
# define PARS_ERROR_ARG -4
# define PARS_ERROR_COMM -5
# define PARS_ERROR_NO_EXIT -6
# define ERROR_NO_EXIT -7

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

enum eOperandType
{
	NIL = 0,
	INT8,
	INT16,
	INT32,
	FLOAT,
	DOUBLE
};

typedef eOperandType eOperandType;

typedef struct 			s_command
{
	int					comm;
	eOperandType		type;
	std::string			value;
}						t_command;

#endif