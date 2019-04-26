/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_position.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/03 19:02:09 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 03:42:32 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/cursor/cursor_position.h"
#include "errno.h"
/*
**	return start position (without prompt len)
**	update start position if scroll detected
*/

int		update_start_position(t_dyn_buf *active_buf,
t_cur_abs_pos *start_pos)
{
	int				win_col;
	int				win_row;
	t_cur_abs_pos	last_pos;

	if ((win_col = get_win_col()) == -1 || (win_row = get_win_row()) == -1)
		return (1);
	last_pos.row = get_prompt_len() / win_col;
	last_pos.col = get_prompt_len() % win_col + start_pos->col;
	if (sim_cursor_movements(start_pos, &last_pos, active_buf, 0) == 1)
		return (1);
	if (last_pos.row + start_pos->row >= win_row)
		start_pos->row -= (last_pos.row + 1 + start_pos->row) % win_row;
	if (start_pos->row < 0)
		start_pos->row = 0;
	reset_win_resized_value();
	return (0);
}

/*
**	Return absolute cursor position
*/

int		get_cursor_position(t_cur_abs_pos *pos, t_dyn_buf *active_buf,
size_t rel_cur_pos, t_cur_abs_pos *start_pos)
{
	int				win_col;
	size_t			i;
	int	 			resize;

	if ((resize = win_has_been_resized()))
	{
		if (update_start_position(active_buf, start_pos) == 1)
			return (1);
	}
	if ((win_col = get_win_col()) == -1)
		return (1);
	pos->col = get_prompt_len() % win_col + start_pos->col;
	pos->row = get_prompt_len() / win_col + start_pos->row;
	i = sim_cursor_movement_light(active_buf, rel_cur_pos, pos, win_col);
	if (resize)
		print_anew(start_pos, active_buf, rel_cur_pos);
	return (0);
}


static void	process_location_termcaps(size_t i, size_t len, unsigned char str[16], t_cur_abs_pos *pos)
{
	while (++i < len)
	{
		if (!(str[i] < ' ' || '~' < str[i]))
		{
			if (str[i] == '[')
				pos->row = ft_atoi((char *)&(str[++i])) - 1;
			else if (str[i] == ';')
				pos->col = ft_atoi((char *)&(str[++i])) - 1;
		}
	}
}


/*
**	Get Cursor position by parsing the string returned
**	after a certain termcaps is sent
**	artificially converted to origin 0
*/

int		ask_start_position(t_cur_abs_pos *pos)
{
	size_t			len;
	unsigned char	str[16];
	size_t			i;
	ssize_t			ret;

	len = 0;
	i = 0;
	write(0, "\033[6n", 4);
	while (len < sizeof(str) - 1 && (ret = read(0, str + len, 1)) == 1)
	{
		if (str[len++] == 'R')
			break ;
	}
	if (ret == -1)
		return (1);
	str[len] = '\0';
	process_location_termcaps(i, len, str, pos);
	return (0);
}
