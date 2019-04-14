/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   types.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 14:34:12 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 17:48:30 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <unistd.h>
# include <termios.h>
# include "../libs/Libft/libft.h"

typedef struct  s_hash_table
{
   size_t   hits;
   char     *bin;
   char     *path;
}               t_hash_table;

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
        t_list                  *hash_table;
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


#endif
