/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_special_params.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/21 02:38:55 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/21 03:49:57 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "storage/storage_special_params.h"

char	*get_special_parameter(t_sh_state *sh_state, char *search)
{
	if (search == NULL)
		return (NULL);
	if (ft_strcmp(search, "?") == 0)
		return (ft_itoa((int)sh_state->status));
	else if (ft_strcmp(search, "$") == 0)
		return (ft_itoa(sh_state->shell_pid));
	else if (ft_strcmp(search, "-") == 0)
		return (ft_strdup("ih"));
	else if (ft_strcmp(search, "!") == 0)
		return (ft_itoa(jobs_super_get(NULL)->last_bpid));
	else if (ft_strcmp(search, "0") == 0)
		return (NAME);
	else
		return (NULL);
}
