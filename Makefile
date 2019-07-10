# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/21 12:14:25 by cchameyr          #+#    #+#              #
#    Updated: 2019/07/10 15:43:13 by cchameyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES =				main.c \
					md5.c

SRCS =				$(addprefix srcs/, $(FILES))

OBJS =				$(addprefix objs/, $(FILES:.c=.o))

CC =				gcc

NAME =				ft_ssl

LIBFT =				libft/libft.a

DEBUGSEGFAULT =		-g3 -fsanitize=address

FLAGS =				-Wall -Wextra -Werror $(DEBUGSEGFAULT)

RM =				rm -rf

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJS):
	$(CC) $(FLAGS) -c $(SRCS)
	@make objs_mv

objs_mv:
	@mkdir objs
	@mv $(FILES:.c=.o) ./objs/

objs_rm:
	@$(RM) objs
	@$(RM) $(FILES:.c=.o)

$(LIBFT):
	make -C ./libft/

clean: objs_rm
	make clean -C ./libft/

fclean: clean
	$(RM) $(LIBFT) $(NAME)

re: fclean all

r: objs_rm
	$(RM) $(NAME)
	@make
