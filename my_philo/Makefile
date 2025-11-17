# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/24 19:39:36 by ewbouffe          #+#    #+#              #
#    Updated: 2025/11/17 22:27:42 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= clang
CFLAGS	= -Wall -Wextra -Werror -g3
# CFLAGS += -fsanitize=address
CFLAGS += -fsanitize=thread

SRCDIR	= srcs
INCDIR	= include
BUILDDIR= build
NAME	= philo
SRC		= $(wildcard $(SRCDIR)/*.c)
OBJ		= $(SRC:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)
VALGRIND = valgrind
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes
GREEN	= \033[1;32m
BLUE	= \033[1;34m
CYAN	= \033[1;36m
RESET	= \033[0m
all: $(NAME)

$(NAME): $(OBJ)

	@echo "$(CYAN)"
	@echo " _____   _    _  _____  _        ____    _____   ____   _____   _    _  ______  _____    _____ "
	@echo "|  __ \ | |  | ||_   _|| |      / __ \  / ____| / __ \ |  __ \ | |  | ||  ____||  __ \  / ____|"
	@echo "| |__) || |__| |  | |  | |     | |  | || (___  | |  | || |__) || |__| || |__   | |__) || (___  "
	@echo "|  ___/ |  __  |  | |  | |     | |  | | \___ \ | |  | ||  ___/ |  __  ||  __|  |  _  /  \___ \ "
	@echo "| |     | |  | | _| |_ | |____ | |__| | ____) || |__| || |     | |  | || |____ | | \ \  ____) |"
	@echo "|_|     |_|  |_||_____||______| \____/ |_____/  \____/ |_|     |_|  |_||______||_|  \_\|_____/ "
	@echo "                                                                                               "
	@echo "$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@$(MAKE) --no-print-directory loading
	@echo "$(GREEN)✅ Compilation terminée !$(RESET)"
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

clean:
	@rm -rf $(BUILDDIR)

fclean: clean
	@rm -f $(NAME)

re: 
	make fclean 
	make all

valgrind: $(NAME)
	@echo "Exécution avec Valgrind..."
	@$(VALGRIND) $(VALGRIND_FLAGS) ./$(NAME) 2 800 200 200

loading :
	@i=0; total=100; \
	while [ $$i -le $$total ]; do \
		filled=`printf "%0.s#" `; \
		empty=`printf "%0.s." `; \
		printf "\r [%-*s%-*s] %d%%" $$i "$$(printf "%0.s#" $$(seq 1 $$i))" $$((total - i)) "$$(printf "%0.s." $$(seq 1 $$((total - i))))" $$(( $$i * 1 )); \
		sleep 0.05; \
		i=`expr $$i + 1`; \
	done; \
	printf "\r\033[K"
	
.PHONY: all clean fclean re valgrind
