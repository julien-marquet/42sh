#ifndef COMPLETION_H
# define COMPLETION_H

# include <dirent.h>
# include "common.h"

# define CHK_NONE		0x0
# define CHK_BUILTINS	0x1
# define CHK_VARS		0x2

char	*trim(char *str);
size_t	is_dir(char *path);
size_t	is_stopping(char str);
size_t	is_path(const char *word);
size_t	is_closed(char *str, char *base);
int		delete_completed(t_input_data *input);

int		lstfree(t_list *files);
void	lstmerge(t_list **list1, t_list *list2);

char	*handle_expand(char *word, t_sh_state *sh_state);
int		handle_completion(t_input_data *input, t_sh_state *sh_state);

size_t	get_var_name_length(char *str);
int		get_builtins(t_list **files, char *needle);
char	*get_path(t_input_data *input, size_t get_all);
t_list	*get_files(char *path, char *needle, int flags, t_list *internal_storage);
int		get_vars(t_list **files, t_list *storage, char *needle);
char	*get_current_word(t_input_data *input, t_sh_state *sh_state);

int		complete_arg(t_input_data *input, char *word, t_sh_state *state);
int		complete_bin(char *word, t_sh_state *sh_state, t_input_data *input);
int		complete_word(t_input_data *input, char *completed, size_t add_slash);

int		find_in_dir(t_list *files, t_input_data *input, char *needle);

int		free_exit(t_list *files, char *str);
#endif
