/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   localvar.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 20:51:02 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 21:02:14 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LOCALVAR_H
# define LOCALVAR_H

# include "parse/parse.h"
# include "storage/storage_manipulations.h"

int		parse_localvar(t_cmd *cmd, t_sh_state *sh_state);

#endif
