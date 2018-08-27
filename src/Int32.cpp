#include "Int32.hpp"
#include "Creator.hpp"

Int32::Int32(int value) : _type(INT32), _prec(8), _value(value), 
			_str(std::to_string(value))
{
}

Int32::Int32(Int32 const & ref) : _type(ref._type),
			_prec(ref._prec), _value(ref._value), 
			_str(std::to_string(ref._value))
{
}

Int32::~Int32()
{
}

int			Int32::getValue(void) const
{
	return (this->_value);
}

int				Int32::getPrecision(void) const
{
	return (this->_prec);
}

eOperandType	Int32::getType(void) const
{
	return (this->_type);
}

std::string const	& Int32::toString(void) const
{
	return (this->_str);
}

///////// operator

IOperand const * Int32::operator+( IOperand const & rhs ) const
{
	Creator			creator;
	const IOperand	*r_operand;
	std::string		str_value;
	eOperandType	type = this->_type > rhs.getType() ?
						this->_type : rhs.getType();
	double			rhs_value = std::stod(rhs.toString());

	str_value = std::to_string(this->_value + rhs_value);
	r_operand = creator.createOperand(type, str_value);
	return (r_operand);
}

IOperand const * Int32::operator-( IOperand const & rhs ) const
{
	Creator			creator;
	const IOperand	*r_operand;
	std::string		str_value;
	eOperandType	type = this->_type > rhs.getType() ?
						this->_type : rhs.getType();
	double			rhs_value = std::stod(rhs.toString());

	str_value = std::to_string(this->_value - rhs_value);
	r_operand = creator.createOperand(type, str_value);
	return (r_operand);
}

IOperand const * Int32::operator*( IOperand const & rhs ) const
{
	Creator			creator;
	const IOperand	*r_operand;
	std::string		str_value;
	eOperandType	type = this->_type > rhs.getType() ?
						this->_type : rhs.getType();
	double			rhs_value = std::stod(rhs.toString());

	str_value = std::to_string(this->_value * rhs_value);
	r_operand = creator.createOperand(type, str_value);
	return (r_operand);
}

IOperand const * Int32::operator/( IOperand const & rhs ) const
{
	Creator			creator;
	const IOperand	*r_operand;
	std::string		str_value;
	eOperandType	type = this->_type > rhs.getType() ?
						this->_type : rhs.getType();
	double			rhs_value = std::stod(rhs.toString());

	str_value = std::to_string(this->_value / rhs_value);
	r_operand = creator.createOperand(type, str_value);
	return (r_operand);
}

IOperand const * Int32::operator%( IOperand const & rhs ) const
{
	Creator			creator;
	const IOperand	*r_operand;
	std::string		str_value;
	eOperandType	type = this->_type > rhs.getType() ?
						this->_type : rhs.getType();
	int			rhs_value = std::stod(rhs.toString());

	str_value = std::to_string(static_cast<int>(this->_value)
				 % rhs_value);
	r_operand = creator.createOperand(type, str_value);
	return (r_operand);
}