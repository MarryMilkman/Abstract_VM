#ifndef FLOAT_HPP
#define FLOAT_HPP

#include "IOperand.hpp"

class Float : IOperand
{
public:
	Float(float value);
	Float(Float const & ref);
	~Float();
	
	float				getValue(void) const;
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
	float const			_value;
	std::string			_str;
};

#endif