# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/07 17:49:46 by jmarquet     #+#   ##    ##    #+#        #
#    Updated: 2019/01/29 23:10:10 by jmarquet    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = 42sh

PATH = ./
SRC_DIR = srcs
OBJ_DIR = objs
HEAD_DIR = incl
LIB_DIR = libs
CFILES = main.c sh.c sh_state.c term_state.c input.c input_buf.c
SRCS = $(addprefix $(PATH)$(SRC_DIR)/, $(CFILES))

HEADER_FILE = $(addprefix $(PATH)$(HEAD_DIR)/, common.h sh.h sh_state.h term_state.h input.h input_utils.h input_buf.h)
OBJ = $(addprefix $(PATH)$(OBJ_DIR)/, $(CFILES:.c=.o))

LIB_NAME = ft
PATH_LIBFT = $(PATH)$(LIB_DIR)/Libft/
LIB = $(addprefix $(PATH_LIBFT), lib$(LIB_NAME).a)

CC := $(shell whereis gcc)
AR := $(shell whereis ar)
RM := $(shell whereis rm)
FLAGS = -Wall -Wextra -Werror -fsanitize=address -g
P_FLAGS = -lcurses

export CC
export AR
export RM
export FLAGS

.PHONY: clean, fclean, all, re, lib

all: lib $(NAME)

$(NAME): $(LIB) $(OBJ) $(HEADER_FILE)
	$(CC) $(FLAGS) $(P_FLAGS) -o $(NAME) -L$(PATH_LIBFT) -l$(LIB_NAME) $(OBJ) -I $(PATH)$(HEAD_DIR)
lib:
	@mkdir -p $(OBJ_DIR)
	@$(MAKE) -eC $(PATH_LIBFT)
$(PATH)$(OBJ_DIR)/%.o:$(PATH)$(SRC_DIR)/%.c $(HEADER_FILE)
	$(CC) $(FLAGS) -c $< -o $@ -I $(PATH)$(HEAD_DIR)
clean:
	$(MAKE) -eC $(PATH_LIBFT) clean
	$(RM) -Rf $(PATH)$(OBJ_DIR)
fclean: clean
	$(MAKE) -eC $(PATH_LIBFT) fclean
	$(RM) -f $(NAME)
re: fclean all
