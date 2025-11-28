/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:17:23 by kamys             #+#    #+#             */
/*   Updated: 2025/11/28 15:18:27 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env_table *env)
{
	char	**new_env;
	size_t	i;

	new_env = env_export(env);
	i = 0;
	while (new_env[i])
		printf("%s\n", new_env[i++]);
}

void	input(char	*line, t_env_table	*env)
{
	t_token	*token;

	token = lexer(line);
	if (!token)
		return ;
	print_tokens(token);
	if (!ft_strncmp(line, "pwd", 4))
		printf("%s\n", env_get(env, "PWD"));
	if (!ft_strncmp(line, "env", 4))
		print_env(env);
	if (!ft_strncmp(line, "exit", 5))
	{
		free(line);
		printf("exit\n");
		exit(0);
	}
}

int	run_interactive_shell(t_env_table *env)
{
	char		*line;

	while (1)
	{
		line = readline(ft_strjoin(env_get(env, "USER"), " > "));
		if (!line)
			break ;
		if (*line)
			add_history(line);
		input(line, env);
		free(line);
	}
	return (0);
}

int	run_command_mode(char **argv)
{
	if (!ft_strncmp(argv[1], "-c", 2))
	{
		printf("algum dia vai começar a executar -> %s\n", argv[2]);
		exit (0);
	}
	ft_putstr_fd("usage: minishell -c \"command\"\n", 2);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_env_table	*env;
	int			status;

	status = 0;
	env = env_init(97, envp);
	if (!env)
		return (1);
	setup_sig();
	if (argc >= 3)
		status = run_command_mode(argv);
	else if (isatty(STDIN_FILENO))
		status = run_interactive_shell(env);
	rl_clear_history();
	rl_cleanup_after_signal();
	env_destroy(env);
	printf("exit\n");
	return (status);
}
