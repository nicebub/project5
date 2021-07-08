ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),) # not in a bash-like shell
	CLEANUP = del /F /Q
	MKDIR = mkdir
  else # in a bash-like shell, like msys
	CLEANUP = rm -f
	MKDIR = mkdir -p
  endif
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	CLEANDIR = rmdir
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
#	GENERATE_RUNNER= tools/genrunners.sh
endif

.PHONY: all clean test run lint #regen

vpath %.cpp src
vpath %.s src
vpath %.hpp include
vpath %.so lib
vpath %.la lib

#COMPILER=g++-10
#COMPILER=g++
COMPILER=`which g++`
BISON = `which bison`
#FLEX = /usr/local/Cellar/flex/2.6.4_2/bin/flex++
FLEX  = `which flex++`
FLOP = -+
#FLOP = -+ -d
FCFLAGS = -I/usr/local/opt/flex/include
#BISOP = -vtd
BISOP = -vt
#FLEX = `which flex++`
#PATHU = unity/src/
PATHS = src/
PATHI = include/
PATHT = test/
PATHB = build/
PATHD = build/depends/
PATHO = build/objs/
PATHR = build/results/

EXAMPLES = example/
EXEC = $(PATHB)project5

BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHR)

BASE_SRCT = $(wildcard $(PATHT)*base*.cpp)
#SRCT = $(wildcard $(PATHT)*[!b][!a][!s][!e]*.c)

SRC_FILES := $(subst $(PATHS),,$(wildcard $(PATHS)*.cpp))
ASSEM_FILES := $(subst $(PATHS),,$(wildcard $(PATHS)*.s))
#OUTFILE := $(PATHI)outfile.in
HEAD_FILES:= $(subst $(PATHI),,$(wildcard $(PATHI)*.hpp))
SOURCES := $(patsubst %,$(PATHS)%,$(SRC_FILES))
OBJECTS := $(patsubst %.cpp,$(PATHO)%.o,$(SRC_FILES))
ASSEMBLYS := $(patsubst %.s,$(PATHO)%.o,$(ASSEM_FILES))
DEPS := $(patsubst %.cpp, $(PATHD)%.d,$(SRC_FILES))
#NEWFILES := $(wildcard $(PATHS)$(NEWSRC)/*.c)
#NEWCLASSOBJS := $(patsubst $(PATHS)$(NEWSRC)/%.c, $(PATHB)%.o, $(NEWFILES))
#NDEPS := $(patsubst %.c,, $(BUILDDIR)/%.D,$(NEWFILES))

COMPILE=$(COMPILER) -c
LINK=$(COMPILER)
DEPEND=$(COMPILER) -MM -MG -MF
CPPFLAGS = -std=c++14 #-DDEBUGON
CPPFLAGS += -Wall -Wpedantic -pedantic-errors -Wno-comment -I. -I$(PATHI)
#CPPFLAGS += -g
CPPFLAGS += -Os
#CPPFLAGS += -ll -lm
CPPFLAGS += -Wno-deprecated-register ${LDFLAGS} -Wmissing-include-dirs -Winvalid-pch -Wno-overloaded-virtual
TFLAGS = $(CPPFLAGS) $(FCFLAGS) #-DTEST 
#BASE_RESULTS = $(patsubst $(PATHT)Test%_Runner.c,$(PATHR)Test%_Runner.txt,$(BASE_SRCT) )
#RESULTS = $(patsubst $(PATHT)Test%_Runner.c,$(PATHR)Test%_Runner.txt,$(SRCT) )

#PASSED = `grep -s PASS $(PATHR)*.txt`
#FAIL = `grep -s FAIL $(PATHR)*.txt`
#IGNORE = `grep -s IGNORE $(PATHR)*.txt`


all: $(BUILD_PATHS) $(EXEC)

clean: test_clean
	$(CLEANUP) ucc.tab.cpp ucc.tab.hpp
	$(CLEANUP) $(PATHI)ucc.tab.hpp $(PATHS)ucc.tab.cpp $(PATHI)location.hh
	$(CLEANUP) $(PATHS)lex.yy.cc
	$(CLEANUP) $(PATHO)*.o
	$(CLEANUP) $(PATHB)*$(TARGET_EXTENSION)
	$(CLEANUP) $(PATHR)*.txt
	$(CLEANUP) $(PATHD)*.d
	$(CLEANUP) $(PATHB)project5
	$(CLEANUP) -rf $(PATHB)project5.dSYM
	$(CLEANUP) examples/*.asm
	$(CLEANDIR) $(PATHD)
	$(CLEANDIR) $(PATHO)
	$(CLEANDIR) $(PATHR)
	$(CLEANDIR) $(PATHB)
test_clean:
#	$(CLEANUP) $(PATHT)*_Runner.c

#.PRECIOUS: $(PATHB)Testbase%_Runner$(TARGET_EXTENSION)
#.PRECIOUS: $(PATHB)Test%set_Runner$(TARGET_EXTENSION)
#.PRECIOUS: $(PATHB)Test%vector_Runner$(TARGET_EXTENSION)
.PRECIOUS: $(PATHD)%.d
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHR)%.txt

$(PATHS)ucc.tab.cpp : $(PATHS)ucc.ypp
	$(BISON) $(BISOP) -o $@ $^
#	mv $@ $(PATHS)
	mv $(PATHS)ucc.tab.hpp $(PATHI)
	mv $(PATHS)location.hh $(PATHI)

$(PATHS)lex.yy.cc : $(PATHS)ucc.l $(PATHS)ucc.tab.cpp
	$(FLEX) $(FLOP) -o $(PATHS)lex.yy.cc $(PATHS)ucc.l
#	mv $@ $(PATHS)
#	$(COMPILER) $(CPPFLAGS) $(FCFLAGS)$(DEBUG) -o $(PATHO)lex.yy.o -c $(PATHS)$@

$(PATHD)%.d:: %.cpp %.hpp $(BUILD_PATHS)
	$(COMPILER) $(CPPFLAGS) $(FCFLAGS) $(DEBUG) -MM -MG $< -o $@
#-include $(DEPS)

#$(PATHB)sclex.yy.c:: $(EXAMPLES)lex.l
#	$(EXEC) $<
#	mv sclex.yy.c $(PATHB)

#$(OUTFILE):

$(PATHO)%.o:: %.s
	$(COMPILER) $(CPPFLAGS) $(DEBUG) -c $< -o $@

#$(PATHO)%.o:: %.c $(PATHI)%.h $(PATHD)%.d
#	$(COMPILER) $(CPPFLAGS) $(DEBUG) -c $< -o $@

$(EXEC):: $(BUILD_PATHS) $(ASSEMBLYS) $(PATHO)ucc.tab.o $(PATHO)lex.yy.o $(OBJECTS) $(OUTFILE)   #$(DEPS)
	$(COMPILER) $(CPPFLAGS) $(FCFLAGS) $(DEBUG) $(ASSEMBLYS) $(PATHO)ucc.tab.o $(PATHO)lex.yy.o $(OBJECTS)  -o $@

run: $(EXEC)
	./$(EXEC) $(EXAMPLES)expr.l


#regen:
#	$(GENERATE_RUNNER)

test: $(BUILD_PATHS) $(BASE_RESULTS) $(RESULTS)
#	@echo "RESULTS: $(RESULTS)"
#	@echo "BASE_RESULTS: $(BASE_RESULTS)"
#	@echo "BASE_SRCT $(BASE_SRCT)"
#	@echo "SRCT $(SRCT)"
	@echo "-----------------------\nIGNORES:\n-----------------------"
	@echo "$(IGNORE)"
	@echo "-----------------------\nFAILURES:\n-----------------------"
	@echo "$(FAIL)"
	@echo "-----------------------\nPASSED:\n-----------------------"
	@echo "$(PASSED)"
	@echo "\nDONE"


$(PATHR)%.txt: $(PATHB)%$(TARGET_EXTENSION)
	-./$< > $@ 2>&1

$(PATHB)Testbase%_Runner$(TARGET_EXTENSION): $(PATHO)Testbase%_Runner.o $(PATHO)Testbase%.o $(PATHO)base%.o $(PATHO)unity.o #$(PATHD)Test%.d
	$(LINK) -o $@ $^

$(PATHB)Test%set_Runner$(TARGET_EXTENSION): $(PATHO)Test%set_Runner.o $(PATHO)baseset.o $(PATHO)Test%set.o $(PATHO)%set.o  $(PATHO)unity.o #$(PATHD)Test%.d
	$(LINK) -o $@ $^

$(PATHB)Test%vector_Runner$(TARGET_EXTENSION): $(PATHO)Test%vector_Runner.o $(PATHO)Test%vector.o $(PATHO)baseset.o $(PATHO)basevector.o $(PATHO)%set.o $(PATHO)%vector.o $(PATHO)unity.o #$(PATHD)Test%.d
	$(LINK) -o $@ $^


#$(PATHB)Test%_Runner$(TARGET_EXTENSION): $(PATHO)Test%_Runner.o $(PATHO)Test%.o $(PATHO)%.o $(PATHO)unity.o #$(PATHD)Test%.d
#	$(LINK) -o $@ $^ $(PATHO)base*.o


#$(PATHB)Test%$(TARGET_EXTENSION): $(PATHO)Test%.o $(PATHO)%.o $(PATHU)unity.o #$(PATHD)Test%.d
#	$(LINK) -o $@ $^

$(PATHO)ucc.tab.o: $(PATHS)ucc.tab.cpp
	$(COMPILER) $(TFLAGS) $(FCFLAGS) -c $< -o $@

$(PATHO)lex.yy.o: $(PATHS)lex.yy.cc
	$(COMPILER) $(TFLAGS) $(FCFLAGS) -c $< -o $@
	
$(PATHO)%.o:: $(PATHS)%.cpp $(PATHI)%.hpp
	$(COMPILER) $(TFLAGS) $(FCFLAGS) -c $< -o $@

$(PATHO)%.o:: $(PATHT)%.cpp
	$(COMPILER) $(TFLAGS) $(FCFLAGS) -c $< -o $@


$(PATHO)%.o:: $(PATHS)%.cpp
	$(COMPILER) $(TFLAGS) $(FCFLAGS) -c $< -o $@

$(PATHO)%.o:: $(PATHU)%.cpp $(PATHU)%.hpp
	$(COMPILER) $(FCFLAGS) $(TFLAGS) -c $< -o $@

$(PATHD)%.d:: $(PATHT)%.c
	$(DEPEND) $@ $<

$(PATHB):
	$(MKDIR) $(PATHB)

$(PATHD):
	$(MKDIR) $(PATHD)

$(PATHO):
	$(MKDIR) $(PATHO)

$(PATHR):
	$(MKDIR) $(PATHR)

LINT = cpplint
LINTFLAGS = --verbose=2

lint:
	 ${LINT} ${LINTFLAGS} src/*.cpp include/*.hpp
