#include "driver.h"



	int no_of_errors = 0;
	std::istream* input = 0;

	void Driver::skip() {
		while (*input) {
			char ch;
			input->get(ch);


			switch (ch) {
			case'\n':
			case';':
				return;
			}

		}
	}