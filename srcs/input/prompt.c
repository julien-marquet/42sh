/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:48:54 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/12 10:08:55 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "input/prompt.h"

static int	prompt_mode(int mode_modifier)
{
	static int	mode = PROMPT_SIMPLE;

	if ((mode_modifier == PROMPT_SIMPLE || mode_modifier == PROMPT_MULTI) &&
mode_modifier != mode)
		mode = mode_modifier;
	return (mode);
}

size_t		print_prompt(int mode_modifier)
{
	int		mode;
	size_t	len;

	mode = prompt_mode(mode_modifier);
	len = mode == PROMPT_SIMPLE ? PROMPT_SIMPLE_SIZE : PROMPT_MULTI_SIZE;
	if (mode_modifier != PROMPT_NO_PRINT)
	{
		if (mode == PROMPT_SIMPLE)
			write(1, PROMPT_SIMPLE_TXT, len);
		else if (mode == PROMPT_MULTI)
			write(1, PROMPT_MULTI_TXT, len);
	}
	return (len);
}

size_t		get_prompt_len(void)
{
	return (print_prompt(PROMPT_NO_PRINT));
}
