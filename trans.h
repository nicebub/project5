#ifndef _MYTRANS
#define _MYTRANS
#include <cstdio>

namespace ucc{

struct Pair{
	int one;
	int two;
};
//int globalcount;
//int localcount;
//int labelcounter;
//extern FILE *infile;


class CodeGenerator{
	public:
	
		static void initializelabel(void);
		static int getlabel(void); 	//return next available label number
		static void gen_label(std::string name);	//generate label with label name : name
		static std::string genlabelw(std::string name, int labelnum); //generate a label with $<labelname><labelnumber>
		static void gen_instr(std::string name); 	//for instructions without arguments
		static void gen_instr_I(std::string name, int arg); // for instructions with arguments
		static void gen_instr_S(std::string name, std::string inS); 	//used for jump command
		static void gen_instr_F(std::string name, float arg);	//use for float
		static void gen_call(std::string funcname, int numargs);
		static void gen_instr_tI(std::string name, int arg1, int arg2);

		static std::string concat(std::string, std::string);	//concat 2 strings and return the answer, remember to free it when done
		static void nullout(std::string name, int length);
	
	private:
};
}
#endif
