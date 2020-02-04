CFLAGS = -O2 -Wall -Wextra -Wfloat-equal -pedantic -ansi
DFLAGS = -g3 -Wall -Wextra -Wfloat-equal -pedantic -ansi
SFLAGS = -g3 -fsanitize=undefined -fsanitize=address
TEST = test4.nal
BASE = tinterp
INCS = interp.h
SOURCES =  $(BASE).c interp.c
EXECS = $(BASE) $(BASE)_d $(BASE)_s
CC = clang

run: $(BASE)
	./$(BASE) $(TEST)

all: $(EXECS)

$(BASE): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $@ $(CFLAGS)

$(BASE)_d: $(SOURCES) $(INCS) 
	$(CC) $(SOURCES) -o $@ $(DFLAGS) 

$(BASE)_s: $(SOURCES) $(INCS) 
	$(CC) $(SOURCES) -o $@ $(SFLAGS) 

clean:
	rm -f $(EXECS)

memleaks: $(BASE)_d $(BASE)_s
	@echo "Sanitize :"
	@./$(BASE)_s $(TEST)
	@echo "Valgrind :"
	@valgrind --leak-check=full ./$(BASE)_d $(TEST)