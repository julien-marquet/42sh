/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_binary.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/20 22:42:46 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 14:53:40 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec/exec_binary.h" 

static size_t	get_array_length(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i += 1;
	return (i);
}

static size_t	get_total_length(char **env, t_list *tmp)
{
	size_t				i;
	t_internal_storage	*entry;
	t_list				*pointer;
	size_t				name_len;

	i = get_array_length(env);
	pointer = tmp;
	while (pointer)
	{
		entry = pointer->content;
		name_len = ft_strlen(entry->string) - ft_strlen(ft_strchr(entry->string, '='));
		if (ft_strncmp(entry->string, *env, name_len + 1) == 0)
			break ;
		pointer = pointer->next;
		if (pointer == NULL && tmp != NULL)
			i += 1;
	}
	return (i);
}

static char	**update_env(char **env, t_list *tmp)
{
	size_t				i;
	char				**new;
	t_internal_storage	*entry;
	size_t				name_len;
	t_list				*pointer;

	if ((new = malloc((get_total_length(env, tmp) + 1) * sizeof(char *))) == NULL)
		return (NULL);
	i = 0;
	while (*env)
	{
		pointer = tmp;
		while (pointer)
		{
			entry = pointer->content;
			name_len = ft_strlen(entry->string) - ft_strlen(ft_strchr(entry->string, '='));
			if (ft_strncmp(entry->string, *env, name_len + 1) == 0)
			{
				new[i] = entry->string;
				break ;
			}
			pointer = pointer->next;
		}
		if (pointer == NULL)
			new[i] = *env;
		i += 1;
		env += 1;
	}
	new[i] = NULL;
	return (new);
}

int		exec_binary(t_cmd *cmd, char **env, const char *path, t_context *context)
{
	pid_t	pid;
	t_proc	*proc;
	const char **arg;
	int		new_pipe[3];
	int		err;
	char	*origin;
	char	**updated_env;

	origin = NULL;
	add_origin(&origin, NAME);
	new_pipe[0] = 0;
	arg = (const char **)cmd->arg;
	if (cmd->red && ft_strcmp(cmd->red, "|") == 0)
	{
		if (pipe(&new_pipe[1]) == -1)
			return (1);
		new_pipe[0] = 1;
	}
	pid = fork();
	if (pid == 0)
	{
		reset_signal_handlers();
		setpgid(0, context->proc_grp->pgid);
		use_pipes(context, new_pipe);
		if ((err = handle_redir(cmd, origin)) != 0)
			exit(err);
		else
		{
			if (cmd->env == NULL)
				updated_env = env;
			else
				if ((updated_env = update_env(env, cmd->env)) == NULL)
					exit(1);
			if (execve(path, cmd->arg, updated_env) == -1)
				exit(1);
			if (cmd->env != NULL)
				free(updated_env);
		}
	}
	else
	{
		ft_strdel(&origin);
		if ((proc = new_proc(pid, cmd->arg[0], context->last)) == NULL)
			return (1);
		if (register_process(context, proc, new_pipe) == 1)
			return (1);
	}
	return (0);
}

