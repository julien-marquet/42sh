/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_cd_getters.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 15:13:35 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 23:56:55 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_cd/builtin_cd.h"

char		*get_dir_operand(t_sh_state *sh_state, int ac, const char **av,
int start)
{
	int		i;
	char	**pointer;

	i = 0;
	pointer = (char **)(av + 1);
	while (*pointer)
	{
		if (**pointer != '-')
			break ;
		i += 1;
		pointer += 1;
	}
	if (ac <= 1 || ac - 1 == i)
		return (ft_strdup(get_env_value(sh_state->internal_storage, "HOME")));
	else
		return (ft_strdup(av[start]));
}

char		*get_curpath(t_sh_state *sh_state, int ac, const char **av, int *i)
{
	char	*directory;
	char	*curpath;

	if ((directory = get_dir_operand(sh_state, ac, av, *i)) == NULL)
		return (NULL);
	if (ft_strncmp(directory, "/", 1) == 0 ||
ft_strncmp(directory, "./", 2) == 0 || ft_strncmp(directory, "../", 3) == 0 ||
ft_strcmp(directory, ".") == 0 || ft_strcmp(directory, "..") == 0)
		return (directory);
	else if ((curpath = retrieve_cdpath(sh_state, av, *i)) == NULL)
		return (directory);
	else
		*i = -2;
	ft_strdel(&directory);
	return (curpath);
}

static char	*loop_over_cdpath(char *cdpath, char **paths, const char **av,
int start)
{
	int		i;
	char	*curpath;

	i = 0;
	while (paths[i] != NULL)
	{
		if (had_null_paths(cdpath, i) == 1)
		{
			curpath = ft_strjoin("./", av[start]);
			if (check_dir_path(curpath) == 0)
				return (curpath);
			ft_strdel(&curpath);
		}
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
			curpath = ft_construct_str(3, paths[i], "/", av[start]);
		else
			curpath = ft_strjoin(paths[i], av[start]);
		if (check_dir_path(curpath) == 0)
			return (curpath);
		else
			ft_strdel(&curpath);
		i++;
	}
	return (NULL);
}

char		*norm1(char *cdpath, char **paths, const char **av, int start)
{
	char	*curpath;

	if ((curpath = loop_over_cdpath(cdpath, paths, av, start)) == NULL)
	{
		free_arr(paths);
		if (ft_strlen(cdpath) > 0 && cdpath[ft_strlen(cdpath) - 1] == ':')
		{
			ft_strdel(&cdpath);
			curpath = ft_strjoin("./", av[start]);
			if (check_dir_path(curpath) == 0)
				return (curpath);
			ft_strdel(&curpath);
		}
	}
	else
		free_arr(paths);
	ft_strdel(&cdpath);
	return (curpath);
}

char		*retrieve_cdpath(t_sh_state *sh_state, const char **av,
int start)
{
	char	*cdpath;
	char	**paths;

	if ((cdpath = ft_strdup(get_var(sh_state->internal_storage,
"CDPATH"))) == NULL)
		return (NULL);
	paths = ft_strsplit((const char *)cdpath, ':');
	if (paths == NULL)
	{
		ft_strdel(&cdpath);
		return (NULL);
	}
	return (norm1(cdpath, paths, av, start));
}
