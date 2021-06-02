#include <cstdio>
#include <cstdlib>
#include <string>
#include <ostream>
#include <iostream>

#include "trans.hpp"

using namespace ucc;

CodeGenerator::CodeGenerator() : labelcounter{1}, outfile{&std::cout}, canGenerate{true} {
}

CodeGenerator::CodeGenerator(std::ostream& out) : labelcounter{1}, outfile{&out}, canGenerate{true} {}

CodeGenerator::~CodeGenerator() {}

void CodeGenerator::setstream(std::ostream* outfile){
	this->outfile = outfile;
}


inline void CodeGenerator::initializelabel(){
	labelcounter = 1;
}

int CodeGenerator::getlabel(){
	labelcounter++;
	return (labelcounter-1);
}

void CodeGenerator::nullout(std::string& name, int length){
	name.clear();
	/*
	int a;
	for(a=0;a<length;a++){
		name[a]=(char)NULL;
	}
	*/
}

std::string CodeGenerator::genlabelw(std::string name, int labelnum){
	std::string temp{"$"};
	temp += name;
	temp += labelnum;
	return temp;
	/*
	char* tempstr;
	int a;
	char buf[30];
	sprintf(buf,"%d",labelnum);
	
	tempstr = (char*) malloc(sizeof(char)*(strlen(name)+strlen(buf)+2));
	nullout(tempstr, (int)(strlen(name)+strlen(buf)+2));
	tempstr[0]='$';
	tempstr++;
	for(a=0;a<(strlen(name));a++)
		tempstr[a]=name[a];
	tempstr= tempstr-1;
	tempstr = (char*)strcat(tempstr,buf);
	return tempstr;
	*/
}
/*
void CodeGenerator::deletelabel(std::string label){
	if(label != NULL){
		free(label);
		//label=NULL;
	}
}
*/
void CodeGenerator::gen_instr(std::string name){
	if(canGenerate){
		*outfile << "\t" << name << "\n";
		//	fprintf(infile, "\t%s\n", name);
}
}

void CodeGenerator::gen_instr_I(std::string name, int arg){
	*outfile << "\t" << name << "\t" << arg << "\n";
//	fprintf(infile, "\t%s\t%d\n", name, arg);
}

void CodeGenerator::gen_instr_S(std::string name, std::string inS){
	if(canGenerate){
		if(name =="jump" || name == "jumpz"){
	//		fprintf(infile,"\t%s\t%s\n",name,inS);
			*outfile << "\t" << name << "\t" << inS << "\n";
		}
		else{
	//	 fprintf(infile,"\t%s\t\"%s\"\n",name,inS);
		 	*outfile << "\t" << name << "\t" << "\"" << inS << "\"\n";
	 	}
	}
}

void CodeGenerator::gen_label(std::string name){
	if(canGenerate){
		//	fprintf(infile, "%s\n", name);
			*outfile << name << "\n";
	}
}

void CodeGenerator::gen_instr_F(std::string name, float arg){
	if(canGenerate){
		//	fprintf(infile, "\t%s\t%f\n", name, arg);
			*outfile << "\t" << name << "\t" << arg << "\n";
	}
}

void CodeGenerator::gen_call(std::string funcname, int numargs){
	if(canGenerate){
		//	fprintf(infile, "\tcall\t%s, %d\n",funcname,numargs);
			*outfile << "\tcall\t" << funcname << ", " << numargs << "\n";
	}
}

void CodeGenerator::gen_instr_tI(std::string name, int arg1, int arg2){
	if(canGenerate){
		//	fprintf(infile, "\t%s\t%d, %d\n",name, arg1, arg2);
			*outfile << "\t" << name << "\t" << arg1 << ", " << arg2 << "\n";
	}
}


std::string CodeGenerator::concat(std::string char1, std::string char2){
	return char1 + char2;
	/*
	char* tempstr;
        int a;
        tempstr = (char*) malloc(sizeof(char)*(strlen(char1)+strlen(char2)+1));
	nullout(tempstr, (int)(strlen(char1)+strlen(char2)+1));
        for(a=0;a<(strlen(char1));a++)
                tempstr[a]=char1[a];
        tempstr = (char*)strcat(tempstr,char2);
        return tempstr;
		  */
}
bool CodeGenerator::canGenerateCode() const noexcept{
	return canGenerate;
}
void CodeGenerator::stop() noexcept{
	canGenerate = false;
}
void CodeGenerator::start() noexcept{
	canGenerate = true;	
}


