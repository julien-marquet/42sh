/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh.h                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 23:05:43 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 03:18:24 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include "common.h"
# include "data/input_data.h"
# include "data/win_data/win_data.h"
# include "sh_state.h"
# include "term_state.h"
# include "jobs/jobs.h"

t_sh_state	*init_sh(void);
void		exit_sh(t_sh_state *sh_state, t_input_data *input_data);

#endif
