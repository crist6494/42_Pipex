/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:57:40 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/13 00:48:50 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "../includes/pipex.h"

void	child1_process(int *fd_file, int *fd, char **av, char **envp)
{
	char	**cmd;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error("Fork");
	if (pid == 0)
	{
		fd_file[0] = open(av[1], O_RDONLY);
		if (fd_file[0] < 0)
			ft_error(av[1]);
		close(fd[0]);
		dup2(fd_file[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		cmd = ft_split(av[2], ' ');
		if (cmd[0] && ft_get_path(cmd[0], envp))
		{
			execve(ft_get_path(cmd[0], envp), cmd, envp);
			ft_free_paths(cmd);
		}
		else
			ft_cmd_not_found(cmd);
	}
}

void	child2_process(int *fd_file, int *fd, char **av, char **envp)
{
	char	**cmd;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error("Fork");
	if (pid == 0)
	{
		fd_file[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_file[1] < 0)
			ft_error(av[4]);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		dup2(fd_file[1], STDOUT_FILENO);
		cmd = ft_split(av[3], ' ');
		if (cmd[0] && ft_get_path(cmd[0], envp))
		{
			execve(ft_get_path(cmd[0], envp), cmd, envp);
			ft_free_paths(cmd);
		}
		else
			ft_cmd_not_found(cmd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	fd_file[2];
	int	fd[2]
	;

	errno = 0;
	if (argc == 5)
	{
		pipe(fd);
		if (pipe(fd) < 0)
			ft_error(NULL);
		child1_process(fd_file, fd, argv, envp);
		child2_process(fd_file, fd, argv, envp);
		close(fd[0]);
		close(fd[1]);
		waitpid(-1, NULL, 0);
		waitpid(-1, NULL, 0);
	}
	else
		exit(EXIT_FAILURE);
	return (0);
} 
 */