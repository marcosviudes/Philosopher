#####################################
### CONFIG
#####################################
.DELETE_ON_ERROR:

NAME		= philo
TEST		= test

CC			= gcc
CFLAGS		= #-Wall -Wextra -Werror -g3
CFLAGS		+= -pthread -g3


RM			= rm -f
MKDIR		= mkdir -p

SRC_DIR		= src/

PHILO_SRC	=	main.c\
				parser.c\
				time_utils.c\
				ft_absatol.c\
				ft_isnum.c\
				ft_putchar_fd.c\
				ft_putendl_fd.c\
				ft_strlen.c\
				ft_putnbr_fd.c

TEST_SRC	=	$(SRC_DIR)/test/main.c

SRC_F 	= $(addprefix $(SRC_DIR), $(PHILO_SRC))


OBJS	= $(SRC_F:%.c=%.o)

INCLUDES 	= -I ./includes

#####################################
### RULES
#####################################

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $^

$(NAME): $(OBJS) ./includes/philosopher.h
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

$(TEST): $(OBJS)
	$(CC) $(DFLAGS) $(TEST_SRC) $(INCLUDES) $(UTILS_O) -o $(TEST)

.PHONY:	all clean fclean re retest debug normi

normi: fclean
	@clear
	norminette src/*
	norminette includes/*

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(TEST)
re: fclean all
debug:
	@$(MAKE) re CFLAGS="-g3 -pthread"
retest:
	$(RM) test
	make test
