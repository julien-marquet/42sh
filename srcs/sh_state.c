/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh_state.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 22:56:52 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 22:20:57 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "sh_state.h"

t_sh_state	*init_sh_state(void)
{
	t_sh_state	*sh_state;

	if ((sh_state = malloc(sizeof(t_sh_state))) == NULL)
		return (NULL);
	sh_state->status = 0;
	sh_state->exit_sig = 0;
	sh_state->internal_storage = NULL;
	sh_state->aliases = NULL;
        sh_state->hash_table = NULL;
	return (sh_state);
}

void		free_sh_state(t_sh_state **state)
{
	t_list	*pointer;
	void	*previous;

	if (state == NULL || *state == NULL)
		return ;
	ft_lstdel(&((*state)->internal_storage), free_lstnode);
	pointer = (*state)->hash_table;
	while (pointer != NULL)
	{
		free(((t_hash_table *)(pointer->content))->bin);
		free(((t_hash_table *)(pointer->content))->path);
		free(pointer->content);
		previous = pointer;
		pointer = pointer->next;
		free(previous);
	}
	free(*state);

}
