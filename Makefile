NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread
INC		= -I includes

SRC_DIR	= src
SRCS	= $(SRC_DIR)/main.c \
		  $(SRC_DIR)/parsing.c \
		  $(SRC_DIR)/time.c \
		  $(SRC_DIR)/threads.c \
		  $(SRC_DIR)/setup.c \
		  $(SRC_DIR)/actions.c \
		  $(SRC_DIR)/output.c \
		  $(SRC_DIR)/monitor.c

OBJ_DIR	= obj
OBJS	= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/philo.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
