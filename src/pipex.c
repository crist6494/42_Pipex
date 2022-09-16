/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:57:40 by cmorales          #+#    #+#             */
/*   Updated: 2022/09/16 20:39:37 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(int *fd, char **argv, char **envp)
{
	int		fd_file;
	char	*path;
	char	**cmd;
	
	fd_file = open(argv[1], O_RDONLY, 0777);
	ft_check_fd(fd_file);
	dup2(fd_file, STDIN_FILENO);
	dup2(fd[1],STDOUT_FILENO);
	close(fd[0]);
	cmd = ft_split(argv[2], ' ');
	path = ft_get_path(cmd[0], envp);
	if (execve(path, cmd, envp) == -1)
		ft_cmd_not_found(cmd, path);
	else
		execve(path, cmd, envp);
		ft_free_paths(cmd);
		free(path);
}

void	parent_process(int *fd, char **argv, char **envp)
{
	int		fd_file;
	char	*path;
	char	**cmd;

	fd_file = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	ft_check_fd(fd_file);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_file,STDOUT_FILENO);
	close(fd[1]);
	cmd = ft_split(argv[3], ' ');
	path = ft_get_path(cmd[0], envp);
	if (execve(path, cmd, envp) == -1)
		ft_cmd_not_found(cmd, path);
	else
	{
		execve(path, cmd, envp);
		ft_free_paths(cmd);
		free(path);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	pid_t	pid;
	
	if (argc == 5)
	{
		pipe(fd);
		if (pipe(fd) == -1)
			exit(EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			perror("Pipex:");
		if (pid == 0)
			child_process(fd, argv, envp);
		waitpid(pid, NULL, 0);
		parent_process(fd, argv, envp);
	}
	else
		return(EXIT_FAILURE);
	return (0);
}