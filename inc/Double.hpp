#ifndef DOUBLE_HPP
#define DOUBLE_HPP

#include "IOperand.hpp"

class Double : IOperand
{
public:
	Double(double value);
	Double(Double const & ref);
	~Double();
	
	double				getValue(void) const;
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
	double const		_value;
	std::string			_str;
};

#endif