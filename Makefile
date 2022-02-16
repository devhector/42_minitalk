CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = /bin/rm -f

SERVER_C = src/server.c
CLIENT_C = src/client.c

INCLUDE = include/

SERVER = server
CLIENT = client

NAME = $(SERVER) $(CLIENT)

LIBFT = libft/libft.a

all: $(NAME)

$(LIBFT):
	make -C libft

$(SERVER): $(LIBFT)
	@echo "Compiling $(SERVER)"
	@$(CC) $(CFLAGS) -I $(INCLUDE) $(SERVER_C) $(LIBFT) -o $(SERVER)

$(CLIENT): $(LIBFT)
	@echo "Compiling $(CLIENT)"
	@$(CC) $(CFLAGS) -I $(INCLUDE) $(CLIENT_C) $(LIBFT) -o $(CLIENT)

clean:
			@echo "Cleaning"
			make clean -C libft

fclean:		clean
			make fclean -C libft
			@$(RM) $(SERVER) $(CLIENT)

re:			fclean all

.PHONY:		all re clean fclean