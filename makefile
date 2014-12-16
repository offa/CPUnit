
CC = g++
CFLAGS = -g -c -W -Wall -Wextra -pedantic -O0 -I./src # -D GLOB_DEBUG #  -D DEBUG_LOG
COMPILE = $(CC) $(CFLAGS) 

DEPFILE = .dependencies

LIBFILE = lib/libCPUnit.a

LNK = ar
LFLAGS = -rcs
LINK = $(LNK) $(LFLAGS)

RM = rm -f

SRCFILES := $(wildcard src/*.cpp)
OBJFILES := $(patsubst %.cpp,%.o,$(SRCFILES))

default: 
	@$(MAKE) cpunit_lib

all: 
	@$(MAKE) cpunit_lib 
	@$(MAKE) run_tests

nolink: $(OBJFILES)

cpunit_lib: $(LIBFILE)

lib/libCPUnit.a: $(OBJFILES)
	@mkdir -p ./lib
	$(LINK) lib/libCPUnit.a $(OBJFILES)
	$(RM) test/tester

run_tests:
	@cd test && $(MAKE)
	test/tester

install: 
	@$(MAKE) depend all
	@cd lib && echo "libCPUnit.a is installed in" && pwd

%.o: %.cpp 
	$(COMPILE) -o $@  $<

include $(wildcard src/*.P)

clean_tests:
	@cd test && $(MAKE) clean

clean:
	@$(RM) $(OBJFILES) $(LIBFILE)
	@make clean_tests

depend:
	@echo "" > $(DEPFILE)
	@makedepend -f$(DEPFILE) $(SRCFILES)
	@cd test && $(MAKE) depend

-include $(DEPFILE)
