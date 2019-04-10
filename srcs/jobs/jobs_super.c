/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_super.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 21:58:54 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 22:33:14 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/jobs_super.h"

t_jobs	*jobs_super_get(void)
{
	static t_jobs jobs = { NULL };

	return (&jobs);
}