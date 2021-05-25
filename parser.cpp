#include "parser_impl.h"
#include "table.h"


namespace Parser {
	double prim(bool get) {
		if (get)get_token();
		switch (curr_tok) {
		case Lexer::NUMBER: {
			double v = Lexer::number_value;
			get_token();
			return v;
		}
		case Lexer::NAME: {
			double& v = table[Lexer::string_value];
			if (get_token() == Lexer::ASSIGN) v = expr(true);
			return v;
		}
		case Lexer::MINUS: {
			return -prim(true);
		}
		case Lexer::LP: {
			double e = expr(true);
			if (curr_tok != Lexer::RP) throw Error::Syntax_error("')' expected");
			get_token();
			return e;
		}
		case Lexer::END:
			return 1;
		default:
			throw Error::Syntax_error("primary expected");
		}

	}


	double term(bool get) {
		double left = prim(get);

		for (; ; ) {
			switch (curr_tok) {
			case Lexer::MUL:
				left *= prim(true);
				break;
			case Lexer::DIV:
				if (double d = prim(true)) {
					left /= prim(true);
					break;
				}
				throw Error::Syntax_error("divide by 0");
			default:
				return left;

			}
		}
	}

	double expr(bool get) {
		double left = term(get);

		for (; ; ) {
			switch (curr_tok) {
			case Lexer::PLUS:
				left += term(true);
				break;
			case Lexer::MINUS:
				left -= term(true);
				break;
			default:
				return left;
			}
		}
	}


}