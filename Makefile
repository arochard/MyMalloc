ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CC = clang -Wall -Wextra -Werror

SRC_DIR = srcs

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -o $@ -fPIC -c $<

all: $(NAME)

$(NAME):$(OBJ)
	$(CC) -shared -fPIC -o $@ $^
	@ln -s $(NAME) libft_malloc.so
	@echo "\033[0;32m$(NAME) : Compilation successful !! \033[0;32m"

clean:
	@rm $(OBJ)

fclean: clean
	@rm $(NAME)
	@rm -f libft_malloc.so

re: fclean all

.PHONY: all clean fclean re
