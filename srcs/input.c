/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 00:52:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/29 05:50:47 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "common.h"
#include "input_utils.h"

/*
**	Get Cursor position by parsing the string returned
**	after a certain termcaps is sent
*/

t_cur_pos	get_cursor_position(void)
{
	t_cur_pos		pos;
	size_t			len;
	unsigned char	str[16];
	size_t			i;

	len = 0;
	i = 0;
	write(0, "\x1B[6n\n", 5);
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
				pos.row = ft_atoi((char *)&(str[++i]));
			else if (str[i] == ';')
				pos.col = ft_atoi((char *)&(str[++i]));
		}
	}
	return (pos);
}

int		clear_line(void)
{
	//tputs(tgoto(tgetstr("cm", NULL), 1, 1), 1, ft_putchar);
	return (0);
}

int		print_prompt(void)
{
	ft_putstr(PROMPT_PLACEHOLDER);
	return (0);
}

char	*handle_input(t_sh_state *sh_state)
{
	char	*input;

	input = NULL;
	print_prompt();
	input = get_input(sh_state);
	return (input);
}

char	*get_input(t_sh_state *sh_state)
{
	char	*input;
	char	buf[READ_SIZE + 1];
	ssize_t	ret;

	input = NULL;
	sh_state->exit_sig = 0;
	ft_bzero(&buf, READ_SIZE);
	ret = read(0, &buf, READ_SIZE);
	ft_putendl(buf);
	get_cursor_position();
	//clear_line();
	return (input);
}
