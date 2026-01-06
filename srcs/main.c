/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:17:23 by kamys             #+#    #+#             */
/*   Updated: 2026/01/06 15:40:47 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_built_in(t_env_table *env, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (cd(env, cmd));
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (echo(env, cmd));
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (print_env(env, cmd));
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (export(env, cmd));
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (pwd(env, cmd));
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (unset(env, cmd));
}

void	input(char	*line, t_env_table	*env)
{
	t_token	*token;
	t_ast	*ast;

	token = lexer(line);
	if (!token)
		return ;
	print_tokens(token);
	ast = parser(token);
	if (!ast)
		return ;
	if (ast->type == NODE_CMD)
		exec_built_in(env, (t_cmd *)ast->content);
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
