/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   win_data_manipulations.h                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:20:42 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 18:24:55 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef WIN_DATA_MANIPULATIONS_H
# define WIN_DATA_MANIPULATIONS_H

# include "common.h"
# include "data/win_data/win_data_defines.h"

int				init_win_data(void);
void			update_win_data();
void			reset_win_resized_value();
int				win_has_been_resized();

#endif
