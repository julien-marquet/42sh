/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_super.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 21:58:54 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/21 03:40:19 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_super.h"

t_jobs	*jobs_super_get(t_sh_state *sh_state)
{
	static t_jobs jobs = { NULL, 0, 0, NULL };

	if (sh_state != NULL)
		jobs.sh_state = sh_state;
	return (&jobs);
}
