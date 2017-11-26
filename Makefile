# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kromain <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/17 15:05:07 by kromain           #+#    #+#              #
#    Updated: 2017/11/13 17:17:31 by kromain          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lemin

SRC = src/*.c

SRCO = $(SRC:.c=.0)

FLAGS = -Wall -Werror -Wextra -o

all: $(NAME)

$(NAME):
	@echo "                              "
	@echo "\033[01;36mCompiling..."
	@echo "(   )                          .-. "
	@echo " | |    .--.    ___ .-. .-.   ( __)  ___ .-.   "
	@echo " | |   /    \  (   )   '   \  (   ) (   )   \  "
	@echo " | |  |  .-. ;  |  .-.  .-. ;  | |   |  .-. .  "
	@echo " | |  |  | | |  | |  | |  | |  | |   | |  | |  "
	@echo " | |  |  |/  |  | |  | |  | |  | |   | |  | |  "
	@echo " | |  |  ' _.'  | |  | |  | |  | |   | |  | |  "
	@echo " | |  |  .'.-.  | |  | |  | |  | |   | |  | |  "
	@echo " | |  |   '  /  | |  | |  | |  | |   | |  | |  "
	@echo "(___)  \.__.'  (___)(___)(___)(___) (___)(___) "
	@echo "                                              "
	@echo "             \       /                        "
	@echo "              \     /                         "
	@echo "               \.-./                          "
	@echo "              (o\^/o)                         "
	@echo "               ./ \.\ ( )-( )-( ) .-'  '-.    "
	@echo "                {-} \(//  ||   \\/ (   )) '-. "
	@echo "                     //-__||__.-\\.       .-' "
	@echo "                    (/    ()     \)'-._.-'    "
	@echo "                    ||    ||      \\          "
	@echo "            MJP     ('    ('       ')         "
	@echo "						   \033[0m "
	make -C	libft/ fclean && make -C libft/
	gcc $(FLAGS) $(NAME) $(SRC) libft/libft.a
	@echo "                              "
	@echo "\033[01;39mFinished making lemin. Available Makefile commands:\033[0m"
	@echo "\033[01;39m - make\033[0m"
	@echo "\033[01;39m - make clean\033[0m"
	@echo "\033[01;39m - make fclean\033[0m"
	@echo "\033[01;39m - make re\033[0m"

clean:
	@echo "                              "
	@echo "\033[01;39mCleaning lemin...\033[0m"
	make -C libft/ clean
	rm -f $(SRCO)

fclean: clean
	@echo "                              "
	@echo "\033[01;31mRemoved Compiled lemin\033[0m"
	rm -f $(NAME)

re: fclean all
