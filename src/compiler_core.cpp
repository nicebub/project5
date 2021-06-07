#include "debug.hpp"
#include "compiler.hpp"
namespace ucc{
	Compiler::Compiler(): mysymtab{nullptr}, 
								code_generator{},
								lexer{nullptr,*this},
								parser{nullptr},
								currentFunc{nullptr},
								outfile{nullptr},
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
		    install_functions_into_symbolTable();
			parser = new uccParser{*this};
			parser->set_debug_stream(std::cerr);
			parser->set_debug_level(1);
		}
		catch(std::bad_alloc& e){
			debugprint(e.what(),"");
			exit(-1);
		}
		mainlabel = code_generator.getlabel();
	}
    
void Compiler::install_functions_into_symbolTable(){
    List* params{List::mklist("",ucc::type::VOID)};
    TableEntry* entry{mysymtab->createFunc("main", ucc::type::INT,params )};
    mysymtab->install(entry);
}

	Compiler::Compiler(int argc, const char** argv) : 	Compiler{}
	{
		openedInputFile(argc,argv);
	}

	Compiler::~Compiler(){
		
		if(outfile != nullptr){
//			std::ofstream* temp{nullptr};
			outfile->flush();
//			temp->close();
			debugprint("Closing file\n","");
			delete outfile;
			outfile = nullptr;
		}
		if(mysymtab != nullptr){
			debugprint("deleteting symbol table\n","");
			delete mysymtab;
			mysymtab = nullptr;
		}
		if(parser != nullptr){
			debugprint("deleteing parser\n","");
			delete parser;
			parser = nullptr;
		}
		currentFunc = nullptr;
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
