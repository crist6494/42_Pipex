/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:51:07 by cmorales          #+#    #+#             */
/*   Updated: 2022/09/14 18:54:27 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_check_fd(int fd)
{
	if (fd == -1)
		perror("Pipex:");
}

void	ft_free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
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
		return(0);
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}


char	*ft_get_the_path(char *cmd, char **envp)
{
	char	**all_the_paths;
	char	*path;
	char	*slash;
	int		i;
	
	i = 0;
	all_the_paths = ft_all_the_paths(envp);
	while (all_the_paths[i])
	{
		slash = ft_strjoin(all_the_paths[i], '/');
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