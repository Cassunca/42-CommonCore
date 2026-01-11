/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:17:23 by kamys             #+#    #+#             */
/*   Updated: 2026/01/10 22:57:09 by kamys            ###   ########.fr       */
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

void	free_tokens(t_token *tok)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok->next;
		free(tok->value);
		free(tok);
		tok = tmp;
	}
}

void	free_redir(t_redir *r)
{
	t_redir *next;

	while (r)
	{
		next = r->next;
		free(r->file);
		free(r);
		r = next;
	}
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
	}
	free_redir(cmd->redir);
	free(cmd);
}

void	free_ast(t_ast *root)
{
	if (!root)
		return ;
	free_ast(root->left);
	free_ast(root->right);
	if (root->type == NODE_CMD)
		free_cmd((t_cmd *)root->content);
	else
		free(root->content);
	free(root);
}

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
	if (ast_root)
		sh->last_status = execute_ast(ast_root, sh->env);
	free_ast(ast_root);
	free_tokens(token);
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
	rl_clear_history();
	rl_cleanup_after_signal();
	env_destroy(sh->env);
	alias_destroy(sh->aliases);
	printf("exit\n");
	return (status);
}
