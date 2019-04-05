/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   win_data.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 22:05:27 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 18:12:07 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef WIN_DATA_H
# define WIN_DATA_H

# include "common.h"

int				init_win_data(void);
void			update_win_data();
int				get_win_col(void);
int				get_win_row(void);
void			reset_win_resized_value();
int				win_has_been_resized();

t_win_data		g_win_data;

#endif
