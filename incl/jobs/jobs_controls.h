/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_controls.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 21:56:05 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 03:29:19 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef JOBS_CONTROLS_H
# define JOBS_CONTROLS_H

# include "common.h"
# include "jobs/jobs_procs/jobs_procs.h"
# include "jobs/jobs_super.h"
# include "term_state.h"
# include "jobs/jobs_update.h"

int			send_to_fg(t_sh_state *sh_state, t_proc_grp *proc_grp);

#endif
