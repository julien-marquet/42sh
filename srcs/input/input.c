/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 00:52:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/31 23:30:47 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "input/input.h"
#include "input/input_utils.h"

/*
**	Get Cursor position by parsing the string returned
**	after a certain termcaps is sent
*/

int		get_cursor_position(t_cur_abs_pos *pos)
{
	size_t			len;
	unsigned char	str[16];
	size_t			i;

	len = 0;
	i = 0;
	write(0, "\x1B[6n", 4);
	while (len < sizeof(str) - 1 && read(0, str + len, 1) == 1)
	{
		if (str[len++] == 'R')
			break ;
	}
	str[len] = '\0';
	while (++i < len)
	{
		if (!(str[i] < ' ' || '~' < str[i]))
		{
			if (str[i] == '[')
				pos->row = ft_atoi((char *)&(str[++i]));
			else if (str[i] == ';')
				pos->col = ft_atoi((char *)&(str[++i]));
		}
	}
	return (0);
}

/*
**	TODO GOTO first line WHEN MULTI-LINE
*/

int		clear_line(void)
{
	t_cur_abs_pos	pos;

	if (get_cursor_position(&pos) != 0)
		return (1);
	tputs(tgoto(tgetstr("cm", NULL), 0, pos.row), 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	return (0);
}

int		print_prompt(void)
{
	ft_putstr(PROMPT_PLACEHOLDER);
	return (0);
}

int		handle_capabilities(t_input_data *input_data,
t_sh_state *sh_state, int *send_input)
{
	int		res;
	input_data->input_buf->len += 0;
	sh_state->status += 0;
	res = 0;
	if (input_data->build_buf->buf[0] == '\n' && (res = 1))
		*send_input = 1;
	if (ft_strcmp(input_data->build_buf->buf, KEY_ARROW_LEFT) == 0 && (res = 1))
		write(1, "[Le]", 4);
	else if (ft_strcmp(input_data->build_buf->buf, KEY_ARROW_RIGHT) == 0 && (res = 1))
		write(1, "[Ri]", 4);
	if (ft_strcmp(input_data->build_buf->buf, KEY_ARROW_UP) == 0 && (res = 1))
		write(1, "[Up]", 4);
	else if (ft_strcmp(input_data->build_buf->buf, KEY_ARROW_DOWN) == 0 && (res = 1))
		write(1, "[Down]", 6);
	else if (ft_strcmp(input_data->build_buf->buf, KEY_SIGINT) == 0 && (res = 1))
	{
		*send_input = 1;
		sh_state->exit_sig = 1;
		sh_state->status = 2;
	}
	return (res);
}

int		get_buf(t_dyn_buf *build_buf)
{
	char	buf[READ_SIZE + 1];
	ssize_t	ret;

	ret = READ_SIZE;
	while (ret >= READ_SIZE)
	{
		ft_bzero(buf, READ_SIZE + 1);
		ret = read(0, &buf, READ_SIZE);
		if (ret == -1 || append_dyn_buf(buf, build_buf) != 0)
			return (1);
	}
	return (0);
}

int		handle_input(t_sh_state *sh_state, t_input_data *input_data)
{
	int		send_input;
	int		is_cap;

	send_input = 0;
	print_prompt();
	while (send_input == 0)
	{
		if (get_buf(input_data->build_buf) != 0)
			return (1);
		is_cap = handle_capabilities(input_data, sh_state, &send_input);
		if (is_cap == -1)
			return (1);
		else if (is_cap == 0)
		{
			append_dyn_buf(input_data->build_buf->buf, input_data->input_buf);
			ft_putstr(input_data->build_buf->buf);
		}
		reset_dyn_buf(input_data->build_buf);
	}
	return (0);
}