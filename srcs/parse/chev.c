/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   chev.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/18 20:14:58 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 22:21:42 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse.h"
#include "editing/input/input_main_process.h"

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

static t_cmd	*parse_chevcreate(char *file, t_cmd *cmd, int *type)
{
	t_file	*new;

	if (!(new = ft_memalloc(sizeof(t_file))))
		return (NULL);
	if (type[C_TYPE] == '<' && type[C_LEN] == 2)
	{
		new->here = ft_strdup("HEREDOC\nPLACE\nHOLDER");
		ft_strdel(&file);
	}
	else
		new->file = file;
	new->type = type;
	if (type[C_TYPE] == '<')
		!cmd->in ? cmd->in = new : parse_chevpush(&cmd->in, new);
	else if (type[C_TYPE] == '>')
		!cmd->out ? cmd->out = new : parse_chevpush(&cmd->out, new);
	return (cmd);
}

static int		*parse_chev_type(char *str, int i)
{
	int		*type;

	if (!(type = ft_memalloc(sizeof(int) * sizeof(t_ctype))))
		return (NULL);
	type[C_TYPE] = str[i];
	type[C_IN] = type[C_TYPE] == '>' ? 1 : 0;
	type[C_OUT] = -1;
	while (i > 0 && ft_isdigit(str[i - 1]))
		i--;
	if ((i > 0 && stresc(";|<>& ", str, i - 1)) || i == 0)
		ft_isdigit(str[i]) ? type[C_IN] = ft_atoi(str + i) : 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i + type[C_LEN]] && str[i + type[C_LEN]] == type[C_TYPE])
		type[C_LEN]++;
	i += type[C_LEN];
	if (str[i] == '&' && str[i + 1])
		type[C_OUT] = ft_atoi(str + i + 1);
	return (type);
}

static int		parse_chev_skip(char *str, int i, char c_type)
{
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && str[i] == c_type)
		i++;
	if (str[i] == '&')
		i++;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

static int		parse_chev_handle(char *str, int i, t_cmd *cmd)
{
	char	*file;
	int		len;
	int		tmp;
	int		*type;

	if (!(type = parse_chev_type(str, i)))
		return (i);
	len = i;
	while (i > 0 && ft_isdigit(str[i - 1]))
		i--;
	if ((i > 0 && stresc(";|<>& ", str, i - 1)) || i == 0)
		len = i;
	i = parse_chev_skip(str, i, type[C_TYPE]);
	tmp = i;
	while (str[i] && (!stresc(";|<>& ", str, i) || is_quoted(str, i)))
		i++;
	if (!(file = strndup_qr(str + tmp, i - tmp)))
		return (0);
	parse_chevcreate(file, cmd, type);
	ft_memset(str + len, ' ', i - len);
	return (i);
}

void			parse_chev(t_cmd *cmd)
{
	char	*str;
	int		i;

	str = cmd->str;
	i = 0;
	while (str[i])
	{
		while (str[i] && is_quoted(str, i))
			i++;
		if (str[i] && stresc("<>", str, i))
			i = parse_chev_handle(str, i, cmd);
		else
			str[i] ? i++ : 0;
	}
}
