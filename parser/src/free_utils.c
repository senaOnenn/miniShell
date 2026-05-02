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