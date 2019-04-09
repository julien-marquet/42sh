/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expand.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 16:16:11 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 16:25:38 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "parse/parse.h"
# include "storage/storage_getters.h"

void	parse_tilde(t_cmd *cmd, t_sh_state *sh_state);
void	parse_param(t_cmd *cmd, t_sh_state *sh_state);

#endif