/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:51:07 by cmorales          #+#    #+#             */
/*   Updated: 2022/09/20 18:21:52 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(char *text)
{
	if (errno == 0)
		write(2, "Error\n", 6);
	else
		perror(text);
	exit(EXIT_FAILURE);
}

void	ft_cmd_not_found(char **cmd)
{
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": command not found\n", 20);
	ft_free_paths(cmd);
	exit(EXIT_FAILURE);
}

void	ft_free_paths(char **paths)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (paths[len])
		len++;
	while (i < len)
		free(paths[i++]);
	free(paths);
}

char	**ft_all_the_paths(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (0);
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

char	*ft_get_path(char *cmd, char **envp)
{
	char	**all_the_paths;
	char	*path;
	char	*slash;
	int		i;

	i = 0;
	all_the_paths = ft_all_the_paths(envp);
	while (all_the_paths[i])
	{
		slash = ft_strjoin(all_the_paths[i], "/");
		path = ft_strjoin(slash, cmd);
		free(slash);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_free_paths(all_the_paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_paths(all_the_paths);
	return (0);
}
