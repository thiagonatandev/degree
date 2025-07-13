EXEC = main

SRCS = main.c diplomas.c
OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

clean-obj:
	rm -f $(OBJS)