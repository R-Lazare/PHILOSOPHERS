name = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=thread

LDFLAGS = -lpthread

src = philo.c utils.c arena_alloc.c arena.c ft_atoi.c ft_isdigit.c ft_printf.c ft_itoa.c ft_putstr_fd.c ft_putchar_fd.c helpers.c

obj = $(src:.c=.o)

$(name): $(obj)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(name) $(obj)

all: $(name)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(obj)

fclean: clean
	rm -f $(name)

re: fclean all

.PHONY: all clean fclean re
