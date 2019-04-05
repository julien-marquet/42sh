/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 18:24:42 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 15:27:53 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "common.h"
#include "sh.h"
#include "editing/input/input.h"
#include "data/input_data.h"
#include "signal_handler.h"
#include "parse.h"

#include <unistd.h>
#include <fcntl.h>
#include "errno.h"

int		main(void)
{
	t_sh_state		*sh_state;
	t_input_data	*input_data;

	char *HEREDOC_PLACEHOLDER = NULL;

	if ((sh_state = init_sh()) == NULL)
		return (1);
	if ((input_data = init_input_data()) == NULL)
		return (1);
	signal(SIGWINCH, handle_sigwinch);
	while (sh_state->exit_sig == 0)
	{
		if (handle_input(sh_state, input_data, HEREDOC_PLACEHOLDER) == 1)
		{
			sh_state->status = 1;
			break ;
		}
		parse(input_data->active_buf->buf, NULL);
		reset_dyn_buf(input_data->active_buf);
	}
	exit_sh(sh_state, input_data);
	return (0);
}

