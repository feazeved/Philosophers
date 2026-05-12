NAME		=	philo_bonus

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
LDFLAGS			=	-pthread

BONUS_DIR		=	.
BONUS_SRC_DIR	=	$(BONUS_DIR)/source
BONUS_INC_DIR	=	$(BONUS_DIR)/includes
BONUS_OBJ_DIR	=	$(BONUS_DIR)/objects

BONUS_SRCS		=	main_bonus.c \
					init_bonus.c \
					parse_bonus.c \
					utils_bonus.c \
					routine_bonus.c \
					monitor_bonus.c
BONUS_OBJS		=	$(addprefix $(BONUS_OBJ_DIR)/, $(BONUS_SRCS:.c=.o))

all:	$(NAME)

bonus:	$(NAME)

$(NAME):	$(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LDFLAGS) -o $(NAME)

$(BONUS_OBJ_DIR)/%.o:	$(BONUS_SRC_DIR)/%.c | $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) -I $(BONUS_INC_DIR) -c $< -o $@

$(BONUS_OBJ_DIR):
	mkdir -p $(BONUS_OBJ_DIR)

clean:
	rm -rf $(BONUS_OBJ_DIR)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all bonus clean fclean re
