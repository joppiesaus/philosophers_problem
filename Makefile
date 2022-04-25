# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jobvan-d <jobvan-d@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/15 17:55:39 by jobvan-d      #+#    #+#                  #
#    Updated: 2022/04/25 17:27:29 by jobvan-d      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = test_philo

INC = -I./unity/src -I./unity/extras/fixture/src -I./philo

UNITY_CFG = -D UNITY_OUTPUT_COLOR -D UNITY_FIXTURE_NO_EXTRAS

CFLAGS = -Wall -Wextra -Werror
OBJ_DIR = obj

DEPS = philo/fork.c philo/thinker.c philo/writer.c philo/parse_args.c \
	philo/time.c philo/thinker_actions.c philo/util.c \
	unity/src/unity.c unity/extras/fixture/src/unity_fixture.c $(wildcard test/*.c)
HEADERS = $(wildcard philo/*.h)
TEST_OBJ = $(DEPS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) $(UNITY_CFG) -c -o $@ $<

$(OBJ_DIR):
	mkdir $@

$(NAME): $(TEST_OBJ)
	$(CC) $(CFLAGS) $(INC) $(UNITY_CFG) -o $@ $^

clean:
	rm -rf $(OBJ_DIR)/*

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
