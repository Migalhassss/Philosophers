
NAME			=	philo

FILES	=	philo.c				\
			check_arguments.c	\
			init.c				\
			routine.c			\
			supervisor.c		\
			philo_status.c		\


OBJS		=	$(FILES:.c=.o)

RM	= rm -f

CC	= cc

CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=thread


all: $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)
re:		fclean all