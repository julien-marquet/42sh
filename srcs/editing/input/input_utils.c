/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_utils.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 18:12:45 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 01:45:16 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_utils.h"

int		count_escape_chars(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && !(str[i] >= '\010' &&
str[i] <= '\011') && str[i] <= '\037')
		i++;
	return (i);
}

int		is_capability(char *s)
{
	int		is_cap;

	is_cap = *s > '\0' && *s <= '\037';
	is_cap |= *s == '\177';
	is_cap |= (*s == '\303' && *(s + 1) == '\247');
	is_cap |= (*s == '\342' && *(s + 1) == '\210' && *(s + 2) == '\232');
	is_cap |= (*s == '\342' && *(s + 1) == '\211' && *(s + 2) == '\210');
	return (is_cap);
}

int		is_sig(char *s)
{
	return (*s == '\04' || *s == '\03' || *s == '\032');
}

int		is_escaped(char *str, size_t i)
{
	int		escape_cpt;

	escape_cpt = 0;
	while (i > 0)
	{
		if (str[i - 1] == '\\')
			escape_cpt++;
		else
			break ;
		i--;
	}
	return (escape_cpt % 2);
}
