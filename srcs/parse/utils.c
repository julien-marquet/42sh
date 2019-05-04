/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 19:40:53 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 18:50:35 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/parse.h"

char	*strndup_qr(char *str, size_t len)
{
	int		i;
	int		state;

	i = 0;
	state = QUOTE_NONE;
	str = ft_strndup(str, len);
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (state == QUOTE_DOUBLE && str[i + 1] &&
		(str[i + 1] == '$' || str[i + 1] == '`' ||
		str[i + 1] == '\"' || str[i + 1] == '\\'))
				ft_memcpy(str + i, str + i + 1, ft_strlen(str + i + 1) + 1);
			else if (state == QUOTE_NONE)
				ft_memcpy(str + i, str + i + 1, ft_strlen(str + i + 1) + 1);
		}
		else if (str[i] == '\"' && state != QUOTE_SIMPLE)
		{
			state = state == QUOTE_NONE ? QUOTE_DOUBLE : QUOTE_NONE;
			ft_memcpy(str + i, str + i + 1, ft_strlen(str + i + 1) + 1);
			continue ;
		}
		else if (str[i] == '\'' && state != QUOTE_DOUBLE)
		{
			state = state == QUOTE_NONE ? QUOTE_SIMPLE : QUOTE_NONE;
			ft_memcpy(str + i, str + i + 1, ft_strlen(str + i + 1) + 1);
			continue ;
		}
		i++;
	}
	return (str);
}

char	*strinsert(char *dst, char *new, size_t i, size_t end)
{
	char	*out;
	size_t	len;

	len = ft_strlen(dst) - (end - i) + ft_strlen(new);
	if (!(out = ft_strnew(len)))
		return (NULL);
	len = i + ft_strlen(new);
	ft_memcpy(out, dst, i);
	ft_memcpy(out + i, new, ft_strlen(new));
	ft_memcpy(out + len, dst + end, ft_strlen(dst + end));
	ft_strdel(&dst);
	return (out);
}

/*
**	ft_strchr with backslash escape
*/

char	*stresc(const char *find, char *str, int i)
{
	char	*out;
	int		k;

	out = ft_strchr(find, str[i]);
	if (out && i > 0)
	{
		if (*out == '&' && (str[i - 1] == '>' || str[i - 1] == '<'))
			return (NULL);
		k = --i;
		while (i >= 0 && str[i] == '\\')
			i--;
		if ((k - i) % 2)
			return (NULL);
	}
	return (out);
}

int		is_quoted(char *str, int i)
{
	int	j;
	int	q;
	int	dq;

	j = 0;
	q = 0;
	dq = 0;
	while (str[j] && j <= i)
	{
		if (stresc("\"", str, j) && !q)
			dq = dq == 2 ? 0 : 2;
		if ((stresc("'", str, j) || (q == 1 && str[j] == '\'')) && !dq)
			q = q == 1 ? 0 : 1;
		j++;
	}
	return (dq ? dq : q);
}
