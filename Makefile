# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/24 19:39:36 by ewbouffe          #+#    #+#              #
#    Updated: 2025/06/25 03:34:18 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g3

SRCDIR	= srcs
INCDIR	= include
BUILDDIR= build
NAME	= philo
SRC		= $(wildcard $(SRCDIR)/*.c)
OBJ		= $(SRC:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)
VALGRIND = valgrind
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

valgrind: $(NAME)
	@echo "Exécution avec Valgrind..."
	@$(VALGRIND) $(VALGRIND_FLAGS) ./$(NAME) 2 800 200 200

.PHONY: all clean fclean re valgrind
