
CC = g++
CFLAGS = -g -c -I../src -Wall -O0 -pedantic-errors # -D DEBUG_LOG
COMPILE = $(CC) $(CFLAGS) # -DSHOW_ERRORS

DEPFILE = .dependencies

LNK = g++
LFLAGS = -L../lib -lCPUnit

RM = rm -f

SRCFILES := $(wildcard *.cpp)
OBJFILES := $(patsubst %.cpp,%.o,$(SRCFILES))

all : tester

tester: $(OBJFILES)
	$(LNK) -o tester $(LFLAGS) $(OBJFILES)

%.o: %.cpp
	$(COMPILE) -o $@ $<

clean:
	@$(RM) $(OBJFILES) tester

depend:
	@echo "" > $(DEPFILE)
	@makedepend -f$(DEPFILE) -I../src $(SRCFILES)

-include $(DEPFILE)