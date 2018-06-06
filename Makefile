NAME = ft_nm

NAME2 = otool

SRC = srcs/main.c srcs/bin_64_revers.c srcs/bin_32_revers.c srcs/lib.c srcs/bin_32.c srcs/bin_64.c  srcs/fat_32.c

SRC2 = srcs/otools.c srcs/otools_64.c srcs/otools_32.c srcs/otool_fat.c srcs/lib.c

FLAGS = -Wall -Wextra -Werror

OBJ = main.o

all: $(NAME)

%.o : %.c
	gcc -c -o $@ $^

$(NAME): $(SRC) $(SRC2)
	@echo "mpinson" > auteur
	@make -C ./libft all
	@cp ./libft/libft.a ./lib
	gcc $(FLAGS) -I ./include/ -L ./lib -lft -o $(NAME) $(SRC)

	gcc $(FLAGS) -I ./include/ -L ./lib -lft -o $(NAME2) $(SRC2)


clean:
	/bin/rm -f $(OBJ)
	@make -C ./libft clean

fclean: clean
	/bin/rm -f $(NAME)
	@make -C ./libft fclean

re: fclean all
