#ifndef INT32_HPP
#define INT32_HPP

#include "IOperand.hpp"

class Int32 : IOperand
{
public:
	Int32(int value);
	Int32(Int32 const & ref);
	~Int32();
	
	int				getValue(void) const;
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
	int const			_value;
	std::string			_str;
};

#endif