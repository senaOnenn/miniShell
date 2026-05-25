#include "../include/minishell.h"

char	*ft_strjoin_safe(char const *s1, char const *s2)
{
	char	*result;
	int		s1len;
	int		s2len;
 
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	result = malloc(s1len + s2len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, s1len);
	ft_memcpy(result + s1len, s2, s2len);
	result[s1len + s2len] = '\0';
	return (result);
}
