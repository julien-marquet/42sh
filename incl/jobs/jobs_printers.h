/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_printers.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 18:27:11 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 22:24:19 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef JOBS_PRINTERS_H
# define JOBS_PRINTERS_H

# include "common.h"

void	print_job_bpid(t_pos_info p_info, int bpid);
void	add_job_status(t_pos_info p_info, int mode, char **display);

#endif
