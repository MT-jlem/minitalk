CC = cc

CFLAGS = -Wall -Wextra -Werror

all : server client

server : server.c ft_printf.c
	@$(CC) $(CFLAGS) ft_printf.c server.c -o server

client : client.c ft_atoi.c ft_strlen.c
	@$(CC) $(CFLAGS) ft_strlen.c ft_atoi.c client.c -o client

clean :
	@rm -rf server client

fclean : clean

bonus : all

re : fclean all

.PHONY : all bonus fclean clean re
