/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_dispatcher.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 19:00:26 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 16:05:01 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_dispatcher.h"

static t_builtin_func	get_builtins_func(const char *name)
{
	size_t					i;
	const char				**assoc_name;
	const t_builtin_func	*assoc_func;

	i = 0;
	assoc_name = get_builtins_names();
	assoc_func = get_builtins_funcs();
	if (name != NULL)
	{
		while (assoc_name[i] != NULL)
		{
			if (ft_strcmp(assoc_name[i], name) == 0)
				return (assoc_func[i]);
			i++;
		}
	}
	return (NULL);
}

t_builtin_context	*init_builtin_context(void)
{
	t_builtin_context *builtin_context;

	if ((builtin_context = ft_memalloc(sizeof(t_builtin_context))) == NULL)
		return (NULL);
	if (add_origin(&builtin_context->origin, NAME) == 1)
		return (NULL);
	return (builtin_context);
}

int			is_valid_as_function(t_cmd *cmd, t_context *context)
{
	if (cmd->red == NULL || ft_strcmp("&&", cmd->red) == 0 ||
ft_strcmp("||", cmd->red) == 0)
	{
		if (context->proc_grp->last_red == NULL ||
	ft_strcmp(context->proc_grp->last_red, "|") != 0)
			return (context->background == 0);
	}
	else if (ft_strcmp(cmd->red, "|") != 0)
	{
		if (context->proc_grp->last_red == NULL)
			return (context->background == 0);
	}
	return (0);
}

int			builtins_dispatcher(t_sh_state *sh_state, t_cmd *cmd,
t_context *context)
{
	t_builtin_func	f;
	int				res;

	res = 0;
	if ((f = get_builtins_func(cmd->arg[0])) != NULL)
	{
		if ((context->builtin_context = init_builtin_context()) == NULL)
			return (-1);
		if (is_valid_as_function(cmd, context))
		{
			sh_state->status = exec_builtin_as_function(sh_state,
		cmd, f, context);
			res = 1;
		}
		else
		{
			if (exec_builtin_as_process(sh_state, cmd,
		f, context) == 1)
				res = -1;
			else
				res = 2;
		}
		free_builtin_context(&context->builtin_context);
	}
	return (res);
}

// put a last flag in jobs procs to avoid DONE when grp not fully launched
