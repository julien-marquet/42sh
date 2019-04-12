/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/23 17:46:26 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 00:13:02 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "common.h"
# include "sh.h"

# define SH_NAME "42sh"

# define CHEV_PERM 420
# define READ_END 0
# define WRITE_END 1


typedef struct		s_file {
	char			*file;
	char			*here;
	int				*type;
	struct s_file	*next;
}					t_file;

typedef struct		s_arg {
	char			*arg;
	int				type;
	struct s_arg	*next;
}					t_arg;

/*
** char		**arg = Command arguments
** char		*red = Redirection type
** t_file	*in = Inputs
** t_file	*out = Outputs
*/

typedef struct		s_cmd {
	char			*str;
	char			**arg;
	char			type;
	char			*red;
	t_file			*in;
	t_file			*out;
	struct s_cmd	*next;
}					t_cmd;

/*
** REDIRECTION CHEVRON TYPE
*/

typedef enum		e_ctype {
	C_IN = 0,
	C_LEN,
	C_OUT,
	C_TYPE
}					t_ctype;

/*
** CHECK
*/

int				parse_error(char *str, int i);
int				parse_check(char *str);

/*
** PARSE
*/

char			*parse_alias(char *str, t_list *aliases, t_list *skip);
int				parse(char *str, t_sh_state *sh_state, t_input_data *input_data);
void			parse_chev(t_cmd *cmd, t_sh_state *sh_state, t_input_data *input_data);
t_cmd			*parse_chevcreate(char *file, t_cmd *cmd, int *type, t_sh_state *sh_state, t_input_data *input_data);
int				parse_tokenize(char *str, t_cmd **cmd);
void			parse_expansion(t_cmd *cmd, t_sh_state *sh_state);
char			**parse_strsplit(char *str, int len);

/*
** UTILS
*/

char			*stresc(const char *find, char *str, int i);
char			*strndup_qr(char *str, size_t len);
char			*strinsert(char *dst, char *new, size_t i, size_t end);
int				is_quoted(char *str, int i);

t_cmd			*parse_nextfree(t_cmd *cmd);

/*
** EXEC
*/

int				exec_chevout(t_cmd *cmd);
int				exec_chevin(t_cmd *cmd);

#endif
