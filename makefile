CC = gcc
RM = rm
CFLAGS = -std=c18 \
  -Wall -Wconversion -Werror -Wextra -Wfatal-errors -Wpedantic -Wwrite-strings \
  -O2 -c

SRCS = main.c tp2.c utils.c
OBJS = main.o tp2.o utils.o

EXEC = main


all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)
$(OBJS): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS)

clean:
	$(RM) $(OBJS) $(EXEC)