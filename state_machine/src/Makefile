IDIR =../include
CC=gcc
CFLAGS= -std=gnu99 -g -Wall -Werror -Wextra -I$(IDIR)

ODIR=obj

_DEPS = dfsm.h queue.h state.h trie.h fail_automat.h darray.h minimisation.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = dfsm.o queue.o state.o trie.o main.o fail_automat.o darray.o minimisation.h
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c $(CFLAGS) -o $@ $<

../a.out : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ 

aho-corasick: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 