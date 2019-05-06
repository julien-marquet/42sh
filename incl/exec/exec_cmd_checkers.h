/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_cmd_checkers.h                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/18 01:05:36 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 23:02:40 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXEC_CMD_CHECKERS_H
# define EXEC_CMD_CHECKERS_H

# include "common.h"
# include "parse/parse.h"

int		cmd_is_empty(t_cmd *cmd);
int		is_end_flag(const char *red);
int		is_pipe_flag(const char *red);
int		is_conditionned_flag(const char *red);
int		is_background(t_cmd *cmd_list);
int		cmd_is_null(t_cmd *cmd);
int		is_last(t_cmd *cmd_list);
int		is_new_proc_grp(t_context *context);

#endif
