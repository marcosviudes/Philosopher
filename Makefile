#####################################
### CONFIG
#####################################
.DELETE_ON_ERROR:

NAME		= philo
TEST		= test

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -O3
CFLAGS		+= -pthread


RM			= rm -f
MKDIR		= mkdir -p

DIR_SRC		= src/
DIR_UTILS	= utils/

PHILO_SRC	=	main.c\
				parser.c\
				time.c\
				exit.c\
				philo_rutine.c\
				philo.c\
				print_messege.c\
				$(DIR_UTILS)ft_absatol.c\
				$(DIR_UTILS)ft_isnum.c\
				$(DIR_UTILS)ft_putchar_fd.c\
				$(DIR_UTILS)ft_putendl_fd.c\
				$(DIR_UTILS)ft_strlen.c\
				$(DIR_UTILS)ft_putnbr_fd.c

TEST_SRC	=	$(DIR_SRC)/test/main.c

SRC_F 	= $(addprefix $(DIR_SRC), $(PHILO_SRC))


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
