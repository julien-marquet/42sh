/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expand_tilde.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 18:38:33 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 17:14:51 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/expand.h"

static char	*expand_getdir(t_cmd *cmd, t_sh_state *sh_state, size_t i, int *nfr)
{
	char	*new;

	new = NULL;
	(*nfr)++;
	if (cmd->str[i + 1] == '+')
		new = get_stored(sh_state->internal_storage, "PWD");
	else if (cmd->str[i + 1] == '-')
		new = get_stored(sh_state->internal_storage, "OLDPWD");
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

static char	*expand_gethome(t_sh_state *sh_state, int *nfr)
{
	struct passwd	*user;
	char			*new;

	user = NULL;
	(*nfr)++;
	new = get_stored(sh_state->internal_storage, "HOME");
	if (!new)
	{
		nfr--;
		if (!(user = getpwuid(getuid())))
			return (NULL);
		new = user->pw_dir;
	}
	return (new);
}

static int	expand_tilde(t_cmd *cmd, t_sh_state *sh_state, size_t i, size_t end)
{
	char			*new;
	char			*tmp;
	int				nfr;
	int				len;

	nfr = 0;
	if (end - i - 1 == 0)
		new = expand_gethome(sh_state, &nfr);
	else if (end - i - 1 == 1)
		new = expand_getdir(cmd, sh_state, i, &nfr);
	else
		new = expand_getuhome(cmd->str + i + 1, end - i - 1);
	if (new)
	{
		len = ft_strlen(new);
		if (!(tmp = strinsert(cmd->str, new, i, end)))
		{
			nfr ? ft_strdel(&new) : 0;
			return (0);
		}
		nfr ? ft_strdel(&new) : 0;
		cmd->str = tmp;
		return (len);
	}
	return (0);
}

void		parse_tilde(t_cmd *cmd, t_sh_state *sh_state)
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
			i += expand_tilde(cmd, sh_state, i, end);
		}
		cmd->str[i] ? i++ : 0;
	}
}
