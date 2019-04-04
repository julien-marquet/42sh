/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_handlers.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 17:51:47 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 20:14:08 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "input/input_handlers.h"



int		handle_capabilities(t_input_data *input_data, t_list *hist_copy)
{
	int	res;

	if ((res = capabilities_dispatcher_1(input_data)) != 0)
		return (res == -1);
	if ((res = capabilities_dispatcher_2(input_data)) != 0)
		return (res == -1);
	if ((res = capabilities_dispatcher_3(input_data)) != 0)
		return (res == -1);
	if ((res = capabilities_dispatcher_4(input_data, hist_copy)) != 0)
		return (res == -1);
	else
		input_data->processed_chars = count_escape_chars(input_data->build_buf->buf);
	return (0);
}


int		handle_sig(t_input_data *input_data, t_sh_state *sh_state)
{
	t_cur_abs_pos pos;

	sh_state->exit_sig = sh_state->exit_sig;
	if ((ft_strncmp(input_data->build_buf->buf, CTRL_C, 1) == 0) && (input_data->processed_chars = 1))
	{
		input_data->sig_call = 1;
		if (get_cursor_position(&pos, input_data->active_buf, input_data->active_buf->len ,input_data->start_pos) == 1)
			return (1);
		if (tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar) != 0)
			return (1);
		write(1, "\n", 1);
	}
	else if ((ft_strncmp(input_data->build_buf->buf, CTRL_D, 1) == 0) && (input_data->processed_chars = 1))
		exit_sh(sh_state, input_data);
	else if ((ft_strncmp(input_data->build_buf->buf, CTRL_Z, 1) == 0) && (input_data->processed_chars = 1))
		dprintf(2, "SUSPEND SIG\n");
	return (0);
}


int		handle_insertion(t_input_data *input_data)
{
	size_t		i;

	i = 0;
	while (i < input_data->build_buf->len && !is_capability(&(input_data->build_buf->buf[i])))
		i++;
	input_data->processed_chars = i;
	if (insertn_dyn_buf(input_data->build_buf->buf, input_data->active_buf, input_data->rel_cur_pos, i) == 1)
		return (1);
	return (insertn_chars(input_data, input_data->build_buf->buf, i, 0));
}