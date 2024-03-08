NAME		=	pipex

CC			=	cc

#FLAG		=	-Wall -Wextra -Werror -g3
FLAG		=	-g3

LIBFT_PATH	=	libft

LIBFT_FILE	=	libft.a

LIBFT_LIB	=	$(LIBFT_PATH)/$(LIBFT_FILE)

C_FILE		=	pipex.c \
				inits.c

OBJS		=	$(C_FILE:.c=.o)

.c.o:
			$(CC) $(FLAG) -c $< -o $@

all:		$(NAME)

$(LIBFT_LIB):
			make -C $(LIBFT_PATH)

$(NAME):	$(LIBFT_LIB) $(OBJS)
			$(CC) $(OBJS) $(LIBFT_LIB) -o $(NAME)

clean:		
			make clean -C $(LIBFT_PATH)
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)
			make fclean -C $(LIBFT_PATH)

re:			fclean all

.PHONY:		all clean fclean re