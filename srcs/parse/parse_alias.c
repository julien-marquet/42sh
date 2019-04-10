/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_alias.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 20:03:25 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 17:04:59 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/parse_alias.h"

int		alias_replace(char *str, t_list *aliases, int i, int j)
{
	char *tmp;

	tmp = ft_strndup(str + j, i - j);
	dprintf(2, "alias of %s = %s\n", tmp, get_alias(aliases, tmp));
	return (0);
}

char		*parse_alias(char *str, t_list *aliases)
{
	int i;
	int j;
	int is_var;

	i = 0;
	while (str[i])
	{
		is_var = 0;
		while (str[i] && ft_isspace(str[i]))
			i++;
		j = i;
		while (str[i] && !ft_isspace(str[i]))
		{
			if (str[i] == '=')
				is_var = 1;
			while (str[i] && is_quoted(str, i))
				i++;
			str[i] ? i++ : 0;
		}
		if (is_var)
		{
			while (str[i] && ft_isspace(str[i]))
				i++;
			continue ;
		}
		dprintf(2, "%.*s\n", i - j, str + j);
		if (alias_replace(str, aliases, i, j))
		{
			//ft_memset(str + j, '5', i - j);
			i = 0;
			continue ;
		}
		while (str[i] && !stresc(";|&", str, i))
			i++;
		while (str[i] && stresc(";|&", str, i))
			i++;
	}
	return (str);
}
