/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_special_params.h                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/21 02:40:02 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 23:55:30 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STORAGE_SPECIAL_PARAMS_H
# define STORAGE_SPECIAL_PARAMS_H

# include "common.h"
# include "jobs/jobs.h"

char	*get_special_parameter(t_sh_state *sh_state, char *search);

#endif
