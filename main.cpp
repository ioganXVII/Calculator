#include "parser.h"
#include "lexer.h"
#include "error.h"
#include "table.h"
#include "driver.h"
#include <sstream>
#include <iostream>


int main(int argc, char* argv[]) {
	using namespace std;
	using namespace Driver;

	cout << "You can write your own varibles." << endl;
	cout << "Just write: name_varible = value;" << endl;
	cout << "After this You can use for another calculations" << endl;
	cout << "Available operators is: +, -, *, /, (, ) and ; for end of expression." << endl <<  endl;
	

	switch (argc)
	{
	case 1:
		input = &cin;
		break;
	case 2:
		input = new istringstream(argv[1]);
		break;
	default:
		std::cerr << "too many arguments\n";
		return 1;
	}


	table["pi"] = 3.1415926535897932385;
	table["e"] =  2.7182818284590452354;


	while (*input) {
		try {
			Lexer::get_token();
			if (Lexer::curr_tok == Lexer::END) break;
			if (Lexer::curr_tok == Lexer::PRINT) continue;
			std::cout << Parser::expr(false) << '\n';
		}
		catch (Error::Zero_divide) {
			std::cerr << "attempt to divide by zero\n";
		}
		catch (Error::Syntax_error e) {
			std::cerr << "syntax error:" << e.p << "\n";
			if (Lexer::curr_tok != Lexer::PRINT) skip();
		}
	}

	if (input != &cin) delete input;

	return no_of_errors;
}