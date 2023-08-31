# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 20:32:15 by mkiflema          #+#    #+#              #
#    Updated: 2023/08/31 20:58:43 by mkiflema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

M_SRCS	= main.c utils.c  philo.c   routine.c actions.c time_handler.c checker.c 
# M_OBJCS	= $(M_SRCS:.c=.o)

CFLAG	=  -Wextra -Werror -Wall -pthread -g3 
# -fsanitize=address
CC		= cc
RM		= rm -f


all: $(NAME)

$(NAME):
	$(CC) $(CFLAG)	$(M_SRCS) -o $(NAME)

clean: 
	$(RM) $(M_OBJCS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norminette:
	norminette *.c 
