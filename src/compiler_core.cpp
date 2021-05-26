#include "compiler.hpp"
namespace ucc{
	Compiler::Compiler(): mysymtab{nullptr}, 
								code_generator{},
								lexer{nullptr,*this},
								parser{nullptr},
								currentFunc{nullptr},
								Line_Number{1},
								globalcount{0},
								offset_counter{5},
								othercounter{1},
								param_offset{0},
								mainlocal{0},
								founderror{false}
	{
		try{
			mysymtab = new SymbolTable{ *this};
		}
		catch(std::bad_alloc& e){
			std::cerr << e.what();
		}
		mainlabel = code_generator.getlabel();
		/*
		if(mysymtab == nullptr){
			error("Unable to construct symbol table","");
		}
		*/
	}

	Compiler::Compiler(int argc, const char** argv) : 	mysymtab{new SymbolTable{ *this} }, 
																		code_generator{},
																		lexer{nullptr,*this},
																		parser{nullptr},
																		currentFunc{nullptr},
																		Line_Number(1),
																		globalcount(0),
																		offset_counter(5),
																		othercounter(1),
																		param_offset(0),
																		mainlocal(0),
																		founderror{false}
	{
		mainlabel = code_generator.getlabel();

		if(mysymtab == nullptr){
			error("Unable to construct symbol table","");
		}
		checkargs(argc,argv);
	}

	Compiler::~Compiler(){
		#ifdef DEBUG
		std::cerr << "Closing file\n";
		#endif

		if(outfile->good()){
			outfile->flush();
		}

		if(mysymtab != nullptr){
			delete mysymtab;
			mysymtab = nullptr;
		}
	}

}

int Compiler::warning(const std::string s1, const std::string s2) noexcept
{
	std::cerr << "Warning:::"<< filename << ":"<< Line_Number << "-> " << s1 << " " 
				 << s2 << "\n";
	return 0;
}

int Compiler::error(const std::string s1, const std::string s2) noexcept {
	std::cerr << "Error:::"<< filename << ":"<< Line_Number << "-> " << s1 << " " 
				 << s2 << "\n";
	founderror=true;
	code_generator.stop();
	 return 0;
}
