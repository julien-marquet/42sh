/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh_state.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 22:56:52 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/20 22:24:18 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "sh_state.h"
#include "builtins/builtin_hash/builtin_hash.h"

t_sh_state	*init_sh_state(void)
{
	t_sh_state	*sh_state;

	if ((sh_state = ft_memalloc(sizeof(t_sh_state))) == NULL)
		return (NULL);
	sh_state->hash_table = NULL;
	return (sh_state);
}

t_sh_state	*duplicate_sh_state(t_sh_state *sh_state)
{
	t_sh_state	*new_state;

	if ((new_state = ft_memalloc(sizeof(t_sh_state))) == NULL)
		return (NULL);
	new_state->aliases = duplicate_aliases(sh_state->aliases);
	new_state->internal_storage = duplicate_storage(sh_state->internal_storage);
	new_state->exit_sig = sh_state->exit_sig;
	new_state->status = sh_state->status;
	new_state->shell_pid = sh_state->shell_pid;
	new_state->term_state = sh_state->term_state;
	new_state->term_state_backup = sh_state->term_state_backup;
	return (new_state);
}

void		free_sh_state(t_sh_state **state)
{
	if (state == NULL || *state == NULL)
		return ;

	remove_all_aliases(&(*state)->aliases);
	ft_lstdel(&((*state)->internal_storage), free_lstinternal_storage_node);
	delete_table(&((*state)->hash_table));
	free(*state);
}
