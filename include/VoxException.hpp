#pragma once

#include <exception>
#include <iostream>

class 	VoxException : public std::exception
{
	public:
		VoxException() {}
		VoxException(std::string error) : _error(error) {}
		virtual ~VoxException() throw() {}
		virtual const char *what() const throw ()
		{
			return _error.c_str();
		}
	private:
		std::string	_error;
};
