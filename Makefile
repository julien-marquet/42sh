# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/07 17:49:46 by jmarquet     #+#   ##    ##    #+#        #
#    Updated: 2019/04/21 01:02:40 by jmarquet    ###    #+. /#+    ###.fr      #
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

CFOLDERS = $(addprefix $(OBJ_DIR)/, storage \
editing editing/cursor editing/history editing/input \
data data/win_data data/dyn_buf data/data_utils \
builtins builtins/builtins_storage builtins/builtins_aliases \
builtins/builtin_hash builtins/builtin_echo builtins/builtins_jobs \
jobs jobs/jobs_procs jobs/jobs_proc_grps \
aliases \
parse parse/alias parse/expand \
exec)

# C FILES

CFILES = main.c sh.c sh_state.c term_state.c signal_handler.c error_handler.c
CFILES += $(addprefix editing/, prompt.c)
CFILES += $(addprefix editing/cursor/, cursor_utils.c cursor_basic_moves.c cursor_complex_moves.c cursor_vertical_moves.c cursor_position.c cursor_simulation.c)
CFILES += $(addprefix editing/history/, history_edition.c history_navigation.c history_utils.c)
CFILES += $(addprefix editing/input/, input_control.c input_action_handlers.c input_bufs_utils.c input_call_history.c input_capabilities_dispatchers.c input_handlers.c input_main_process.c input_utils.c input_validator.c)
CFILES += $(addprefix parse/, check.c chev.c chev_create.c free.c split.c token.c parse.c utils.c localvar.c)
CFILES += $(addprefix parse/alias/, alias.c skiplst.c)
CFILES += $(addprefix parse/expand/, expand_tilde.c expand_param.c expand_error.c expand.c)
CFILES += $(addprefix data/, input_data.c)
CFILES += $(addprefix data/data_utils/, data_utils_lst.c data_utils_str.c data_utils_arr.c)
CFILES += $(addprefix data/dyn_buf/, dyn_buf_manipulations.c dyn_buf_setters.c)
CFILES += $(addprefix data/win_data/, win_data_getters.c win_data_manipulations.c)
CFILES += $(addprefix storage/, storage_getters.c storage_manipulations.c storage_env.c storage_utils.c)
CFILES += $(addprefix builtins/, builtins_utils.c builtin_exit.c builtins_dispatcher.c builtins_execution.c)
CFILES += $(addprefix builtins/builtins_storage/, builtin_export.c builtin_unset.c builtin_unsetenv.c builtin_set.c builtin_env.c builtin_setenv.c)
CFILES += $(addprefix builtins/builtin_hash/, builtin_hash.c table.c utils.c)
CFILES += $(addprefix builtins/builtins_aliases/, builtin_alias.c builtin_unalias.c)
CFILES += $(addprefix builtins/builtin_echo/, builtin_echo.c builtin_echo_utils.c)
CFILES += $(addprefix builtins/builtins_jobs/, builtin_fg.c builtin_jobs.c builtin_bg.c)
CFILES += $(addprefix aliases/, aliases_getters.c aliases_manipulations.c aliases_utils.c)
CFILES += $(addprefix jobs/, jobs_printers.c jobs_controls.c jobs_display.c jobs_flush.c jobs_super.c jobs_update.c)
CFILES += $(addprefix jobs/jobs_procs/, jobs_procs_getters.c jobs_procs_setters.c)
CFILES += $(addprefix jobs/jobs_proc_grps/, jobs_proc_grps_getters.c jobs_proc_grps_setters.c)
CFILES += $(addprefix exec/, exec.c exec_utils.c exec_binary.c exec_dispatcher.c exec_by_flag.c exec_cmd_checkers.c )

SRCS = $(addprefix $(PATH)$(SRC_DIR)/, $(CFILES))
OBJ = $(addprefix $(PATH)$(OBJ_DIR)/, $(CFILES:.c=.o))

# HEADER FILES

TMPFILES = common.h sh.h sh_state.h term_state.h signal_handler.h types.h error_handler.h
TMPFILES += $(addprefix parse/, parse.h utils.h expand.h localvar.h parse_alias.h)
TMPFILES += $(addprefix editing/, prompt.h)
TMPFILES += $(addprefix editing/history/, history.h history_edition.h history_navigation.h history_utils.h)
TMPFILES += $(addprefix editing/input/, input.h input_control.h input_action_handlers.h input_bufs_utils.h input_call_history.h input_capabilities_dispatchers.h input_handlers.h input_main_process.h input_utils.h input_validator.h)
TMPFILES += $(addprefix editing/cursor/, cursor.h cursor_utils.h cursor_basic_moves.h cursor_complex_moves.h cursor_vertical_moves.h cursor_position.h cursor_simulation.h)
TMPFILES += $(addprefix data/, input_data.h)
TMPFILES += $(addprefix data/data_utils/, data_utils.h data_utils_lst.h data_utils_str.h data_utils_arr.h)
TMPFILES += $(addprefix data/dyn_buf/, dyn_buf.h dyn_buf_manipulations.h dyn_buf_setters.h)
TMPFILES += $(addprefix data/win_data/, win_data.h win_data_defines.h win_data_getters.h win_data_manipulations.h)
TMPFILES += $(addprefix storage/, storage.h storage_getters.h storage_env.h storage_utils.h storage_manipulations.h)
TMPFILES += $(addprefix builtins/, builtins_utils.h builtin_exit.h builtins_dispatcher.h builtins_execution.h builtins_defines.h builtins.h)
TMPFILES += $(addprefix builtins/builtins_storage/, builtin_export.h builtin_unset.h builtin_unsetenv.h builtin_set.h builtin_env.h builtin_setenv.h builtins_storage.h)
TMPFILES += $(addprefix builtins/builtin_test/, builtin_test.h)
TMPFILES += $(addprefix builtins/builtin_hash/, builtin_hash.h)
TMPFILES += $(addprefix builtins/builtins_aliases/, builtins_aliases.h builtin_alias.h builtin_unalias.h)
TMPFILES += $(addprefix builtins/builtin_echo/, builtin_echo.h builtin_echo_utils.h)
TMPFILES += $(addprefix builtins/builtins_jobs/, builtin_bg.h builtin_fg.h builtins_jobs.h builtin_jobs.h)
TMPFILES += $(addprefix aliases/, aliases.h aliases_getters.h aliases_manipulations.h aliases_utils.h)
TMPFILES += $(addprefix jobs/, jobs_printers.h jobs.h jobs_controls.h jobs_display.h jobs_flush.h jobs_super.h jobs_update.h)
TMPFILES += $(addprefix jobs/jobs_procs/, jobs_procs.h jobs_procs_getters.h jobs_procs_setters.h)
TMPFILES += $(addprefix jobs/jobs_proc_grps/, jobs_proc_grps.h jobs_proc_grps_getters.h jobs_proc_grps_setters.h)
TMPFILES += $(addprefix exec/, exec.h exec_utils.h exec_binary.h exec_dispatcher.h exec_by_flag.h exec_cmd_checkers.h)

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
