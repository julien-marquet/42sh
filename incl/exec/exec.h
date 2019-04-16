/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 23:13:44 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 18:12:21 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "common.h"
# include "exec/exec_by_flag.h"
# include "parse/parse.h"

int		exec_cmd_list(t_sh_state *sh_state, t_cmd *cmd_list,
		const char *job_name);

#endif
