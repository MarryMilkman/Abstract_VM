#ifndef INT16_HPP
# define INT16_HPP

# include "IOperand.hpp"

class Int16 : IOperand
{
public:
	Int16(short value);
	Int16(Int16 const & ref);
	~Int16();
	
	short				getValue(void) const;
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
	short const			_value;
	std::string			_str;
};

#endif