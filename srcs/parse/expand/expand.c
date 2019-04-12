/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expand.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 18:38:33 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 20:43:02 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/expand.h"

void		parse_expansion(t_cmd *cmd, t_sh_state *sh_state)
{
	parse_tilde(cmd, sh_state);
	parse_param(cmd, sh_state);
	parse_localvar(cmd, sh_state);
}
