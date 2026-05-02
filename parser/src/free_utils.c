#include "../include/minishell.h"

/* Çift yıldızlı (NULL sonlandırmalı) string dizisini temizler */
void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/* s1'i free eder, s1+s2'yi birleştirip döndürür.
   s2 dokunulmaz — caller kendi free eder.
   İkisi de NULL ise NULL döner. */
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;
 
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
	{
		result = ft_strdup(s1);
		free(s1);
		return (result);
	}
	result = ft_strjoin(s1, s2); /* libft'den — yeni malloc */
	free(s1);                    /* s1'i temizle, s2'ye dokunma */
	return (result);
}

/* Token listesini tamamen serbest bırakır */
void	free_tokens(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->value);
		free(list);
		list = tmp;
	}
}

/* t_cmd dizisinin tamamını serbest bırakır */
void	free_cmds(t_cmd *cmds, int count)
{
	int	i;
 
	if (!cmds)
		return ;
	i = 0;
	while (i < count)
	{
		if (cmds[i].args != NULL)	
			free_array(cmds[i].args); /* NULL sonlandırılmış string dizisi */
		if(cmds[i].redir_lst != NULL)
			free_redirs(cmds[i].redir_lst);
		i++;
	}
	free(cmds);
}

/* t_redir listesini serbest bırakır */
void	free_redirs(t_redir *list)
{
	t_redir	*tmp;
 
	while (list)
	{
		tmp = list->next;
		free(list->file); /* new_redir'e ft_strdup ile geldi, free edilmeli */
		free(list);
		list = tmp;
	}
}