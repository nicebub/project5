#ifndef _TRANSLATOR_HPP
#define _TRANSLATOR_HPP

#include <string>
#include "program.hpp"
namespace project5 {
	class Machine;
	
	class Translator {

		public:
			Translator(Machine& mach);
			virtual ~Translator() = 0;
			Translator(const Translator&);
			Translator& operator=(const Translator&);
			
			Program::register_t convertCmd2ByteCode(std::string& s);

			void translateMOV();
			void translateHALT();
			void translatePUSH();
			void translatePOP();
			void translateCALL();
			void translateADD();
			void translateSUB();
			void translateDIV();
			void translateMULT();
			void tranlsateJMP();
			void translateJMPZ();
			void translateZERO();
			
		private:
			Machine & mach;
	};

}



#endif