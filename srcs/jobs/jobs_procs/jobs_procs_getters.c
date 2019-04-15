/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_procs_getters.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:46:10 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 00:52:19 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_procs/jobs_procs_getters.h"

t_proc		*find_by_pid(t_proc_grp *proc_grp, int pid)
{
	t_list	*tmp;

	tmp = proc_grp->procs;
	while (tmp != NULL)
	{
		if (((t_proc *)tmp->content)->pid == pid)
			return ((t_proc *)tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

t_proc *get_last_proc(t_proc_grp *proc_grp)
{
	t_list	*tmp;

	tmp = proc_grp->procs;
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp == NULL || ((t_proc *)tmp->content)->last != 1)
		return (NULL);
	return ((t_proc *)tmp->content);
}