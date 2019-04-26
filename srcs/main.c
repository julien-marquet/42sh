/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 18:24:42 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 23:50:40 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "common.h"
#include "sh.h"
#include "editing/input/input.h"
#include "data/input_data.h"
#include "signal_handler.h"
#include "parse/parse.h"
#include "storage/storage.h"
#include "builtins/builtins.h"
#include "storage/storage.h"
#include "aliases/aliases.h"
#include "exec/exec.h"

int		main(int ac, char **av, char **env)
{
	t_sh_state		*sh_state;
	t_input_data	*input_data;

	ac = av[0][0];
	if ((sh_state = init_sh()) == NULL)
		return (1);
	if ((input_data = init_input_data()) == NULL)
		return (1);
	if ((sh_state->internal_storage = init_env((const char **)env)) == NULL)
		return (1);

	signal(SIGWINCH, handle_sigwinch);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGSTOP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, handle_sigchld);

	sh_state->shell_pid = getpgid(0);
	jobs_set_sh_state(sh_state);
	while (sh_state->exit_sig == 0)
	{

		display_jobs_alert();
		flush_exited();
		if (handle_input(sh_state, input_data, NULL) == 1)
		{
			sh_state->status = 1;
			break ;
		}
		if (parse_exec(input_data->active_buf->buf, sh_state, input_data) == -1)
		{
			sh_state->status = 1;
			break ;
		}
		reset_dyn_buf(input_data->active_buf);
	}
	exit_sh(sh_state, input_data);
	return (0);
}

// TODO couper + (copier coller integres)
// TODO ◦ La création de variable d’environnement pour une commande unique
// TODO La gestion des parametres speciaux, comme ? pour le code de sortie de la commande precedente
// TODO ctrl + r pour rechercher dans l'historique
// TODO update HASH quand $PATH est update
// TODO builtin fc
// TODO (cd -P -L)
// TODO env -i