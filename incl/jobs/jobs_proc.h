/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_proc.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 17:31:09 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 22:40:08 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef JOBS_PROC_H
# define JOBS_PROC_H

# include "common.h"

t_proc	*find_by_pid(t_proc_grp *proc_grp, int pid);
t_proc	*new_proc(int pid, int status, char *name);
int		add_proc(t_proc *proc, t_proc_grp *proc_grp);
#endif
