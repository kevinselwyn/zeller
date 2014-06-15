NAME   := zeller
BINDIR := /usr/local/bin

all: $(NAME)

$(NAME): $(NAME).c
	gcc -w -o $@ $< -lm

test: $(NAME)
	./$(NAME) "July 4, 1776"

install: $(NAME)
	install -m 0755 $< $(BINDIR)

uninstall:
	rm -f $(BINDIR)/$(NAME)

clean:
	rm $(NAME)
