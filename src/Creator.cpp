#include "Creator.hpp"
#include "Int8.hpp"
#include "Int16.hpp"
#include "Int32.hpp"
#include "Float.hpp"
#include "Double.hpp"

IOperand const	*Creator::createOperand(eOperandType type, std::string const & value) const
{
	if (type == INT8)
		return (this->_createInt8(value));
	if (type == INT16)
		return (this->_createInt16(value));
	if (type == INT32)
		return (this->_createInt32(value));
	if (type == FLOAT)
		return (this->_createFloat(value));
	else
		return (this->_createDouble(value));
}

IOperand const	*Creator::_createInt8(std::string const & value) const
{
	Int8	*operand;

	operand = new Int8(static_cast<char>(std::stoi(value)));
	return (reinterpret_cast<IOperand *>(operand));
}

IOperand const	*Creator::_createInt16(std::string const & value) const
{
	Int16	*operand;

	operand = new Int16(static_cast<short>(std::stoi(value)));
	return (reinterpret_cast<IOperand *>(operand));
}

IOperand const	*Creator::_createInt32(std::string const & value) const
{
	Int32	*operand;

	operand = new Int32((std::stoi(value)));
	return (reinterpret_cast<IOperand *>(operand));
}

IOperand const	*Creator::_createFloat(std::string const & value) const
{
	Float	*operand;

	operand = new Float((std::stof(value)));
	return (reinterpret_cast<IOperand *>(operand));
}

IOperand const	*Creator::_createDouble(std::string const & value) const
{
	Double	*operand;

	operand = new Double((std::stod(value)));
	return (reinterpret_cast<IOperand *>(operand));
}

