/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   common.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 18:35:08 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/28 23:25:54 by jmarquet    ###    #+. /#+    ###.fr     */
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

typedef struct	s_buffer
{
	char	*content;
	size_t	size;
	size_t	len;
}				t_buffer;

typedef struct	s_sh_input
{
	unsigned int	wrapped;
	unsigned int	insert_mode;
	t_buffer		i_buffer;
	t_buffer		o_buffer;
	size_t			prompt_len;
	size_t			cursor_pos;
}				t_sh_input;

typedef struct	s_sh_state
{
	struct termios	term_state;
	struct termios	term_state_backup;
	t_sh_input		input;
	size_t			status;
}				t_sh_state;

#endif
