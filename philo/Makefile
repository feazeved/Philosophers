NAME			=	philo

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -g
LDFLAGS			=	-pthread

MANDATORY_DIR	=	.
SRC_DIR			=	$(MANDATORY_DIR)/source
INC_DIR			=	$(MANDATORY_DIR)/includes
OBJ_DIR			=	$(MANDATORY_DIR)/objects

SRCS			=	main.c \
					init.c \
					parse.c \
					utils.c \
					routine.c \
					monitor.c
OBJS			=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all bonus clean fclean re
