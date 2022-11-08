CC = gcc
RM = rm
CFLAGS = -std=c18 \
  -Wall -Wconversion -Werror -Wextra -Wfatal-errors -Wpedantic -Wwrite-strings \
  -O2 -c

SRCS = main.c generate_text.c
OBJS = main.o generate_text.o

EXEC = genere-texte


all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)
$(OBJS): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS)

clean:
	$(RM) $(OBJS) $(EXEC)
