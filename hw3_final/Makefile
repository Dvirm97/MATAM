CC = gcc
OFILES = mtmflix.o user.o series.o mtmFlixTestEx.o Mtm_ex3.o
LIB = -L. -lm -lmtm
DEBUG_FLAG = -DNDEBUG # assign -g for debug, -DNDEBUG for release
FLAGS = -std=c99 mtmflix -Wall -pedantic-errors -Werror
EXE = mtmflix


$(EXE): $(OFILES)
	$(CC) $(DEBUG_FLAG) $(OFILES) $(LIB) -o $@

mtmflix.o: mtmflix.c map.h set.h list.h mtmflix.h mtm_ex3.h series.h user.h
	$(CC) $(DEBUG_FLAG) $(FLAGS) $(LIB) $*.c

user.o: user.c user.h map.h series.h set.h mtm_ex3.h list.h
	$(CC) $(DEBUG_FLAG) $(FLAGS) $(LIB) $*.c

series.o: series.c series.h set.h map.h mtm_ex3.h list.h
	$(CC) $(DEBUG_FLAG) $(FLAGS) $(LIB) $*.c

mtmFlixTestEx.o: mtmFlixTestEx.c test_utilities.h mtmflix.h mtm_ex3.h list.h
	$(CC) $(DEBUG_FLAG) $(FLAGS) $(LIB) $*.c

clean:
	rm -f *.o $(EXE)
