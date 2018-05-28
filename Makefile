NAME = ft_nm

SRC = srcs/main.c

FLAGS = -Wall -Wextra -Werror

SRC2 = main.o

all: $(NAME)

%.o : %.c
	gcc -c -o $@ $^

$(NAME): $(SRC)
	@echo "mpinson" > auteur
	@make -C ./libft all
	@make -C ./ft_printf
	@cp ./libft/libft.a ./lib
	@cp ./ft_printf/libftprintf.a ./lib
	gcc $(FLAGS) -I ./include/ -L ./lib -lft -lftprintf -o $(NAME) $(SRC)


clean:
	/bin/rm -f $(SRC2)
	@make -C ./libft clean
	@make -C ./ft_printf clean

fclean: clean
	/bin/rm -f $(NAME)
	@make -C ./libft fclean
	@make -C ./ft_printf fclean

re: fclean all
