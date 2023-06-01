# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 20:32:15 by mkiflema          #+#    #+#              #
#    Updated: 2023/06/01 21:53:51 by mkiflema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

M_SRCS	= philo.c fork_handler.c  utils.c thread_handler.c  routine.c time_handler.c
M_OBJCS	= $(M_SRCS:.c=.o)

CFLAG	=  -Wextra -Werror -Wall
#  -g  -fsanitize=address
CC		= cc
RM		= rm -f


all: $(NAME)

$(NAME): $(M_OBJCS)
	$(CC) $(CFLAG)	$(M_OBJCS) -o $(NAME)

clean: 
	$(RM) $(M_OBJCS)

fclean: clean
	$(RM) $(NAME)

re: fclean all


