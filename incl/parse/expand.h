/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expand.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 16:16:11 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 05:01:50 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <pwd.h>
# include "parse/parse.h"
# include "parse/localvar.h"
# include "storage/storage.h"

# define ERR_EOF1 "unexpected EOF while looking for matching `}'"

char	*expand_gethome(t_sh_state *sh_state);
int		parse_tilde(t_cmd *cmd, t_sh_state *sh_state);
int		parse_param(t_cmd *cmd, t_sh_state *sh_state);
int		param_check_isspecial(char *str);
int		expand_error_handler(int type, char *str);

#endif
