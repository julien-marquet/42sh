/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   types.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 14:34:12 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 02:33:47 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <unistd.h>
# include <termios.h>
# include "../libs/Libft/libft.h"

typedef enum	e_job_status
{
	running,
	exited,
	signaled,
	stopped,
	continued,
}				t_job_status;

typedef struct	s_cur_abs_pos
{
	int		row;
	int		col;
}				t_cur_abs_pos;

typedef struct	s_sh_state
{
	struct termios	term_state;
	struct termios	term_state_backup;
	unsigned char	status;
	size_t			exit_sig;
	t_list			*internal_storage;
	t_list			*aliases;
	int				shell_pid;
}				t_sh_state;

typedef struct	s_dyn_buf
{
	size_t	len;
	size_t	size;
	char	*buf;
}				t_dyn_buf;

typedef struct	s_input_data
{
	t_dyn_buf		*active_buf;
	t_dyn_buf		*build_buf;
	t_dyn_buf		*stored_buf;
	t_dyn_buf		*initial_buf;
	t_list			*history_list;
	size_t			rel_cur_pos;
	size_t			processed_chars;
	t_cur_abs_pos	*start_pos;
	int				enter;
	size_t			sig_call;
}				t_input_data;

typedef struct	s_win_data
{
	int				err;
	int				resized;
	struct winsize	ws;
}				t_win_data;

typedef struct	s_internal_storage
{
	char	*string;
	int		exported;
	int		new_entry;
}				t_internal_storage;

typedef struct	s_fds
{
	int		in;
	int		out;
	int		err;
}				t_fds;


typedef struct	s_builtin_context
{
	char	*origin;
	t_fds	fds;
}				t_builtin_context;

/*
** t_arg	t_cmd->arg constructor
*/

typedef struct		s_arg {
	char			*arg;
	int				type;
	struct s_arg	*next;
}					t_arg;

/*
** t_file	Parsed redirections
**
** char		*file = Redirection file / Heredoc end
** char		*here = Heredoc output
** int		*type = Redirection type (t_ctype)
*/

typedef struct		s_file {
	char			*file;
	char			*here;
	int				*type;
	struct s_file	*next;
}					t_file;

/*
** t_cmd	Parsed command
**
** char		**arg = Command arguments
** char		*red = Redirection type
** t_file	*in = Inputs
** t_file	*out = Outputs
*/

typedef struct		s_cmd {
	char			*str;
	char			**arg;
	char			type;
	char			*red;
	t_file			*in;
	t_file			*out;
	struct s_cmd	*next;
}					t_cmd;

/*
** t_ctype	Chevron redirection type
*/

typedef enum		e_ctype {
	C_IN = 0,
	C_LEN,
	C_OUT,
	C_TYPE
}					t_ctype;

typedef struct	s_proc
{
	int				pid;
	t_job_status	status;
	int				code;
	char			*name;
	int				updated;
	int				last;
	t_cmd			*remaining;
}				t_proc;

typedef struct	s_proc_grp
{
	t_list	*procs;
	int		pgid;
	char	*name;
}				t_proc_grp;

typedef struct	s_jobs
{
	t_list	*proc_grps;
	int		busy;
}				t_jobs;

typedef struct	s_context
{
	int					background;
	t_list				*rem_cmd;
	t_proc_grp			*proc_grp;
	t_builtin_context	*builtin_context;
	char				*prev_ex_flag;
	int					last;
}				t_context;

typedef int		(*t_exec_func)(t_sh_state *, const char **parsed,
				t_context *context);
typedef int		(*t_builtin_func)(t_sh_state *, int ac, const char **av,
				t_builtin_context *context);

#endif
