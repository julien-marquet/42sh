/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_cmd_checkers.h                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/18 01:05:36 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 01:08:35 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXEC_CMD_CHECKERS_H
# define EXEC_CMD_CHECKERS_H

# include "common.h"
# include "parse/parse.h"

int		cmd_is_empty(t_cmd *cmd);
int		is_end_flag(t_cmd *cmd);
int		is_pipe_flag(t_cmd *cmd);
int		is_conditionned_flag(t_cmd *cmd);
int		is_background(t_cmd *cmd_list);

#endif
