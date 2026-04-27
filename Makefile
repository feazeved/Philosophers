NAME			=	philo
BONUS_NAME		=	philo_bonus

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
LDFLAGS			=	-pthread

MANDATORY_DIR	=	mandatory
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

BONUS_DIR		=	bonus
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

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

bonus:	$(BONUS_NAME)

$(BONUS_NAME):	$(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LDFLAGS) -o $(BONUS_NAME)

$(BONUS_OBJ_DIR)/%.o:	$(BONUS_SRC_DIR)/%.c | $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) -I $(BONUS_INC_DIR) -c $< -o $@

$(BONUS_OBJ_DIR):
	mkdir -p $(BONUS_OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)

fclean:	clean
	rm -f $(NAME) $(BONUS_NAME)

re:	fclean all

.PHONY:	all bonus clean fclean re
