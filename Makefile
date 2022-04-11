# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jobvan-d <jobvan-d@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/15 17:55:39 by jobvan-d      #+#    #+#                  #
#    Updated: 2022/04/11 17:09:12 by jobvan-d      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC = cc
INCL = -I./unity/src -I./unity/extras/fixture/src -I./philo
CFLAGS = -Wall -Wextra
OBJ_DIR = obj

DEPS = philo/fork.c philo/thinker.c philo/writer.c philo/arg_checking.c unity/extras/fixture/src/unity_fixture.c $(wildcard test/*.c)
HEADERS = $(wildcard philo/*.h)
TEST_OBJ = $(DEPS:%.c=$(OBJ_DIR)/%.o)

TEST_DEPS = $(shell find test -type f -name "*.c")
TEST_OBJ = $(TEST_DEPS:%.c=%.o)

all: test

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCL) -c -o $@ $<

$(OBJ_DIR):
	mkdir $@

test: $(TEST_OBJ)
	$(CC) $(CFLAGS) $(INCL) -o $@ $^

clean:
	rm -f $(OBJ_DIR)/*.o

fclean: clean
	rm -f $(NAME)
	rm -f test

re: fclean $(NAME)

.PHONY: all clean fclean re
