#ifndef COMPLETION_H
# define COMPLETION_H

# include <dirent.h>
# include "common.h"

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

char	*get_current_word(t_input_data *input, t_sh_state *sh_state);
int		complete_arg(t_input_data *input, char *word, t_sh_state *state);
int		complete_bin(char *word, t_sh_state *sh_state, t_input_data *input);
#endif
