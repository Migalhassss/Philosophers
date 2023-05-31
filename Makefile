
NAME			=	philo

FILES	=	philo.c				\
			check_arguments.c	\
			init.c				\
			routime.c			\


OBJS		=	$(FILES:.c=.o)

RM	= rm -f

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror -g #-fsanitize=address


all: $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)
re:		fclean all