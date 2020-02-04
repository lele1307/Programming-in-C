CFLAGS = -O2 -Wall -Wextra -Werror -Wfloat-equal -pedantic -ansi
DFLAGS = -g3 -Wall -Wextra -Werror -Wfloat-equal -pedantic -ansi
SFLAGS = -g3 -fsanitize=undefined -fsanitize=address
TESTBASE = homophones
INCS = fmvm.h
SOURCES =  $(TESTBASE).c fmvm.c
EXECS = $(TESTBASE) $(TESTBASE)_d $(TESTBASE)_s fhomophone
CC = clang

run: $(TESTBASE)
	./$(TESTBASE) -n 4 CHRISTMAS PROGRAM PASSING

all: $(EXECS)

$(TESTBASE): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $@ $(CFLAGS)

$(TESTBASE)_d: $(SOURCES) $(INCS) 
	$(CC) $(SOURCES) -o $@ $(DFLAGS) 

$(TESTBASE)_s: $(SOURCES) $(INCS) 
	$(CC) $(SOURCES) -o $@ $(SFLAGS) 

clean:
	rm -f $(EXECS)

memleaks: $(TESTBASE)_d $(TESTBASE)_s
	@echo "Sanitize :"
	@./$(TESTBASE)_s RHYME
	@echo "Valgrind :"
	@valgrind --leak-check=full ./$(TESTBASE)_d RHYME

