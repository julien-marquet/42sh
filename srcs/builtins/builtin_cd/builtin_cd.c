/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_cd.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 20:23:54 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 15:22:21 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_cd/builtin_cd.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

int				verify_path(char *origin, char *curpath, char *formatted)
{
	int		err;

	err = 0;
	if (formatted == NULL)
		err = 1;
	else
	{
		if (ft_strlen(formatted) > PATH_MAX)
			err = 1;
		if ((err = check_dir_path(formatted)) != 0)
		{
			handle_dir_path_error(origin, curpath, err);
			err = 1;
		}
	}
	ft_strdel(&curpath);
	return (err);
}

static int		change_dir(t_sh_state *sh_state, char *formatted, int print)
{
	char	*pwd;

	if (formatted == NULL)
		return (1);
	if (chdir(formatted) != 0)
	{
		ft_strdel(&formatted);
		return (1);
	}
	if ((pwd = get_env_value(sh_state->internal_storage, "PWD")) != NULL)
		add_entry_storage(sh_state, "OLDPWD", pwd, 1);
	add_entry_storage(sh_state, "PWD", formatted, 1);
	if (print)
		ft_putendl_fd(formatted, 1);
	ft_strdel(&formatted);
	return (0);
}

int				builtin_cd(t_sh_state *sh_state, int ac,
const char **av, t_builtin_context *context)
{
	char	*curpath;
	char	*opts;
	int		i;

	add_origin(&context->origin, "cd");
	i = -2;
	if (ac == 2 && ft_strcmp(av[1], "-") == 0)
		curpath = get_old_pwd(sh_state, context);
	else
	{
		if ((i = handle_builtin_options(av, "PL", &opts, context)) == -1)
			return (1);
		else if (i == 0)
		{
			free(opts);
			print_error(context->origin, "usage: cd [-L|[-P]] [dir]", 2);
			return (1);
		}
		else
			curpath = get_curpath(sh_state, ac, av, &i);
		free(opts);
	}
	return (change_dir(sh_state, format_and_verify(sh_state,
curpath, context->origin, check_links(av, i < 0 ? 0 : i - 1)), i == -2));
}
