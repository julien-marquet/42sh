/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   chev.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/18 20:14:58 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 15:11:06 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse.h"

static void		parse_chevpush(t_file **file, t_file *new)
{
	t_file *tmp;

	tmp = *file;
	if (file != NULL && new != NULL)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/*
** Free new->file in heredoc function
*/

static t_cmd	*parse_chevcreate(char *file, t_cmd *cmd, int *type, char chev)
{
	t_file	*new;

	new = ft_memalloc(sizeof(t_file));
	if (chev == '<' && type[C_LEN] == 2)
	{
		new->here = ft_strdup("HEREDOC\nPLACE\nHOLDER");
		ft_strdel(&file);
	}
	else
		new->file = file;
	new->type = type;
	if (chev == '<')
		!cmd->in ? cmd->in = new : parse_chevpush(&cmd->in, new);
	else if (chev == '>')
		!cmd->out ? cmd->out = new : parse_chevpush(&cmd->out, new);
	return (cmd);
}

static int		*parse_chev_type(char *str, int i, char chev)
{
	int		*type;

	if (!(type = ft_memalloc(sizeof(int) * 3)))
		return (NULL);
	type[C_IN] = chev == '>' ? 1 : 0;
	type[C_OUT] = -1;
	while (i > 0 && ft_isdigit(str[i - 1]))
		i--;
	if ((i > 0 && stresc(";|<>& ", str, i - 1)) || i == 0)
		ft_isdigit(str[i]) ? type[C_IN] = ft_atoi(str + i) : 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i + type[C_LEN]] && str[i + type[C_LEN]] == chev)
		type[C_LEN]++;
	i += type[C_LEN];
	if (str[i] == '&' && str[i + 1])
		type[C_OUT] = ft_atoi(str + i + 1);
	return (type);
}

static int		parse_chev_skip(char *str, int i, char chev)
{
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && str[i] == chev)
		i++;
	if (str[i] == '&')
		i++;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

static int		parse_chev_handle(char *str, int i, t_cmd *cmd, char chev)
{
	char	*file;
	int		len;
	int		tmp;
	int		*type;

	type = parse_chev_type(str, i, chev);
	len = i;
	while (i > 0 && ft_isdigit(str[i - 1]))
		i--;
	if ((i > 0 && stresc(";|<>& ", str, i - 1)) || i == 0)
		len = i;
	i = parse_chev_skip(str, i, chev);
	tmp = i;
	while (str[i] && (!stresc(";|<>& ", str, i) || is_quoted(str, i)))
		i++;
	if (!(file = strndup_qr(str + tmp, i - tmp)))
		return (0);
	parse_chevcreate(file, cmd, type, chev);
	ft_memset(str + len, ' ', i - len);
	return (i);
}

void			parse_chev(t_cmd *cmd)
{
	char	*str;
	char	*chev;
	int		i;

	str = cmd->str;
	chev = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] && is_quoted(str, i))
			i++;
		if (str[i] && (chev = stresc("<>", str, i)))
			i = parse_chev_handle(str, i, cmd, *chev);
		else
			str[i] ? i++ : 0;
	}
}
