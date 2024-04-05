# Nom de la bibliothèque
NAME = libgnl.a

# Compilateur
CC = gcc

# Flags de compilation
CFLAGS = -Wall -Wextra -Werror -I ../libft

# Fichiers source
SRCS = get_next_line.c get_next_line_utils.c

# Fichiers objets
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
