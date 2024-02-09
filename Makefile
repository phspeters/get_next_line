# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/09 17:00:05 by pehenri2          #+#    #+#              #
#    Updated: 2024/02/09 17:04:05 by pehenri2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			=	get_next_line.a
CC 				=	cc
CFLAGS 			=	-Wall -Wextra -Werror -Wunreachable-code -g3
HEADERS			=	-I ./include
SRC_PATH		=	./src/mandatory/
FILES			=	get_next_line.c	get_next_line_utils.c
SRC				=	$(addprefix $(SRC_PATH), $(FILES))
OBJS 			=	${SRC:%.c=%.o}
BONUS_PATH		=	./src/bonus/
FILES_BONUS 	=	get_next_line_bonus.c get_next_line_utils_bonus.c
SRC_BONUS		=	$(addprefix $(BONUS_PATH), $(FILES_BONUS))
OBJS_BONUS 		=	${SRC_BONUS:%.c=%.o}

${NAME}: $(OBJS)

bonus: $(OBJS_BONUS)

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ && printf "Compiling: $(notdir $<\n)"
	@ar rcs $(NAME) $@

norm:
	@norminette -R CheckForbiddenSourceHeader

clean:
	@rm -f $(OBJS)
	@rm -f $(OBJS_BONUS)
	@echo "Deleted object files"

fclean: clean
	@rm -f $(NAME)
	@echo "Deleted static library"

re: fclean all

all: $(NAME) bonus

.PHONY: clean fclean re all norm