# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/07 17:49:46 by jmarquet     #+#   ##    ##    #+#        #
#    Updated: 2019/04/05 15:03:24 by mmoya       ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = 42sh

PATH = ./
SRC_DIR = srcs
OBJ_DIR = objs
HEAD_DIR = incl
LIB_DIR = libs

# C FOLDERS LIST

CFOLDERS = $(addprefix $(OBJ_DIR)/, editing data editing/cursor editing/history editing/input parse)

# C FILES

CFILES = main.c sh.c sh_state.c term_state.c signal_handler.c
CFILES += $(addprefix editing/, prompt.c)
CFILES += $(addprefix editing/cursor/, cursor_utils.c cursor_basic_moves.c cursor_complex_moves.c cursor_vertical_moves.c cursor_position.c cursor_simulation.c)
CFILES += $(addprefix editing/history/, history_edition.c history_navigation.c history_utils.c)
CFILES += $(addprefix editing/input/, input_control.c input_action_handlers.c input_bufs_utils.c input_call_history.c input_capabilities_dispatchers.c input_handlers.c input_main_process.c input_utils.c input_validator.c)
CFILES += $(addprefix data/, dyn_buf.c input_data.c win_data.c)
CFILES += $(addprefix parse/, check.c chev.c expand_tilde.c expand.c free.c split.c token.c parse.c utils.c)

SRCS = $(addprefix $(PATH)$(SRC_DIR)/, $(CFILES))
OBJ = $(addprefix $(PATH)$(OBJ_DIR)/, $(CFILES:.c=.o))

# HEADER FILES

TMPFILES = common.h sh.h sh_state.h term_state.h signal_handler.h parse.h
TMPFILES += $(addprefix editing/, prompt.h)
TMPFILES += $(addprefix editing/history/, history.h history_edition.h history_navigation.h history_utils.h)
TMPFILES += $(addprefix editing/input/, input.h input_control.h input_action_handlers.h input_bufs_utils.h input_call_history.h input_capabilities_dispatchers.h input_handlers.h input_main_process.h input_utils.h input_validator.h)
TMPFILES += $(addprefix editing/cursor/, cursor.h cursor_utils.h cursor_basic_moves.h cursor_complex_moves.h cursor_vertical_moves.h cursor_position.h cursor_simulation.h)
TMPFILES += $(addprefix data/, dyn_buf.h input_data.h win_data.h)


HFILES = $(addprefix $(PATH)$(HEAD_DIR)/, $(TMPFILES))

LIB_NAME = ft
PATH_LIBFT = $(PATH)$(LIB_DIR)/Libft/
LIB = $(addprefix $(PATH_LIBFT), lib$(LIB_NAME).a)

CC := $(shell whereis gcc)
AR := $(shell whereis ar)
RM := $(shell whereis rm)
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
P_FLAGS = -lcurses

export CC
export AR
export RM
export FLAGS

.PHONY: clean, fclean, all, re, lib

all: lib $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(CC) $(FLAGS) $(P_FLAGS) -o $(NAME) -L$(PATH_LIBFT) -l$(LIB_NAME) $(OBJ) -I $(PATH)$(HEAD_DIR)
lib:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(CFOLDERS)
	@$(MAKE) -eC $(PATH_LIBFT)
$(PATH)$(OBJ_DIR)/%.o:$(PATH)$(SRC_DIR)/%.c $(HFILES)
	$(CC) $(FLAGS) -c $< -o $@ -I $(PATH)$(HEAD_DIR)
clean:
	$(MAKE) -eC $(PATH_LIBFT) clean
	$(RM) -Rf $(PATH)$(OBJ_DIR)
fclean: clean
	$(MAKE) -eC $(PATH_LIBFT) fclean
	$(RM) -f $(NAME)
re: fclean all
