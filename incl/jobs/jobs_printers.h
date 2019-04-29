/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_printers.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 18:27:11 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 13:08:43 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef JOBS_PRINTERS_H
# define JOBS_PRINTERS_H

# include "common.h"

int		add_job_status(t_pos_info p_info, const char *name,
		t_proc *proc, char **job_status);
void	print_job_bpid(t_pos_info p_info, int bpid);

#endif
