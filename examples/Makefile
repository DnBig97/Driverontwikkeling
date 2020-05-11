CC=gcc
CFLAGS=-I.
OBJ = test_application.o 

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

test_application: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)