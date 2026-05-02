#include "../include/minishell.h"

/* Hem sayısal mı diye bakar, hem de long long taşması (overflow) var mı kontrol eder */
static int	parse_exit_code(char *str, long long *code)
{
	int					sign;
	unsigned long long	res;
	int					max_digit;

	sign = 1;
	res = 0;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!*str)
		return (0); /* Sadece + veya - girilmişse hata */
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0); /* Harf varsa hata */
			
		/* Sağ tarafı int olarak hesaplayıp int ile kıyaslıyoruz, hata gidiyor */
		max_digit = 7 + (sign == -1);
		if (res > 922337203685477580ULL
			|| (res == 922337203685477580ULL && (*str - '0') > max_digit))
			return (0); /* Sınır aşıldıysa hata */
			
		res = res * 10 + (*str - '0');
		str++;
	}
	*code = (long long)res * sign;
	return (1);
}

/* exit [kod] → shell'den çık */
int	builtin_exit(char **args, char ***env)
{
	long long	code;

	(void)env;
	ft_putendl_fd("exit", 1);
	if (!args[1])
		exit(0); /* NOT: Bunu executor'a bağlarken shell->exit_status olarak güncelleyeceğiz */
	
	if (!parse_exit_code(args[1], &code))
	{
		/* Bash orijinal hata mesajı formatı */
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255); /* Sayısal değilse veya taşıyorsa 255 ile çık */
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1); /* Çıkış yapma, sadece hata kodu dön */
	}
	
	/* Bash kuralı: 256'nın modunu alarak çık */
	exit((int)(code % 256));
}