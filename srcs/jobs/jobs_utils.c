/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_utils.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 22:10:19 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 22:10:20 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_flush.h"

int	has_to_be_flushed(t_proc *last_proc, t_proc *last_proc_all,
t_proc_grp *proc_grp)
{
	if (last_proc == NULL)
	{
		if (last_proc_all == NULL)
			return (0);
		return (1);
	}
	else
	{
		return (proc_grp->revived == 1 || last_proc->status == exited ||
	last_proc->status == signaled);
	}
}
