/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/05 19:38:47 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/21 03:15:29 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/parse.h"

static int	parse_error(char *str, int i)
{
	ft_putstr_fd(NAME, 2);
	ft_putstr_fd(": syntax error near unexpected token `", 2);
	ft_putchar_fd(str[i], 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

static int	check_start(char *str, int start)
{
	int i;

	i = 0;
	while (str[i] && i < start)
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_end(char *str, char c, int len, int start)
{
	int special;

	special = 0;
	if (check_start(str, start))
		return (1);
	str += start;
	if ((c == '&' && len == 1) || c == ';')
		special = 1;
	while (str[len] && !ft_strchr(";|&", str[len]))
	{
		if (!ft_isspace(str[len]))
			return (0);
		len++;
	}
	if (special && str[len] == 0)
		return (0);
	return (1);
}

/*
** Possible Parse error
** more than 1 consecutive `;`
** more than 2 consecutive `| < > &`
** `< > >& <&` followed by `newline |`
** `; | || &&` followed by whitespaces only
** starting or ending with `| || &&`
*/

static int	parse_error_handler(char *str, char *c, int i, int len)
{
	if (len > 2)
		return (1);
	else if (*c == ';' && len > 1)
		return (1);
	else if (*c == '<' || *c == '>')
	{
		i += len;
		if (str[i] == '&')
		{
			if (len == 2)
				return (1);
			i++;
		}
		while (ft_isspace(str[i]))
			i++;
		if (ft_strchr(";|<>", str[i]))
			return (1);
	}
	if (*c == '|' || *c == '&' || *c == ';')
		return (check_end(str, *c, len, i));
	return (0);
}

int			parse_check(char *str)
{
	int		i;
	int		len;
	char	*c;

	i = 0;
	while (str[i])
	{
		while (str[i] && is_quoted(str, i))
			i++;
		if ((c = stresc(";|<>&", str, i)) && *c)
		{
			len = 0;
			while (str[i + len] == *c)
				len++;
			if (parse_error_handler(str, c, i, len))
				return (parse_error(str, i));
			i += len;
			continue ;
		}
		str[i] ? i++ : 0;
	}
	return (0);
}
