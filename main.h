#ifndef _MYMAINH
#define _MYMAINH
#include "type.h"


#define extern

namespace ucc{
	class Compiler{
		public:
			Compiler();
			~Compiler();
		private:
			extern FILE*	infile;
			extern int		Line_Number;
			extern int		globalcount;
			extern int		offset_counter;
			extern int		labelcounter;
			extern char*	filename;
			extern bool		founderror;
			Symtab*			mysymtab;
			int 				othercounter;
			int 				param_offset;
			int 				mainlocal;
	};
}
#endif
