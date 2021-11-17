# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/04 03:12:03 by kwonhyukbae       #+#    #+#              #
#    Updated: 2021/11/17 15:31:19 by hkwon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
#CFLAGS = -g3 -fsanitize=address
AR = ar rc
RM = rm -f

INCLUDE_DIR = ./includes
SRCS_DIR = ./srcs
LIB_DIR = ./libft

SRCS_BUILTIN_DIR = $(SRCS_DIR)/builtin_func
SRCS_BUILTIN = $(addprefix $(SRCS_BUILTIN_DIR)/, \
		ft_echo.c \
		ft_cd.c \
		ft_pwd.c \
		ft_export.c \
		ft_export2.c \
		ft_unset.c \
		ft_env.c \
		ft_exit.c \
)

SRCS_INIT_DIR = $(SRCS_DIR)/init
SRCS_INIT = $(addprefix $(SRCS_INIT_DIR)/, \
		init_shell.c\
		init_line.c\
		init_check.c\
		init_special_check.c\
)

SRCS_PARSE_DIR = $(SRCS_DIR)/parsing
SRCS_PARSE = $(addprefix $(SRCS_PARSE_DIR)/, \
		parse_start.c\
		parse_line.c\
		parse_token.c\
		parse_token_arr.c\
		parse_token_quote.c\
		parse_normal_string.c\
		parse_dquote_string.c\
		parse_token_list.c\
)

SRCS_RUN_DIR = $(SRCS_DIR)/run
SRCS_RUN = $(addprefix $(SRCS_RUN_DIR)/, \
		minishell.c\
		builtin.c\
		inner.c\
		pipe.c\
		redirect.c\
		redirect_close.c\
)

SRCS_UTILS_DIR = $(SRCS_DIR)/utils
SRCS_UTILS = $(addprefix $(SRCS_UTILS_DIR)/, \
		find.c\
		print.c\
		utils.c\
		free.c\
)

SRCS_MAIN = $(addprefix $(SRCS_DIR)/, \
		main.c)

SRCS = \
	$(SRCS_MAIN) \
	$(SRCS_INIT) \
	$(SRCS_PARSE) \
	$(SRCS_RUN) \
	$(SRCS_BUILTIN) \
	$(SRCS_UTILS) \

# OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

vpath %.c \
	$(SRCS_DIR) \
	$(SRCS_INIT_DIR) \
	$(SRCS_PARSE_DIR) \
	$(SRCS_RUN_DIR) \
	$(SRCS_BUILTIN_DIR) \
	$(SRCS_UTILS_DIR) \

all : $(NAME)

$(NAME) : $(LIBFT)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -I $(LIB_DIR)/$(INCLUDE_DIR) \
	-L ./$(LIB_DIR) -lreadline -L/Users/hkwon/.brew/opt/readline/lib -I/Users/hkwon/.brew/opt/readline/include \
	-lft -o $(NAME) $(SRCS)

# 우분투용 Make
# $(NAME) : $(LIBFT)
# 	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -I $(LIB_DIR)/$(INCLUDE_DIR) \
# 	-o $(NAME) $(SRCS) $(LIB_DIR)/libft.a -lreadline

$(LIBFT) :
	@make -C $(LIB_DIR)
	@cp $(LIB_DIR)/$(LIBFT) .

clean :
	@$(RM) -r $(OBJS_DIR)
	@make -C $(LIB_DIR) clean

fclean : clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@make -C $(LIB_DIR) fclean

re : fclean all

.PHONY : all clean fclean re
