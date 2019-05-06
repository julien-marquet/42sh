/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh_state.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 22:56:52 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 19:42:59 by mmoya       ###    #+. /#+    ###.fr     */
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

void		free_sh_state(t_sh_state **state)
{
	if (state == NULL || *state == NULL)
		return ;
	remove_all_aliases(&(*state)->aliases);
	ft_lstdel(&((*state)->internal_storage), free_lstinternal_storage_node);
	delete_table(&((*state)->hash_table));
	free(*state);
}
