/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_sig_handlers.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 18:33:59 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 18:45:01 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_sig_handlers.h"

int		ctrl_c_handler(t_input_data *input_data)
{
	t_cur_abs_pos	pos;

	input_data->sig_call = 1;
	if (get_cursor_position(&pos, input_data->active_buf,
input_data->active_buf->len, input_data->start_pos) == 1)
		return (1);
	if (tputs(tgoto(tgetstr("cm", NULL), pos.col,
pos.row), 1, ft_putchar) != 0)
		return (1);
	write(1, "\n", 1);
	if (get_search_mode() == 1)
	{
		reset_dyn_buf(input_data->active_buf);
		set_search_mode(0);
	}
	return (0);
}

int		ctrl_d_handler(t_sh_state *sh_state, t_input_data *input_data)
{
	if (get_eof() == 1 && input_data->active_buf->len == 0)
		set_eof(2);
	else if (input_data->active_buf->len == 0 &&
	input_data->stored_buf->len == 0)
		exit_sh(sh_state, input_data);
	else
		write(1, "\a", 1);
	return (0);
}

int		ctrl_r_handler(t_sh_state *sh_state, t_input_data *input_data)
{
	char	*searched;
	int		result;

	if (get_search_mode() == 0)
	{
		set_search_mode(1);
		if (print_anew(input_data->start_pos, input_data->active_buf,
	input_data->rel_cur_pos) == 1)
			return (1);
	}
	else
	{
		searched = ft_strdup(get_searched());
		if ((result = find_in_history(sh_state, input_data,
	searched, 1)) <= 0)
		{
			ft_strdel(&searched);
			return (result == -1 ? 1 : 0);
		}
	}
	return (0);
}
