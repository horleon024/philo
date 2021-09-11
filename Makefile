# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/13 13:48:05 by lhorefto          #+#    #+#              #
#    Updated: 2021/07/15 15:53:43 by lhorefto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	main.c utils.c actions.c init.c errors.c
OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror 
HEADER			= philo.h

NAME			= philo

all:			$(NAME)

$(NAME):		$(HEADER)
				$(CC) $(CFLAGS) $(SRCS) -lpthread -o $(NAME) $(HEADER)

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)
