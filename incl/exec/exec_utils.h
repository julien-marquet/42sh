/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_utils.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/20 23:17:29 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/20 23:22:00 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

# include "common.h"
# include "jobs/jobs.h"

int		register_process(t_context *context, t_proc *proc);
void	reset_signal_handlers(void);

#endif
