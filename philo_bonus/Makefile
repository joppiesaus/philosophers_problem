# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jobvan-d <jobvan-d@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/15 17:55:39 by jobvan-d      #+#    #+#                  #
#    Updated: 2022/05/05 12:33:03 by jobvan-d      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# TODO: check if according to subject

NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJ_DIR = obj

DEPS = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJ = $(DEPS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR):
	mkdir $@

clean:
	rm -f $(OBJ_DIR)/*.o

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
