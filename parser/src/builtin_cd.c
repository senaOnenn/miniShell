#include "../include/minishell.h"

/* OLDPWD ve PWD'yi env'de günceller */
static int	update_pwd(char ***env)
{
	char	cwd[4096];
	char	*oldpwd;

	oldpwd = get_env_value("PWD", *env);
	if (oldpwd)
		*env = env_update(*env, "OLDPWD", oldpwd);
	if (!getcwd(cwd, sizeof(cwd)))
		return (1);
	*env = env_update(*env, "PWD", cwd);
	return (0);
}

/* Yolu belirleyen ve özel durumları (HOME, -) yöneten işçi */
static char	*get_cd_path(char **args, char **env)
{
	char	*path;

	if (!args[1])
	{
		path = get_env_value("HOME", env);
		if (!path)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (path);
	}
	/* strncmp sınırını 2 yaptık, sadece "-" yazıldığından emin olmak için */
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_value("OLDPWD", env);
		if (!path)
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		else
			ft_putendl_fd(path, 1); /* cd - durumunda yeni dizini ekrana basar */
		return (path);
	}
	return (args[1]);
}

/* cd [path] ana fonksiyonu */
int	builtin_cd(char **args, char ***env)
{
	char	*path;

	/* 42 Tuzağı: Birden fazla argüman kontrolü */
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	path = get_cd_path(args, *env);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (update_pwd(env));
}