/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   common.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 18:35:08 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 20:21:18 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef SH_COMMON_H
# define SH_COMMON_H

# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>
# include <unistd.h>
# include <termios.h>

# include "../libs/Libft/libft.h"

typedef struct	s_cur_abs_pos
{
	int		row;
	int		col;
}				t_cur_abs_pos;

typedef struct	s_sh_state
{
	struct termios	term_state;
	struct termios	term_state_backup;
	size_t			status;
	size_t			exit_sig;
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

#endif
