/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:48:54 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 19:18:33 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/prompt.h"

static int		prompt_mode(int mode_modifier)
{
	static int	mode = PROMPT_SIMPLE;

	if ((mode_modifier == PROMPT_SIMPLE || mode_modifier == PROMPT_MULTI) &&
mode_modifier != mode)
		mode = mode_modifier;
	return (mode);
}

static size_t	print_classic_prompt(int mode_modifier)
{
	size_t	display_len;
	int		mode;
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

static size_t	print_searched_mode_prompt(int mode_modifier)
{
	const char	*searched;
	size_t		display_len;

	if ((searched = get_searched()) == NULL)
		display_len = PROMPT_SEARCH_DISPLAY_LEN + 2;
	else
		display_len = PROMPT_SEARCH_DISPLAY_LEN + ft_strlen(searched) + 2;
	if (mode_modifier != PROMPT_NO_PRINT)
	{
		write(1, PROMPT_SEARCH_TXT, PROMPT_SEARCH_BUF_LEN);
		ft_putstr_fd(searched, 1);
		write(1, ": ", 2);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
	}
	return (display_len);
}

/*
** Print the prompt if modifier != PROMPT_NO_PRINT
** Update Prompt mode if modifer == (PROMPT_SIMPLE || PROMPT_MULTI)
** PROMPT_NO_SET -> just print the prompt
** @return PROMPT LEN
*/

size_t			print_prompt(int mode_modifier)
{
	if (get_search_mode() == 0)
		return (print_classic_prompt(mode_modifier));
	else
		return (print_searched_mode_prompt(mode_modifier));
}

size_t			get_prompt_len(void)
{
	return (print_prompt(PROMPT_NO_PRINT));
}
