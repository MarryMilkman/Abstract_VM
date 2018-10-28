#include "Creator.hpp"
#include "Int8.hpp"
#include "Int16.hpp"
#include "Int32.hpp"
#include "Float.hpp"
#include "Double.hpp"

IOperand const	*Creator::createOperand(eOperandType type, std::string const & value) const
{
	try
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
	catch (std::exception & e)
	{
		std::cerr << e.what() << "\n";
		exit(0);
	}
}

IOperand const	*Creator::_createInt8(std::string const & value) const
{
	Int8		*operand;
	long long	num;

	try
	{
		num = std::stoll(value);
	}
	catch (std::exception & e)
	{
		std::cerr << "Error: overflow Int8\n";
		exit(0);
	}
	if (num > 127 || num < -128)
		throw Creator::CreatorException(INT8);
	operand = new Int8(static_cast<char>(num));
	return (reinterpret_cast<IOperand *>(operand));
}

IOperand const	*Creator::_createInt16(std::string const & value) const
{
	Int16	*operand;
	long long	num;

	try
	{
		num = std::stoll(value);
	}
	catch (std::exception & e)
	{
		std::cerr << "Error: overflow Int16\n";
		exit(0);
	}
	if (num > 32767 || num < -32768)
		throw Creator::CreatorException(INT16);
	operand = new Int16(static_cast<short>(num));
	return (reinterpret_cast<IOperand *>(operand));
}

IOperand const	*Creator::_createInt32(std::string const & value) const
{
	Int32	*operand;
	long long	num;

	try
	{
		num = std::stoll(value);
	}
	catch (std::exception & e)
	{
		std::cerr << "Error: overflow Int32\n";
		exit(0);
	}
	if (num > 2147483647 || num < -2147483648)
		throw Creator::CreatorException(INT32);
	operand = new Int32(static_cast<int>(num));
	return (reinterpret_cast<IOperand *>(operand));
}

IOperand const	*Creator::_createFloat(std::string const & value) const
{
	Float	*operand;

	try 
	{
		operand = new Float((std::stof(value)));
	}
	catch (std::exception & e)
	{
		std::cerr << "Error: overflow Float\n";
		exit(0);
	}
	return (reinterpret_cast<IOperand *>(operand));
}

IOperand const	*Creator::_createDouble(std::string const & value) const
{
	Double	*operand;

	try
	{
		operand = new Double((std::stod(value)));
	}
	catch (std::exception & e)
	{
		std::cerr << "Error: overflow Double\n";
		exit(0);
	}
	return (reinterpret_cast<IOperand *>(operand));
}

// Exception

Creator::CreatorException::CreatorException() throw()
{
}

Creator::CreatorException::CreatorException(eOperandType type) throw() : type(type)
{
}

Creator::CreatorException::CreatorException(Creator::CreatorException const & ref) throw()
{
	*this=ref;
}

Creator::CreatorException::~CreatorException() throw()
{	
}

const char	*Creator::CreatorException::what() const throw()
{
	if (this->type == INT8)
		return ("Error: overflow Int8");
	if (this->type == INT16)
		return ("Error: overflow Int16");
	if (this->type == INT32)
		return ("Error: overflow Int32");
	return ("Error");
}

Creator::CreatorException	& Creator::CreatorException::operator=(Creator::CreatorException const & ref) throw()
{
	this->type = ref.type;
	return (*this);
}