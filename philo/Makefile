# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 20:32:15 by mkiflema          #+#    #+#              #
#    Updated: 2023/09/02 23:02:39 by mkiflema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

M_SRCS	= main.c utils.c  philo.c   routine.c pickup_down_forks.c \
			time_handler.c checker.c display_msg.c clear_free.c
			

CFLAGS	=  -Wextra -Werror -Wall  -g3 
lthread = -pthread
CC		= cc
RM		= rm -rf

M_OBJS = $(M_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(M_OBJS)
	$(CC) $(CFLAGS) $(lthread) $(M_SRCS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(M_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

