#include "Int8.hpp"
#include "Creator.hpp"

Int8::Int8(char value) : _type(INT8), _prec(8), _value(value), 
			_str(std::to_string(value))
{
}

Int8::Int8(Int8 const & ref) : _type(ref._type),
			_prec(ref._prec), _value(ref._value), 
			_str(std::to_string(ref._value))
{
}

Int8::~Int8()
{
}

char			Int8::getValue(void) const
{
	return (this->_value);
}

int				Int8::getPrecision(void) const
{
	return (this->_prec);
}

eOperandType	Int8::getType(void) const
{
	return (this->_type);
}

std::string const	& Int8::toString(void) const
{
	return (this->_str);
}

///////// operator

IOperand const * Int8::operator+( IOperand const & rhs ) const
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

IOperand const * Int8::operator-( IOperand const & rhs ) const
{
	Creator			creator;
	const IOperand	*r_operand;
	std::string		str_value;
	eOperandType	type = this->_type > rhs.getType() ?
						this->_type : rhs.getType();
	double			rhs_value = std::stod(rhs.toString());

	str_value = std::to_string(rhs_value - this->_value);
	r_operand = creator.createOperand(type, str_value);
	return (r_operand);
}

IOperand const * Int8::operator*( IOperand const & rhs ) const
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

IOperand const * Int8::operator/( IOperand const & rhs ) const
{
	Creator			creator;
	const IOperand	*r_operand;
	std::string		str_value;
	eOperandType	type = this->_type > rhs.getType() ?
						this->_type : rhs.getType();
	double			rhs_value = std::stod(rhs.toString());

	str_value = std::to_string(rhs_value / this->_value);
	r_operand = creator.createOperand(type, str_value);
	return (r_operand);
}

IOperand const * Int8::operator%( IOperand const & rhs ) const
{
	Creator			creator;
	const IOperand	*r_operand;
	std::string		str_value;
	eOperandType	type = this->_type > rhs.getType() ?
						this->_type : rhs.getType();
	double			rhs_value = std::stod(rhs.toString());
	double			result;

	result = std::fmod(rhs_value, static_cast<double>(this->_value));
	str_value = std::to_string(result);
	r_operand = creator.createOperand(type, str_value);
	return (r_operand);
}