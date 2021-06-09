# project5
> A subset-C compiler that compiles to OS X. Originally based on C source of the same compiler.

## General
A toy C compiler that produces assembly code for a virtual machine that may not exist anymore.  Because of this,
I also wrote an intrepreter/vm but I haven't posted the code. 
## Background
My orignal goal was to see what it would take for me to use an original C codebase and turn it into a C++
one instead.  I had originally coded this with the C flex/bison(lex/yacc) lexer and parsers so I have tried
to use flex++ and bison c++ classes as a replacement.
### Other Goals
 - Create a preprocessor that can take include directives for multiple file source projects
- Get all original functionality working
- Create a test suite that can automatically run
- Optimize code

## Internal Features
* Generated Lexical Analyzer from Flex++
* Generated Syntactic Analyzer from Bison
* Custon Symbol Table
* Custom Semantic Analyzer - currently not tree walking but uses a one-time pass
* Custom Code Generator - currently generates code for an older language that I did not come up with

## User Features
* Compile a subset of C programs down to Assembly. (No machine or bytecode generation at this time)

# Compiling
(in the source directory) run make:

```
computer:myhome/ userBob$ cd source_to_project5
computer:mhome/source_to_project5/ userBob$ make
```

# Running
(in the build directory) run project5:

```
computer:myhome/source_to_project5/ userBob$ cd build
computer:mhome/source_to_project5/ userBob$ ./project5
```

Run project 5 with the '-h' flag for help on how to use the command

Basic usage -- add the name of a current C file ending in '.c' as the first command-line parameter
to project5.

If all goes well, the assembly file of the same name ending in '.asm' will be left in the same directory
as the '.c' file.

# Running Tests
Although it hasn't been automated, I have included some sample files to run through the compiler

Some of these I have writen, some of them were written by other people.

There are test files that will fail, those that test the compiler against erroneous code and some that will succeed.

# Output

A '.asm' file to be fed into a machine/virtual machine , to an interpreter or to a opcode/bytecode generator.

# Further Goals

Yes. :)

# Contact
Feel free to contact [me](mailto:scott@laureltreecomputing.com) with questions, comments, suggestions, etc. I'm open to feedback.
