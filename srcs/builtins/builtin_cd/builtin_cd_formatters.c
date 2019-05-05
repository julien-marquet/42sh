/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_cd_formatters.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 15:12:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 15:14:35 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_cd/builtin_cd.h"

char	*format_path(t_sh_state *sh_state, char *curpath, size_t res_links)
{
	char	*final;
	char	*canon;

	if ((canon = ft_strdup(curpath)) == NULL)
		return (NULL);
	if (make_path_absolute(sh_state, &canon) != 0)
	{
		ft_strdel(&canon);
		return (NULL);
	}
	final = !res_links ? canon : NULL;
	if (res_links)
	{
		if ((final = resolve_links(sh_state,
	ft_strdup("/"), &canon)) == NULL)
		{
			ft_strdel(&canon);
			return (NULL);
		}
		ft_strdel(&canon);
	}
	if (make_path_canonical(&final) != 0)
		return (NULL);
	return (final);
}

int		make_path_canonical(char **path)
{
	int		i;

	i = -1;
	while ((*path)[++i] != '\0')
	{
		if ((*path)[i] == '/')
		{
			if (remove_dot(path, &i))
				continue ;
			else if (remove_dot_dot(path, &i))
				continue ;
			else if (remove_slashes(path, &i))
				continue ;
		}
	}
	return (0);
}

int		make_path_absolute(t_sh_state *sh_state, char **path)
{
	char	*pwd;
	char	*tmp;

	if (!path || !*path)
		return (1);
	if ((*path)[0] == '/')
		return (0);
	if ((pwd = get_env_value(sh_state->internal_storage,
"PWD")) == NULL)
		return (1);
	tmp = *path;
	if (pwd[ft_strlen(pwd) - 1] == '/')
		*path = ft_strjoin(pwd, tmp);
	else
		*path = ft_construct_str(3, pwd, "/", tmp);
	ft_strdel(&tmp);
	return (path == NULL);
}
