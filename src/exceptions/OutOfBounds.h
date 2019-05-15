#include <iostream>
#include <exception>

struct OutOfBounds : public std::exception
{
	const char * what () const noexcept override {
    	return "Out of bounds";
    }
};
