#include "Double.hpp"
#include "Creator.hpp"

Double::Double(double value) : _type(DOUBLE), _prec(8), _value(value), 
			_str(std::to_string(value))
{
}

Double::Double(Double const & ref) : _type(ref._type),
			_prec(ref._prec), _value(ref._value), 
			_str(std::to_string(ref._value))
{
}

Double::~Double()
{
}

double			Double::getValue(void) const
{
	return (this->_value);
}

int				Double::getPrecision(void) const
{
	return (this->_prec);
}

eOperandType	Double::getType(void) const
{
	return (this->_type);
}

std::string const	& Double::toString(void) const
{
	return (this->_str);
}

///////// operator

IOperand const * Double::operator+( IOperand const & rhs ) const
{
	Creator			creator;
	const IOperand	*r_operand;
	std::string		str_value;
	eOperandType	type = this->_type > rhs.getType() ?
						this->_type : rhs.getType();
	double			rhs_value;

	try
	{
		rhs_value = std::stod(rhs.toString());
	}
	catch (std::exception & e)
	{
		std::cerr << "Error: overflow Double";
		exit(0);
	}
	str_value = std::to_string(this->_value + rhs_value);
	r_operand = creator.createOperand(type, str_value);
	return (r_operand);
}

IOperand const * Double::operator-( IOperand const & rhs ) const
{
	Creator			creator;
	const IOperand	*r_operand;
	std::string		str_value;
	eOperandType	type = this->_type > rhs.getType() ?
						this->_type : rhs.getType();
	double			rhs_value;

	try
	{
		rhs_value = std::stod(rhs.toString());
	}
	catch (std::exception & e)
	{
		std::cerr << "Error: overflow Double";
		exit(0);
	}
	str_value = std::to_string(rhs_value - this->_value);
	r_operand = creator.createOperand(type, str_value);
	return (r_operand);
}

IOperand const * Double::operator*( IOperand const & rhs ) const
{
	Creator			creator;
	const IOperand	*r_operand;
	std::string		str_value;
	eOperandType	type = this->_type > rhs.getType() ?
						this->_type : rhs.getType();
	double			rhs_value;

	try
	{
		rhs_value = std::stod(rhs.toString());
	}
	catch (std::exception & e)
	{
		std::cerr << "Error: overflow Double";
		exit(0);
	}
	str_value = std::to_string(this->_value * rhs_value);
	r_operand = creator.createOperand(type, str_value);
	return (r_operand);
}

IOperand const * Double::operator/( IOperand const & rhs ) const
{
	Creator			creator;
	const IOperand	*r_operand;
	std::string		str_value;
	eOperandType	type = this->_type > rhs.getType() ?
						this->_type : rhs.getType();
	double			rhs_value;

	try
	{
		rhs_value = std::stod(rhs.toString());
	}
	catch (std::exception & e)
	{
		std::cerr << "Error: overflow Double";
		exit(0);
	}
	str_value = std::to_string(rhs_value / this->_value);
	r_operand = creator.createOperand(type, str_value);
	return (r_operand);
}

IOperand const * Double::operator%( IOperand const & rhs ) const
{
	Creator			creator;
	const IOperand	*r_operand;
	std::string		str_value;
	eOperandType	type = this->_type > rhs.getType() ?
						this->_type : rhs.getType();
	double			rhs_value;
	double			result;

	try
	{
		rhs_value = std::stod(rhs.toString());
	}
	catch (std::exception & e)
	{
		std::cerr << "Error: overflow Double";
		exit(0);
	}
	result = std::fmod(rhs_value, static_cast<double>(this->_value));
	str_value = std::to_string(result);
	r_operand = creator.createOperand(type, str_value);
	return (r_operand);
}