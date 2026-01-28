/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:17:23 by kamys             #+#    #+#             */
/*   Updated: 2026/01/28 14:12:50 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	input(char	*line, t_shell *sh)
{
	t_token	*token;
	t_ast	*ast_root;

	reset_signal();
	token = lexer(line);
	if (!token)
		return ;
	ast_root = parser(token);
	free_tokens(token);
	expand_alias_ast(ast_root, sh);
	if (traverse_ast_heredoc(ast_root, sh) == INTERRUPTED_BY_SIGINT)
	{
		free_ast(ast_root);
		reset_signal();
		unlink(".heredoc_tmp");
		return ;
	}
	if (ast_root)
		sh->last_status = execute_ast(ast_root, sh);
	free_ast(ast_root);
	unlink(".heredoc_tmp");
}

static void	exit_coder(t_shell *sh)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	sh->exit_code = sh->last_status;
	sh->should_exit = 1;
}

static void	run_interactive_shell(t_shell *sh)
{
	struct termios	term;
	char			*line;
	char			*prompt;
	int				exit_code;

	tcgetattr(STDIN_FILENO, &term);
	while (!sh->should_exit)
	{
		prompt = get_prompt(sh->env);
		line = readline(prompt);
		free(prompt);
		if (!line)
		{
			exit_coder(sh);
			break ;
		}
		if (*line)
			add_history(line);
		input(line, sh);
		free(line);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	exit_code = sh->exit_code;
	clean_up(sh);
	exit(exit_code);
}

static int	run_command_mode(char **argv, t_shell *sh)
{
	if (!ft_strncmp(argv[1], "-c", 2))
	{
		if (argv[2])
			input(argv[2], sh);
		exit (sh->last_status);
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
	shell_upadate(sh);
	init_ps1(sh->env);
	sh->aliases = init_alias(97);
	sh->should_exit = 0;
	if (argc >= 3)
		status = run_command_mode(argv, sh);
	else if (isatty(STDIN_FILENO))
		run_interactive_shell(sh);
	return (status);
}
