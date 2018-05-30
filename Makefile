NAME = ft_nm

SRC = srcs/main.c srcs/bin_64_revers.c srcs/bin_32_revers.c srcs/lib.c srcs/bin_32.c srcs/bin_64.c  srcs/fat_32.c

FLAGS = -Wall -Wextra -Werror

SRC2 = main.o

all: $(NAME)

%.o : %.c
	gcc -c -o $@ $^

$(NAME): $(SRC)
	@echo "mpinson" > auteur
	@make -C ./libft all
	@cp ./libft/libft.a ./lib
	gcc $(FLAGS) -I ./include/ -L ./lib -lft -o $(NAME) $(SRC)


clean:
	/bin/rm -f $(SRC2)
	@make -C ./libft clean

fclean: clean
	/bin/rm -f $(NAME)
	@make -C ./libft fclean

re: fclean all
