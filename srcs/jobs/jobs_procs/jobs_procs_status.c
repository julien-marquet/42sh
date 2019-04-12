/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_procs_status.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 22:24:18 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 22:24:41 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_procs/jobs_procs_status.h"

t_job_status	retrieve_status(int stat_loc)
{
	if (WIFEXITED(stat_loc))
		return (exited);
	if (WIFSIGNALED(stat_loc))
		return (signaled);
	if (WIFSTOPPED(stat_loc))
		return (stopped);
	if (WIFCONTINUED(stat_loc))
		return (running);
	return (0);
}
