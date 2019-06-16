
# Makefile 

CC = gcc

CFLAGS += -Wall -c -Wno-format -I$(shell pwd)

LDFLAGS_LIB += -lpthread -lm -shared -fPIC -D_REENTRANT


SOURCES_LIB += ./CALC_UI.c

SOURCES_main += ./calc_main.c

OBJ_LIB=$(SOURCES_LIB:.c=.o)
EXEC_LIB=libRCALC.so

LDFLAGS_main += -lRCALC

OBJ_main=$(SOURCES_main:.c=.o)
EXEC_main=CALC_UI.out


library: $(SOURCES_LIB) $(EXEC_LIB)

all: $(SOURCES_main) $(EXEC_main)

$(EXEC_LIB) : $(OBJ_LIB)
	$(CC) $(OBJ_LIB) $(LDFLAGS_LIB) -o $@

$(EXEC_main) : $(OBJ_main)
	$(CC) $(OBJ_main) $(LDFLAGS_main) -o $@


.c.o:
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm -rf libRCALC.so
	rm -rf *.o
	rm -rf *.out


