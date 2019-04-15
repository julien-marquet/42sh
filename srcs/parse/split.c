/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   split.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 17:56:56 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 15:30:10 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/parse.h"

static void		parse_argpush(t_arg **arg, t_arg *new)
{
	t_arg *tmp;

	tmp = *arg;
	if (arg != NULL && new != NULL)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static t_arg	*parse_argcreate(char *str, int len, t_arg *arg)
{
	t_arg	*new;

	if (!(new = malloc(sizeof(t_arg))))
		return (NULL);
	if (!(new->arg = strndup_qr(str, len)))
		return (NULL);
	new->type = 0;
	new->next = NULL;
	if (!arg)
		return (new);
	parse_argpush(&arg, new);
	return (arg);
}

static t_arg	*parse_split_create(char *str, int len)
{
	t_arg	*arg;
	int		start;
	int		i;

	i = 0;
	arg = NULL;
	while (i < len)
	{
		while (i < len && ft_isspace(str[i]))
			i++;
		start = i;
		while (i < len && (!stresc(" \t\n\f\v\r", str, i) || is_quoted(str, i)))
			i++;
		if (i - start)
			arg = parse_argcreate(str + start, i - start, arg);
	}
	return (arg);
}

static int		parse_split_count(t_arg *split)
{
	int	len;

	len = 0;
	while (split)
	{
		len++;
		split = split->next;
	}
	return (len);
}

char			**parse_strsplit(char *str, int len)
{
	t_arg	*split;
	t_arg	*tmp;
	char	**arg;
	int		i;

	if (!(split = parse_split_create(str, len)))
		return (NULL);
	i = parse_split_count(split);
	if (!(arg = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	arg[i] = NULL;
	i = 0;
	while (split)
	{
		arg[i++] = split->arg;
		tmp = split;
		split = split->next;
		free(tmp);
	}
	return (arg);
}
