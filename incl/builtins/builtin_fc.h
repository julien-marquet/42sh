/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fc.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 00:12:30 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/24 19:47:30 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_FC_H
# define BUILTIN_FC_H

# include "common.h"
# include "builtins/builtins_utils.h"
# include "editing/history/history.h"
# include "error_handler.h"

typedef	struct	s_fc_infos
{
	char		*opts;
	char		*editor;
	int			first;
	int			last;
}				t_fc_infos;


int		builtin_fc(t_sh_state *sh_state, int ac, const char **av,
		t_builtin_context *context);

#endif
