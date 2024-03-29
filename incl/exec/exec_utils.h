/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_utils.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/20 23:17:29 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 23:04:21 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

# include "common.h"
# include "jobs/jobs.h"

int		register_process(t_context *context, t_proc *proc, int new_pipe[3]);
void	reset_signal_handlers(void);
int		is_absolute_path(const char *path);
int		move_to_next_valid_condition(const char *condition, t_cmd **cmd);
void	handle_bpid(int exec_res, t_context *context);

#endif
