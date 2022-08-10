CC=gcc
INCDIRS=-I.
OPT=-O0
CFLAGS=-Wall -Werror -g $(INCDIRS) $(OPT)


CFILES:=ip-arg.c
OBJECTS:=ip-arg.o
HEADERS:=ip-arg.h
BINARY=ipArg

# ifdef $(TEST)
# 	$(HEADERS) += CuTest.h
# 	$(CFILES) += test.c
# 	$(OBJECTS) += test.O0
# 	echo $(TEST)
# else
# 	$(CFILES) += main.c
# 	$(OBJECTS) += main.o
# 	$(TEST)
# endif
#.PHONY: test
#
#HEADERS: $(HEADERS) + CuTest.h
#CFILES: -main.c
#CFILES: +test.c

all: $(BINARY)

$(BINARY): $(OBJECTS) main.o $(HEADERS) CuTest.h
	$(CC) -o $@ $(OBJECTS) main.o

test: ipArgDebug

ipArgDebug: $(OBJECTS) CuTest.o test.o $(HEADERS)
	$(CC) -o $@ $(OBJECTS) CuTest.o test.o

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf $(BINARY) *.o ipArg ipArgDebug
