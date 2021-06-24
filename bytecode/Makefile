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

.PHONY: all clean test run lint

SRCDIR = src
OBJDIR = obj
BUILDDIR = build
HDRDIR = include

FULLOBJDIR = ${BUILDDIR}/${OBJDIR}

SRC := $(wildcard ${SRCDIR}/*.cpp)
HDR := $(wildcard ${HDRDIR}/*.hpp)
SRC_STRIP := $(subst ./,,$(wildcard ${SRCDIR}/*.cpp))
HDR_STRIP := $(subst ./,,$(wildcard ${HDRDIR}/*.hpp))

OBJS := $(patsubst ${SRCDIR}/%,%,$(subst .cpp,.o, $(SRC)))
FULLOBJS := $(patsubst %,${FULLOBJDIR}/%,${OBJS})
DEBUG = -g
G++ = `which g++`
BINARY = bytecode
EXEC = ${BUILDDIR}/${BINARY}
LINT = cpplint
LINTFLAGS = --verbose=2

STD = -std=c++2a
CPPFLAGS += -I${HDRDIR} ${STD}

all: ${BUILDDIR} ${FULLOBJDIR} ${EXEC}
#	@echo "---------------Source Files------------------"
#	@echo "in directory: " ${SRCDIR}
#	@echo ${SRC}
#	@echo "---------------Header Files------------------"
#	@echo "in directory: " ${HDRDIR}
#	@echo ${HDR}
#	@echo "------Will turn into these object files------"
#	@echo "in directory: " ${FULLOBJDIR}
#	@echo ${OBJS}

$(BUILDDIR):
	$(MKDIR) $(BUILDDIR)

$(FULLOBJDIR):
	$(MKDIR) $(FULLOBJDIR)


${FULLOBJDIR}/%.o: ${SRCDIR}/%.cpp ${HDRDIR}/%.hpp
	${G++} ${CPPFLAGS} ${DEBUG} -c $< -o $@
${FULLOBJDIR}/%.o: ${SRCDIR}/%.cpp 
	${G++} ${CPPFLAGS} ${DEBUG} -c $< -o $@
	
${EXEC}: ${FULLOBJS}
	@echo ${FULLOBJS}
	${G++} ${CPPFLAGS} ${DEBUG} $^ -o $@

lint:
	 ${LINT} ${LINTFLAGS} src/*.cpp include/*.hpp

clean:
	${CLEANUP} ${FULLOBJDIR}/*
	${CLEANDIR} ${FULLOBJDIR}
	${CLEANUP} ${BUILDDIR}/*
	${CLEANDIR} ${BUILDDIR}
	

