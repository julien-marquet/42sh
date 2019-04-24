/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_cd.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 20:23:54 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/24 05:22:06 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_cd.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

int		check_dir_path(const char *path)
{
	struct stat	f_stat;

	dprintf(2, "check dir path, path = %s\n", path);
	if (path == NULL)
		return (1);
	if (access(path, F_OK) == -1)
		return (1);
	if (stat(path, &f_stat) == -1)
		return (1);
	if (S_ISDIR(f_stat.st_mode) == 0)
		return (1);
	return (0);
}

int		check_for_cons_separator(char *cdpath, int j)
{
	int		separator;

	separator = 0;
	j--;
	while (j >= 0 && cdpath[j] == ':')
	{
		separator++;
		j--;
	}
	return (separator > 1 || (separator == 1 && j == -1));
}

int		had_null_paths(char *cdpath, int i)
{
	int	j;
	int	separator;
	int entry;

	separator = 1;
	entry = -1;
	j = 0;
	while (cdpath[j] != '\0')
	{
		if (cdpath[j] != ':')
		{
			if (separator == 1)
			{
				entry++;
				separator = 0;
			}
		}
		separator |= cdpath[j] == ':';
		if (entry == i)
			return (check_for_cons_separator(cdpath, j));
		j++;
	}
	return (0);
}

char	*loop_over_cdpath(char *cdpath, char **paths, const char **av,
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

char	*retrieve_cdpath(t_sh_state *sh_state, int ac, const char **av,
int start)
{
	char	*cdpath;
	char	**paths;
	char	*curpath;

	if ((cdpath = ft_strdup(get_env_value(sh_state->internal_storage,
"CDPATH"))) == NULL)
		return (NULL);
	paths = ft_strsplit((const char *)cdpath, ':');
	if (paths == NULL)
		return (NULL);
	if ((curpath = loop_over_cdpath(cdpath, paths, av, start)) == NULL)
	{
		free_arr(paths);
		if (cdpath[ft_strlen(cdpath) - 1] == ':')
		{
			ft_strdel(&cdpath);
			curpath = ft_strjoin("./", av[start]);
			if (check_dir_path(curpath) == 0)
				return (curpath);
			ft_strdel(&curpath);
		}
	}
	ft_strdel(&cdpath);
	return (curpath);
}

char	*get_dir_operand(t_sh_state *sh_state, int ac, const char **av,
int start)
{
	if (ac <= 1)
		return (ft_strdup(get_env_value(sh_state->internal_storage, "HOME")));
	else
		return (ft_strdup(av[start]));
}

char	*get_curpath(t_sh_state *sh_state, int ac, const char **av, int i)
{
	char	*directory;
	char	*curpath;

	if ((directory = get_dir_operand(sh_state, ac, av, i)) == NULL)
		return (NULL);
	if (ft_strncmp(directory, "/", 1) == 0 ||
ft_strncmp(directory, "./", 2) == 0 || ft_strncmp(directory, "../", 3) == 0)
		return (directory);
	else if ((curpath = retrieve_cdpath(sh_state, ac, av, i)) == NULL)
		return (directory);
	ft_strdel(&directory);
	return (curpath);
}

char	*get_old_pwd(t_sh_state *sh_state, t_builtin_context *context)
{
	char	*res;

	if ((res = ft_strdup(get_env_value(sh_state->internal_storage,
"OLDPWD"))) == NULL)
		print_error(context->origin, "OLDPWD not set", 2);
	return (res);
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

int		get_prec_slash_pos(char *path, int i)
{
	if (i > 0)
		i--;
	while (i > 0)
	{
		if (path[i] == '/')
			return (i);
		i--;
	}
	return (i);
}

int		count_unnecessary_slashes(char *path, int i)
{
	int		cpt;

	cpt = 0;
	i++;
	while (path[i] == '/')
	{
		cpt++;
		i++;
	}
	return (cpt);
}

int	remove_dot(char **path, int *i)
{
	if (ft_strncmp(&(*path)[*i], "/./", 3) == 0)
	{
		ft_strcpy(&(*path)[*i], &(*path)[*i + 2]);
		*i -= 1;
		return (1);
	}
	return (0);
}

int	remove_dot_dot(char **path, int *i)
{
	int		j;

	if (ft_strncmp(&(*path)[*i], "/../", 4) == 0)
	{
		j = get_prec_slash_pos(*path, *i);
		ft_strcpy(&(*path)[j],
	&(*path)[*i + 3]);
		*i -= j + 1;
		return (1);
	}
	return (0);
}

int	remove_slashes(char **path, int *i)
{
	int		j;

	if ((j = count_unnecessary_slashes(*path, *i)) > 0)
	{
		if ((*i == 0 && j > 1) || (*i != 0))
		{
			ft_strcpy(&(*path)[*i],
		&(*path)[*i + j]);
			*i -= 1;
			return (1);
		}
	}
	return (0);
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

int		builtin_cd(t_sh_state *sh_state, int ac,
const char **av, t_builtin_context *context)
{
	char	*curpath;
	char	*opts;
	int		i;

	add_origin(&context->origin, "cd");
	if (ac == 2 && ft_strcmp(av[1], "-") == 0)
		curpath = get_old_pwd(sh_state, context);
	else
	{
		if ((i = handle_builtin_options(av, "LP", &opts, context)) == -1)
			return (1);
		else if (i == 0)
		{
			print_error(context->origin, "usage: cd [-L|-P] [dir]", 2);
			return (1);
		}
		else
			curpath = get_curpath(sh_state, ac, av, i);
	}
	if (make_path_absolute(sh_state, &curpath) != 0)
		return (1);
	if (make_path_canonical(&curpath) != 0)
		return (1);
	dprintf(2, "canonical path = %s\n", curpath);
	return (0);
}
