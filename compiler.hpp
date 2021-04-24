#ifndef _COMPILER_HPP
#define _COMPILER_HPP
#include <string>
#include "type.h"

extern FILE* 						yyin;

//#define extern

namespace ucc{
	class Compiler{
		public:
			Compiler();
			~Compiler();
			std::string openfile(int argc, const char** argv);
			int checkargs(int argc, const char** argv);

			static FILE* 			infile;
			static std::string 	filename;
			static int 				Line_Number;
			static int 				globalcount;
			static int				offset_counter;
			static int				labelcounter;
			static int 				othercounter;
			static int 				param_offset;
			static int 				mainlocal;
			static bool 			founderror;

			SymbolTable 			mysymtab;
		private:
//			extern FILE*	infile;
//			Symtab*			mysymtab;
	};
}
#endif
