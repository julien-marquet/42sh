/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_validator.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 18:07:32 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 23:38:11 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_validator.h"

static void	search_for_quote(size_t i, int *opened, int *quote_type, t_dyn_buf *dyn_buf)
{

	if (dyn_buf->buf[i] == '\'' && ((*quote_type == QUOTE_SIMPLE && *opened == 1) || ((*quote_type == QUOTE_SIMPLE || *quote_type == QUOTE_NONE) && *opened == 0 && !is_escaped(dyn_buf->buf, i))))
	{
		if ((*opened = !(*opened)) == 0)
			*quote_type = QUOTE_NONE;
		else
			*quote_type = QUOTE_SIMPLE;
	}
	else if (dyn_buf->buf[i] == '\"' && !is_escaped(dyn_buf->buf, i))
	{
		if (*quote_type == QUOTE_NONE || *quote_type == QUOTE_DOUBLE)
		{
			if ((*opened = !(*opened)) == 0)
				*quote_type = QUOTE_NONE;
			else
				*quote_type = QUOTE_DOUBLE;
		}
	}
}

int		here_doc_is_closed(t_dyn_buf *dyn_buf, char *here_doc)
{
	size_t	len;

	if (dyn_buf->buf != NULL && here_doc != NULL)
	{
		len = ft_strlen(here_doc);
		if (ft_strncmp(dyn_buf->buf, here_doc, len) == 0)
			return (dyn_buf->len - 1 == len);
	}
	return (0);
}

static int		quotes_are_closed(t_dyn_buf *dyn_buf)
{
	int		opened;
	size_t	i;
	int		quote_type;

	i = 0;
	opened = 0;
	quote_type = QUOTE_NONE;
	while (i < dyn_buf->len)
	{
		search_for_quote(i, &opened, &quote_type, dyn_buf);
		i++;
	}
	return (opened == 0);
}

static int		operator_is_lonely(t_dyn_buf *dyn_buf)
{
	int		i;

	i = (int)dyn_buf->len - 1;
	if (i < 2)
		return (0);
	if (ft_strncmp(&(dyn_buf->buf[i - 2]), "||", 2) == 0 ||
ft_strncmp(&(dyn_buf->buf[i - 2]), "&&", 2) == 0 ||
ft_strncmp(&(dyn_buf->buf[i - 2]), "${", 2) == 0)
	{
		if (i == 2)
			return (1);
		else if (dyn_buf->buf[i - 3] == ' ')
			return (1);
	}
	return (0);
}

int		output_is_ready(t_dyn_buf *dyn_buf, int valid_here_doc)
{
	if (valid_here_doc == 0)
		return (0);
	if (valid_here_doc == 1)
		return (1);
	if (!(dyn_buf->len > 0 && dyn_buf->buf[dyn_buf->len - 1] == '\n'))
		return (0);
	if (!quotes_are_closed(dyn_buf))
		return (0);
	else if (operator_is_lonely(dyn_buf))
		return (0);
	else if (dyn_buf->buf[dyn_buf->len - 1] == '\n' &&
is_escaped(dyn_buf->buf, dyn_buf->len - 1))
		return (0);
	return (1);
}
