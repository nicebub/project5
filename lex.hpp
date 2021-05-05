#ifndef _LEX_HPP
#define _LEX_HPP

#include <string>

namespace ucc{
	class Lex{
		public:
			Lex();
			~Lex();
			std::string string_buf;
//	char string_buf[MAX_STR_CONST];
			std::string* string_buf_ptr;
//	char *string_buf_ptr;
	};
}

#endif