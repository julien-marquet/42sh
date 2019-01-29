/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 00:52:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/29 23:13:03 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "common.h"
#include "input.h"
#include "input_utils.h"

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

int		handle_input(t_sh_state *sh_state, t_input_buf *input_buf)
{
	print_prompt();
	get_input(sh_state, input_buf);
	return (0);
}

char	*get_input(t_sh_state *sh_state, t_input_buf *input_buf)
{
	char	*input;
	char	buf[READ_SIZE + 1];
	ssize_t	ret;

	input = NULL;
	sh_state->exit_sig = 0;
	ft_bzero(&buf, READ_SIZE);
	ret = read(0, &buf, READ_SIZE);
	append_input_buf(buf, input_buf);
	ft_putendl(input_buf->buf);
	return (input);
}
