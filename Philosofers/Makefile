# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/01 13:58:05 by siroulea          #+#    #+#              #
#    Updated: 2024/03/04 15:56:46 by siroulea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  philosofers

SRC =	main.c		\
		init.c	\
		parsing.c	\
		utils.c		\
		Philosofers.c	\
			

OBJS = ${SRC:.c=.o}

CC = clang
CFLAGS = -Wextra -Wall -Werror 

CLEAN = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(CLEAN) $(OBJS)
	$(CLEAN) *.o

fclean: clean
	$(CLEAN) $(NAME)

re: fclean all


# leaks: all
# 	valgrind --leak-check=full --track-fds=yes --trace-children=yes -s ./pipex ft_split.c "wc -l" "wc -l"  caca 