/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   types.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 14:34:12 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 03:25:17 by jmarquet    ###    #+. /#+    ###.fr     */
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

typedef struct	s_proc
{
	int				pid;
	t_job_status	status;
	int				code;
	char			*name;
	int				updated;
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

typedef struct	s_context
{
	int					background;
	t_proc_grp			*proc_grp;
	t_builtin_context	*builtin_context;
}				t_context;


#endif
