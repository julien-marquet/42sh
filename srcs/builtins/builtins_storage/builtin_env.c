/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_env.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 22:37:30 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 23:25:57 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtin_env.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

char	**generate_unique_env(const char **av, int start, int len)
{
	char	**env;
	int		i;
	size_t	pair_len;

	if ((env = (char **)ft_memalloc(sizeof(char *) * (len + 1))) == NULL)
		return (NULL);
	env[len] = NULL;
	i = 0;
	while (i < len)
	{
		pair_len = ft_strlen(av[start + i]);
		env[i] = ft_memalloc(pair_len + 2);
		ft_strcpy(env[i], av[start + i]);
		env[i][pair_len] = '\n';
		env[i][pair_len] = '\0';
		i++;
	}
	return (env);
}

char	*create_job_name_from_arr(const char **av)
{
	size_t	arr_len;
	size_t	strs_len;
	size_t	name_pos;
	size_t	i;
	char	*name;

	arr_len = ft_arraylen((const void **)av);
	i = 0;
	strs_len = 0;
	while (i < arr_len)
		strs_len += ft_strlen(av[i++]);
	if ((name = ft_memalloc(strs_len + i + 1)) == NULL)
		return (NULL);
	i = 0;
	name_pos = 0;
	while (name_pos < strs_len)
	{
		ft_strcpy(&name[name_pos], av[i]);
		name_pos += ft_strlen(av[i++]);
		name[name_pos] = ' ';
		name_pos++;
	}
	return (name);
}

int		execute_binary(t_sh_state *sh_state,
t_special_exec_context *sp_context, const char **av)
{
	pid_t		pid;
	t_proc_grp	*proc_grp;

	pid = fork();
	if (pid == 0)
	{
		setpgid(0, getpid());
		reset_signal_handlers();
		if (execve(sp_context->path, sp_context->av, sp_context->env) == -1)
			exit(1);
	}
	else
	{
		setpgid(pid, pid);
		if ((proc_grp = register_special_job(pid, av)) == NULL)
			return (1);
		send_special_to_fg(sh_state, proc_grp);
		return (0);
	}
	return (0);
}

int		handle_env_exec(t_sh_state *sh_state, const char **av,
int start, t_builtin_context *context)
{
	int						pairs;
	int						new_start;
	int						res;
	t_special_exec_context	sp_context;

	res = 0;
	new_start = start;
	if ((pairs = count_pairs(av, &new_start, context->origin)) == -1)
		res = 1;
	else if ((sp_context.env = generate_unique_env(av, start, pairs)) == NULL)
		res = 1;
	else
	{
		sp_context.av = (char *const *)&av[new_start];
		if ((sp_context.path = find_utility(sh_state,
	&av[new_start], context)) == NULL)
			res = &av[new_start] != NULL;
		else
		{
			res = execute_binary(sh_state, &sp_context, av);
			ft_strdel(&sp_context.path);
		}
		free_arr(sp_context.env);
	}
	return (res);
}

int		builtin_env(t_sh_state *sh_state, int ac, const char **av,
t_builtin_context *context)
{
	int		start;
	char	*opts;
	int		res;

	add_origin(&context->origin, "env");
	res = 0;
	if (ac == 1)
		print_env(sh_state->internal_storage, 1);
	else
	{
		if ((start = handle_builtin_options(av, "i", &opts, context)) == -1)
			res = 1;
		else if (start == 0)
			env_error(context->origin, &res);
		else
		{
			if (context->is_process && (res = 1))
				print_error(context->origin, "no job control", 2);
			else
				res = handle_env_exec(sh_state, av, start, context);
		}
		ft_strdel(&opts);
	}
	return (res);
}
