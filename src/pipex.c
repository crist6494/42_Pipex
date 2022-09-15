/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:57:40 by cmorales          #+#    #+#             */
/*   Updated: 2022/09/15 21:07:08 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child1_process(int *fd, char **argv, char **envp)
{
	int		fd_file;
	char	*path;
	char	**cmd;
	
	close(fd[1]);
	fd_file = open(argv[1], O_RDONLY);
	ft_check_fd(fd_file);
	dup2(fd_file, STDIN_FILENO);
	dup2(fd[1],STDOUT_FILENO);
	close(fd_file);
	close(fd[1]);
	cmd = ft_split(argv[2], ' ');
	path = ft_get_the_path(cmd[0], envp);
	if (execve(path, cmd, envp) == -1)
		ft_cmd_not_found(cmd, path);
	else
	{
		execve(path, cmd, envp);
		ft_free_paths(cmd);
		free(path);
	}
}

void	child2_process(int *fd, char **argv, char **envp)
{
	int		fd_file;
	char	*path;
	char	**cmd;

	close(fd[0]);
	fd_file = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT);
	ft_check_fd(fd_file);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_file,STDOUT_FILENO);
	close(fd[0]);
	close(fd_file);
	cmd = ft_split(argv[3], ' ');
	path = ft_get_the_path(cmd[0], envp);
	if (execve(path, cmd, envp) == -1)
		ft_cmd_not_found(cmd, path);
	else
	{
		execve(path, cmd, envp);
		ft_free_paths(cmd);
		free(path);
	}
}

void	pipex(char **argv, char **envp)
{
	int	fd[2];
	pid_t	pid;
	
	pipe(fd);
	pid = fork();
	if (pid < 0)
		perror("Fork:");
	else if (pid == 0)
		child1_process(fd, argv, envp);
	else
	{
		pid = fork();
		if (pid < 0)
		perror("Fork:");
		else if (pid == 0)
		child2_process(fd, argv, envp);
		else
		{
			close(fd[0]);
			close(fd[1]);
		}
	}
	waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return(EXIT_FAILURE);
	pipex(argv, envp);
	return (0);
}