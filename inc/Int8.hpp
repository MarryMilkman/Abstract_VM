#ifndef INT8_HPP
# define INT8_HPP

#include "IOperand.hpp"

class Int8 : IOperand
{
public:
	Int8(char value);
	Int8(Int8 const & ref);
	~Int8();
	
	char				getValue(void) const;
	int					getPrecision(void) const override;
	eOperandType		getType(void) const override;
	std::string const	& toString(void) const override;
	
	IOperand const 		*operator+(IOperand const & rhs) const override;
	IOperand const 		*operator-(IOperand const & rhs) const override;
	IOperand const 		*operator*(IOperand const & rhs) const override;
	IOperand const 		*operator/(IOperand const & rhs) const override;
	IOperand const 		*operator%(IOperand const & rhs) const override;

private:
	eOperandType const	_type;
	int const			_prec;
	char const			_value;
	std::string			_str;
};

#endif