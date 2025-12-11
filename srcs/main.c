/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:17:23 by kamys             #+#    #+#             */
/*   Updated: 2026/01/22 11:09:45 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input(char	*line, t_shell *sh)
{
	t_token	*token;
	t_ast	*ast_root;

	token = lexer(line);
	if (!token)
		return ;
	ast_root = parser(token);
	expand_alias_ast(ast_root, sh);
	expand_ast(ast_root, sh->env);
	if (traverse_ast_heredoc(ast_root, sh) == INTERRUPTED_BY_SIGINT)
	{
		free_ast(ast_root);
		free_tokens(token);
		return ;
	}
	if (ast_root)
		sh->last_status = execute_ast(ast_root, sh->env);
	free_ast(ast_root);
	free_tokens(token);
	unlink(".heredoc_tmp");
}

int	run_interactive_shell(t_shell *sh)
{
	char		*line;
	char		*prompt;

	while (1)
	{
		prompt = get_prompt(sh->env);
		line = readline(prompt);
		free(prompt);
		if (!line)
			break ;
		if (*line)
			add_history(line);
		input(line, sh);
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
	t_shell		*sh;
	int			status;

	status = 1;
	sh = malloc(sizeof(t_shell));
	if (!sh)
		return (status);
	sh->env = env_init(97, envp);
	if (!sh->env)
	{
		free(sh);
		return (status);
	}
	setup_sig();
	init_ps1(sh->env);
	sh->aliases = init_alias(97);
	if (argc >= 3)
		status = run_command_mode(argv);
	else if (isatty(STDIN_FILENO))
		status = run_interactive_shell(sh);
	clean_up(sh);
	printf("exit\n");
	return (status);
}
