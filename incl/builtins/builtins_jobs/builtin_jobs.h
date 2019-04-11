/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_jobs.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/11 20:45:10 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 20:48:36 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_JOBS_H
# define BUILTIN_JOBS_H

# include "common.h"
# include "jobs/jobs.h"

int			builtin_jobs(t_sh_state *sh_state, int ac,
			const char **av, t_builtin_context *context);

#endif
