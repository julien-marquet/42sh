/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:48:54 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 18:38:22 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/prompt.h"

static int	prompt_mode(int mode_modifier)
{
	static int	mode = PROMPT_SIMPLE;

	if ((mode_modifier == PROMPT_SIMPLE || mode_modifier == PROMPT_MULTI) &&
mode_modifier != mode)
		mode = mode_modifier;
	return (mode);
}

/*
** Print the prompt if modifier != PROMPT_NO_PRINT
** Update Prompt mode if modifer == (PROMPT_SIMPLE || PROMPT_MULTI)
** PROMPT_NO_SET -> just print the prompt
** @return PROMPT LEN
*/

size_t		print_prompt(int mode_modifier)
{
	int		mode;
	size_t	display_len;
	size_t	buf_len;

	mode = prompt_mode(mode_modifier);
	display_len = mode == PROMPT_SIMPLE ?
PROMPT_SIMPLE_DISPLAY_LEN : PROMPT_MULTI_DISPLAY_LEN;
	buf_len = mode == PROMPT_SIMPLE ?
PROMPT_SIMPLE_BUF_LEN : PROMPT_MULTI_BUF_LEN;
	if (mode_modifier != PROMPT_NO_PRINT)
	{
		if (mode == PROMPT_SIMPLE)
			write(1, PROMPT_SIMPLE_TXT, buf_len);
		else if (mode == PROMPT_MULTI)
			write(1, PROMPT_MULTI_TXT, buf_len);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
	}
	return (display_len);
}

size_t		get_prompt_len(void)
{
	return (print_prompt(PROMPT_NO_PRINT));
}
