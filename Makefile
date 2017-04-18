# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/31 14:56:28 by nbouchin          #+#    #+#              #
#    Updated: 2017/04/12 13:49:57 by nbouchin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= gcc
FLAGS	= -Wall -Wextra -Werror
LIB		= libft/libft.a
HEADER	= include/
LIBSRC	= libft/
SRCDIR	= src/
OBJDIR	= obj/
SRC		= catch_error.c     env_utils.c       ft_env.c          prompt.c \
		cd_utils.c        free_tab.c        minishell.c       tab_processing.c \
		env_expand.c      ft_cd.c           minishell_utils.c unset_env.c \
		env_processing.c  ft_echo.c         path_processing.c	free_cd_data.c \
		cd_error.c

# colors

GRN		=	\033[0;32m
RED		=	\033[0;31m
CYN		=	\033[0;36m
NC		=	\033[0m

SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJS	= $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(FLAGS) -L./$(LIBSRC) -lft -o $(NAME) $(OBJS)
	@echo "\n${CYN}PROCESSING DONE !${NC}"

$(LIB):
	@echo "${CYN}Processing ${NC}./libft/obj ${CYN}[${NC}...${CYN}]${NC}"
	@make -C $(LIBSRC)
	@echo "\n${CYN}Processing ${NC}./obj ${CYN}[${NC}...${CYN}]${NC}"

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)$(NAME).h
	@echo "${GRN}Compiling${NC} $@"
	@$(CC) $(FLAGS) -c -o $@ $< -I $(HEADER)

clean:
	@echo "${RED}Cleaning ${NC}./obj/ ${RED}[${NC}...${RED}]${NC}"
	@rm -rf $(OBJS)
	@echo "${RED}Cleaning ${NC}./libft/obj/ ${RED}[${NC}...${RED}]${NC}"
	@make -C $(LIBSRC) clean

fclean: clean
	@echo "${RED}Cleaning ${NC}./${RED}ft_ls${NC}"
	@rm -Rf $(NAME)
	@echo "${RED}Cleaning ${NC}./libft/${RED}libft.h${NC}\n"
	@make -C $(LIBSRC) fclean
	@echo "${RED}DELET DONE !${NC}"

re: fclean all

.PHONY: all clean fclean re
