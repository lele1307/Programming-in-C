CFLAGS = -Wall -Wextra -pedantic -ansi -O2 -lm
SFLAGS = -fsanitize=address -fsanitize=undefined -g3 -lm
DFLAGS = -Wall -Wextra -pedantic -ansi -g3 -lm
CC = clang
BASE = nal
BASE1 = parse
TEST1 = tparse
BASE2 = interp
TEST2 = tinterp
BASE3 = exten
TEST3 = texten
BEXECS = parse interp exten
SEXECS = parse_s interp_s exten_s
DEXECS = parse_d interp_d exten_d
EXECS = $(BEXECS) $(SEXECS) $(DEXECS)

all : $(BEXECS)

parse : $(BASE1).c $(BASE1).h 
	$(CC) $(TEST1).c $(BASE1).c $(CFLAGS) -o $(TEST1)
parse_s : $(BASE1).c $(BASE1).h 
	$(CC) $(TEST1).c $(BASE1).c $(SFLAGS) -o $(TEST1)_s
parse_d : $(BASE1).c $(BASE1).h 
	$(CC) $(TEST1).c $(BASE1).c $(DFLAGS) -o $(TEST1)_d

interp : $(BASE2).c $(BASE2).h 
	$(CC) $(TEST2).c $(BASE2).c $(CFLAGS) -o $(TEST2)
interp_s : $(BASE2).c $(BASE2).h 
	$(CC) $(TEST2).c $(BASE2).c $(SFLAGS) -o $(TEST2)_s
interp_d : $(BASE2).c $(BASE2).h 
	$(CC) $(TEST2).c $(BASE2).c $(DFLAGS) -o $(TEST2)_d

exten : $(BASE3).c $(BASE3).h $(BASE2).c $(BASE2).h 
	$(CC) $(TEST3).c $(BASE3).c $(BASE2).c $(CFLAGS) -o $(TEST3)
exten_s : $(BASE3).c $(BASE3).h $(BASE2).c $(BASE2).h 
	$(CC) $(TEST3).c $(BASE3).c $(BASE2).c $(SFLAGS) -o $(TEST3)_s
exten_d : $(BASE3).c $(BASE3).h $(BASE2).c $(BASE2).h 
	$(CC) $(TEST3).c $(BASE3).c $(BASE2).c $(DFLAGS) -o $(TEST3)_d


testparse : parse_s parse_d
	./tparse_s test1.$(BASE)
	./tparse_s test2.$(BASE)
	./tparse_s test3.$(BASE)
	./tparse_s test4.$(BASE)
	./tparse_s test5.$(BASE)
	./tparse_s test6.$(BASE)
	./tparse_s escape211.$(BASE)
	./tparse_s labne.$(BASE)
	./tparse_s labnw.$(BASE)
	./tparse_s labse.$(BASE)
	./tparse_s labsw.$(BASE)
	./tparse_s munge.$(BASE)
	valgrind ./tparse_d test1.$(BASE)
	valgrind ./tparse_d test2.$(BASE)
	valgrind ./tparse_d test3.$(BASE)
	valgrind ./tparse_d test4.$(BASE)
	valgrind ./tparse_d test5.$(BASE)
	valgrind ./tparse_d test6.$(BASE)
	valgrind ./tparse_d escape211.$(BASE)
	valgrind ./tparse_d labne.$(BASE)
	valgrind ./tparse_d labnw.$(BASE)
	valgrind ./tparse_d labse.$(BASE)
	valgrind ./tparse_d labsw.$(BASE)
	valgrind ./tparse_d munge.$(BASE)

testinterp : interp_s interp_d
	./tinterp_s test1.$(BASE)
	./tinterp_s test2.$(BASE)
	./tinterp_s test4.$(BASE)
	./tinterp_s test5.$(BASE)
	valgrind ./tinterp_d test1.$(BASE)
	valgrind ./tinterp_d test2.$(BASE)
	valgrind ./tinterp_d test4.$(BASE)
	valgrind ./tinterp_d test5.$(BASE)

testextension : exten_s exten_d
	./texten_s exten_test1.$(BASE)
	valgrind ./texten_d exten_test1.$(BASE)

escape211:
	./tinterp escape211.nal
	
clean :
	rm -fr $(EXECS)
