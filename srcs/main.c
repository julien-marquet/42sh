/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 18:24:42 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/11 11:36:31 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "common.h"
#include "sh.h"
#include "input/input.h"
#include "input/input_data.h"
#include "win_data.h"
#include "signal_handler.h"

#include <unistd.h>
#include <fcntl.h>
#include "errno.h"

int		main(void)
{
	t_sh_state		*sh_state;
	t_input_data	*input_data;

	sh_state = init_sh();
	input_data = init_input_data();
	signal(SIGWINCH, handle_sigwinch);
	signal(SIGINT, handle_sigint);
	while (sh_state->exit_sig == 0)
	{

		if (handle_input(sh_state, input_data) == 1)
		{
			sh_state->status = 1;
			break ;
		}
		dprintf(2, "\n--------------------\nOUTPUT = %s\n--------------------\n", input_data->input_buf->buf);
		reset_dyn_buf(input_data->input_buf);
	}
	exit_sh(sh_state);
	return (0);
}

