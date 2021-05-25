#pragma once
#ifndef DRIVER_H
#define DRIVER_H


#include <istream>
namespace Driver {
	static int no_of_errors;
	static std::istream* input;
	void skip();
}

#endif