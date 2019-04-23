/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/23 17:46:26 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/22 01:53:08 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "common.h"
# include "sh.h"
# include "parse/utils.h"
# include "exec/exec.h"
# include "exec/exec_cmd_checkers.h"

# define CHEV_FILE -1
# define CHEV_CLOSE -2
# define CHEV_PERM 420

/*
** CHECK
*/

int					parse_check(char *str);

/*
** PARSE
*/

char				*parse_alias(char *str, t_list *aliases, t_list *skip);
int					parse_exec(char *str, t_sh_state *sh_state, t_input_data *input_data);
t_cmd				*parse_cmdcreate(char *str, int len, t_cmd *cmd, int type);
void				parse_chev(t_cmd *cmd, t_sh_state *sh_state, t_input_data *input_data);
void				parse_chevcreate(char *file, t_cmd *cmd, int *type, void *sh_info[2]);
int					parse_tokenize(char *str, t_cmd **cmd);
int					parse_expansion(t_cmd *cmd, t_sh_state *sh_state);
char				*get_expand_str(char *str, t_sh_state *sh_state);
char				**parse_strsplit(char *str, int len);

t_cmd				*parse_nextfree(t_cmd *cmd);
void				free_executed_cmds(t_cmd *acmd, t_cmd *remaining, t_cmd *cmd);

/*
** EXEC
*/

int					exec_chevout(t_file *out);
int					exec_chevin(t_file *in);

#endif
