/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/05 19:38:47 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 15:03:26 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse.h"

int			parse_error(char *str, int i)
{
	ft_putstr_fd(SH_NAME, 2);
	ft_putstr_fd(": syntax error near unexpected token `", 2);
	ft_putchar_fd(str[i], 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

/*
** Possible Parse error
** more than 1 consecutive `;`
** more than 2 consecutive `| < > &`
** `< > >& <&` followed by `newline |`
*/

static int	parse_error_handler(char *str, char *c, int i, int j)
{
	if (j > 2)
		return (1);
	else if (*c == ';' && j > 1)
		return (1);
	else if (*c == '<' || *c == '>')
	{
		i += j;
		if (str[i] == '&')
			i++;
		while (ft_isspace(str[i]))
			i++;
		if (ft_strchr(";|<>", str[i]))
			return (1);
	}
	return (0);
}

int			parse_check(char *str)
{
	int		i;
	int		j;
	char	*c;

	i = 0;
	while (str[i])
	{
		while (str[i] && is_quoted(str, i))
			i++;
		if ((c = stresc(";|<>&", str, i)) && *c)
		{
			j = 0;
			while (str[i + j] == *c)
				j++;
			if (parse_error_handler(str, c, i, j))
				return (parse_error(str, i));
			i += j;
		}
		str[i] ? i++ : 0;
	}
	return (0);
}
