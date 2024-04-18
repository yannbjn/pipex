NAME		=	pipex

BNAME		=   pipex_bonus

CC			=	cc

FLAG		=	-Wall -Wextra -Werror -g3

LIBFT_PATH	=	libft

LIBFT_FILE	=	libft.a

LIBFT_LIB	=	$(LIBFT_PATH)/$(LIBFT_FILE)

C_FILE		=	pipex.c \
				inits.c \
				exec.c \
				freeclose.c

BC_FILE		=	bonus/bpipex.c \
				bonus/binits.c \
				bonus/bexec.c \
				bonus/bfreeclose.c

OBJS		=	$(C_FILE:.c=.o)

BOBJS		=	$(BC_FILE:.c=.o)

.c.o:
			$(CC) $(FLAG) -c $< -o $@

all:		$(NAME)

ball:		$(NAME) $(BNAME)

$(LIBFT_LIB):
			make -C $(LIBFT_PATH)

$(NAME):	$(LIBFT_LIB) $(OBJS)
			$(CC) $(OBJS) $(LIBFT_LIB) -o $(NAME)

$(BNAME):	$(LIBFT_LIB) $(BOBJS)
			$(CC) $(BOBJS) $(LIBFT_LIB) -o $(BNAME)

bonus:		$(BNAME)

clean:		
			make clean -C $(LIBFT_PATH)
			rm -f $(OBJS)
			rm -f $(BOBJS)

fclean:		clean
			rm -f $(NAME)
			rm -f $(BNAME)
			make fclean -C $(LIBFT_PATH)

re:			fclean all

bre:		fclean ball

.PHONY:		all clean fclean re bonus