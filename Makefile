NAME = ft_ping
INCLUDES = ./includes
SRC_PATH = ./sources
OBJ_PATH = $(SRC_PATH)/debug
SRC_NAMES = main.c
OBJ_NAMES = $(SRC_NAMES:.c=.o)
SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAMES))
OBJS = $(addprefix $(OBJ_PATH)/,$(OBJ_NAMES))
LUTILS_PATH = ./libft
LUFLAGS = -L$(LUTILS_PATH) -lft
IFLAGS = -I$(INCLUDES)
CFLAGS = -Wall -Wextra -Werror
CC = gcc

all: $(NAME)

$(OBJ_PATH):
	mkdir $@

$(NAME): $(OBJ_PATH) $(OBJS)
	make -C $(LUTILS_PATH)
	$(CC) -o $@ $(OBJS) $(LUFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $? -o $@

clean:
	rm -rf $(OBJ_PATH)
	make -C $(LUTILS_PATH) fclean

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
