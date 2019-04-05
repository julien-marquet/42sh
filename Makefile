# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/07 17:49:46 by jmarquet     #+#   ##    ##    #+#        #
#    Updated: 2019/04/05 18:07:09 by jmarquet    ###    #+. /#+    ###.fr      #
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

CFOLDERS = $(addprefix $(OBJ_DIR)/, storage editing data data/dyn_buf editing/cursor editing/history editing/input)

# C FILES

CFILES = main.c sh.c sh_state.c term_state.c signal_handler.c
CFILES += $(addprefix editing/, prompt.c)
CFILES += $(addprefix editing/cursor/, cursor_utils.c cursor_basic_moves.c cursor_complex_moves.c cursor_vertical_moves.c cursor_position.c cursor_simulation.c)
CFILES += $(addprefix editing/history/, history_edition.c history_navigation.c history_utils.c)
CFILES += $(addprefix editing/input/, input_control.c input_action_handlers.c input_bufs_utils.c input_call_history.c input_capabilities_dispatchers.c input_handlers.c input_main_process.c input_utils.c input_validator.c)
CFILES += $(addprefix data/, input_data.c win_data.c lst_utils.c)
CFILES += $(addprefix data/dyn_buf/, dyn_buf_manipulations.c dyn_buf_setters.c)
CFILES += $(addprefix storage/, storage_getters.c storage_manipulations.c storage_env.c storage_utils.c)

SRCS = $(addprefix $(PATH)$(SRC_DIR)/, $(CFILES))
OBJ = $(addprefix $(PATH)$(OBJ_DIR)/, $(CFILES:.c=.o))

# HEADER FILES

TMPFILES = common.h sh.h sh_state.h term_state.h signal_handler.h types.h
TMPFILES += $(addprefix editing/, prompt.h)
TMPFILES += $(addprefix editing/history/, history.h history_edition.h history_navigation.h history_utils.h)
TMPFILES += $(addprefix editing/input/, input.h input_control.h input_action_handlers.h input_bufs_utils.h input_call_history.h input_capabilities_dispatchers.h input_handlers.h input_main_process.h input_utils.h input_validator.h)
TMPFILES += $(addprefix editing/cursor/, cursor.h cursor_utils.h cursor_basic_moves.h cursor_complex_moves.h cursor_vertical_moves.h cursor_position.h cursor_simulation.h)
TMPFILES += $(addprefix data/, input_data.h win_data.h lst_utils.h)
TMPFILES += $(addprefix data/dyn_buf/, dyn_buf.h dyn_buf_manipulations.h dyn_buf_setters.h)
TMPFILES += $(addprefix storage/, storage.h storage_getters.h storage_env.h storage_utils.h storage_manipulations.h)


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
