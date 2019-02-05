/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   common.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 18:35:08 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 22:25:55 by jmarquet    ###    #+. /#+    ###.fr     */
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
# include "win_data.h"

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

#endif
