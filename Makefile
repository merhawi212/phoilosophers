# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 20:32:15 by mkiflema          #+#    #+#              #
#    Updated: 2023/08/19 20:23:25 by mkiflema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

M_SRCS	= philo.c fork_handler.c  utils.c thread_handler.c  routine.c time_handler.c checker.c actions.c
M_OBJCS	= $(M_SRCS:.c=.o)

Cdead	=  -Wextra -Werror -Wall -pthread -g3
# -fsanitize=address
CC		= cc
RM		= rm -f


all: $(NAME)

$(NAME):
	$(CC) $(Cdead)	$(M_SRCS) -o $(NAME)

clean: 
	$(RM) $(M_OBJCS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norminette:
	norminette *.c 
