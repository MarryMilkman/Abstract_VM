#ifndef CREATOR_HPP
# define CREATOR_HPP

# include "IOperand.hpp"

class Creator
{
public:
	Creator(){}
	~Creator(){}

	class	CreatorException : public std::exception
	{
	public:
		CreatorException() throw();
		CreatorException(CreatorException const & ref) throw();
		CreatorException(eOperandType type) throw();
		~CreatorException() throw();

		virtual const char	*what() const throw();

		Creator::CreatorException	& operator=(Creator::CreatorException const & ref) throw();
		eOperandType		type;
	};

	IOperand const	*createOperand(eOperandType type, std::string const & value) const;
private:
	IOperand const	*_createInt8(std::string const & value) const;
	IOperand const	*_createInt16(std::string const & value) const;
	IOperand const	*_createInt32(std::string const & value) const;
	IOperand const	*_createFloat(std::string const & value) const;
	IOperand const	*_createDouble(std::string const & value) const;
};

#endif