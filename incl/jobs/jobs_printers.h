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

char	*get_status_value(t_job_status status, int code, size_t detailed);
void	assign_display(char **display, char **str);
int		print_status(t_job_status status, int code, char **str);
int		print_pos(t_pos_info p_info, char **str);
void	print_spaces(int printed, int desired, char **str);
int		print_pid(int pid, char **str);
int		print_detailed_status(t_job_status status, int code, char **str);
void	print_name(const char *name, char **str);
void	print_job_bpid(t_pos_info p_info, int bpid);
void	add_job_status(t_pos_info p_info, int mode, char **display);

#endif
