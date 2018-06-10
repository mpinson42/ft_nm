NAME = ft_nm

NAME2 = ft_otool

SRC = srcs/main.c srcs/lib.c srcs/bin_32.c srcs/bin_64.c  srcs/fat_32.c srcs/print.c srcs/sort_64.c srcs/sort_32.c

SRC2 = srcs/otools.c srcs/otools_64.c srcs/otools_32.c srcs/otool_fat.c srcs/lib.c

FLAGS = -Wall -Wextra -Werror

OBJ = main.o lib.o bin_32.o bin_64.o  fat_32.o print.o sort_64.o sort_32.o

OBJ2 = otools.o otools_64.o otools_32.o otool_fat.o lib.o

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
	/bin/rm -f $(OBJ2)
	@make -C ./libft clean

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(NAME2)
	@make -C ./libft fclean

re: fclean all
