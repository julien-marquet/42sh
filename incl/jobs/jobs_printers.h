/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jobs_printers.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 18:27:11 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 18:29:31 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef JOBS_PRINTERS_H
# define JOBS_PRINTERS_H

# include "common.h"

int		print_job_status(int pos, const char *name,
		t_job_status status, int code);

#endif
