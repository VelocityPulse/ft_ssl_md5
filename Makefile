# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchameyr <cchameyr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/21 12:14:25 by cchameyr          #+#    #+#              #
#    Updated: 2019/07/28 10:33:22 by cchameyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES =				main.c \
					md5.c \
					ssl_process.c \
					sha2.c

SRCS =				$(addprefix srcs/, $(FILES))

OBJS =				$(addprefix objs/, $(FILES:.c=.o))

CC =				gcc

NAME =				ft_ssl

LIBFT =				libft/libft.a

DEBUGSEGFAULT =		-g3 -fsanitize=address

FLAGS =				#-Wall -Wextra -Werror

RM =				rm -rf

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(DEBUGSEGFAULT) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJS):
	$(CC) $(FLAGS) $(DEBUGSEGFAULT) -c $(SRCS)
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
