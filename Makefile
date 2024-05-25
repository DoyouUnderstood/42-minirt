
NAME = miniRT
LIBFT_DIR = lib/libft
FT_PRINTF_DIR = lib/ft_printf
GNL_DIR = lib/GNL
MLX_DIR = lib/mlx
CC = gcc
CFLAGS = -Wall -Wextra -Werror 
DEBUG_FLAGS = -g -fsanitize=address
# / pour compiler sous Mac, rajouter ceci a mlx_flags ==> -framework OpenGL -framework AppKit
MLX_FLAGS = -L$(MLX_DIR) -framework OpenGL -framework AppKit -lmlx -lm
# CRITERION_FLAGS = -lcriterion
INC_FLAGS = -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -I$(GNL_DIR) -I$(MLX_DIR) -framework OpenGL -framework AppKit -lmlx -lm
TEST_SRCS =  unit_test/cube.c

SRCS = $(shell find src -name "*.c")
OBJ = $(SRCS:.c=.o)

TEST_OBJ = $(TEST_SRCS:.c=.o)

LIBS = $(FT_PRINTF_DIR)/libftprintf.a $(GNL_DIR)/libgnl.a $(LIBFT_DIR)/libft.a 

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(OBJ) -o $(NAME) $(LIBS) $(MLX_FLAGS) $(INC_FLAGS) $(CRITERION_FLAGS) $(LDFLAGS)

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR)

$(FT_PRINTF_DIR)/libftprintf.a:
	make -C $(FT_PRINTF_DIR)

$(GNL_DIR)/libgnl.a:
	make -C $(GNL_DIR)


test: $(TEST_SRCS) $(LIBS)
	clang $(CFLAGS) -o test_$(NAME) $(TEST_SRCS) $(OBJ) $(LIBS) $(MLX_FLAGS) $(INC_FLAGS) $(CRITERION_FLAGS)
	./test_$(NAME)


# Règle pour nettoyer les objets
clean:
		rm -f $(OBJ) # $(TEST_OBJ)
		make -C $(LIBFT_DIR) clean
		make -C $(FT_PRINTF_DIR) clean
		make -C $(GNL_DIR) clean

fclean: clean
		rm -f $(NAME) test_$(NAME)
		make -C $(LIBFT_DIR) fclean
		make -C $(FT_PRINTF_DIR) fclean
		make -C $(GNL_DIR) fclean

re: fclean all

debug: CFLAGS += $(DEBUG_FLAGS)
debug: LDFLAGS += $(DEBUG_FLAGS)
debug: re


.PHONY: all clean fclean re test

# 