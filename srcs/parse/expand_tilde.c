/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expand_tilde.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 18:38:33 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 15:08:28 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse.h"

static char	*expand_getdir(t_cmd *cmd, t_term *term, size_t i)
{
	char	*new;

	(void)term;
	new = NULL;
	if (cmd->str[i + 1] == '+')
		new = sh_getenv("PWD", term->env);
	else if (cmd->str[i + 1] == '-')
		new = sh_getenv("OLDPWD", term->env);
	return (new);
}

static char	*expand_getuhome(char *str, size_t len)
{
	struct passwd	*user;
	char			*new;
	char			*tmp;

	user = NULL;
	tmp = ft_strndup(str, len);
	if (!(user = getpwnam(tmp)))
	{
		ft_strdel(&tmp);
		return (NULL);
	}
	new = user->pw_dir;
	ft_strdel(&tmp);
	return (new);
}

static char	*expand_gethome(t_term *term)
{
	struct passwd	*user;
	char			*new;

	(void)term;
	user = NULL;
	new = sh_getenv("HOME", term->env);
	if (!new)
	{
		if (!(user = getpwuid(getuid())))
			return (NULL);
		new = user->pw_dir;
	}
	return (new);
}

static int	expand_tilde(t_cmd *cmd, t_term *term, size_t i, size_t end)
{
	struct passwd	*user;
	char			*new;
	char			*tmp;

	user = NULL;
	new = NULL;
	if (end - i - 1 == 0)
		new = expand_gethome(term);
	else if (end - i - 1 == 1)
		new = expand_getdir(cmd, term, i);
	else
		new = expand_getuhome(cmd->str + i + 1, end - i - 1);
	if (new)
	{
		if (!(tmp = strinsert(cmd->str, new, i, end)))
			return (0);
		cmd->str = tmp;
		return (ft_strlen(new));
	}
	return (0);
}

void		parse_tilde(t_cmd *cmd, t_term *term)
{
	size_t	i;
	size_t	end;

	i = 0;
	end = 0;
	while (cmd->str[i])
	{
		while (cmd->str[i] && is_quoted(cmd->str, i))
			i++;
		if (cmd->str[i] == '~' && (i == 0 || ft_isspace(cmd->str[i - 1])))
		{
			end = i;
			while (cmd->str[end] && !ft_isspace(cmd->str[end]) &&
			cmd->str[end] != '/')
				end++;
			i += expand_tilde(cmd, term, i, end);
		}
		cmd->str[i] ? i++ : 0;
	}
}
