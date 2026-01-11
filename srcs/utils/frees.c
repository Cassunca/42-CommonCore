/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:53:20 by kamys             #+#    #+#             */
/*   Updated: 2026/01/11 20:55:24 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_up(t_shell *sh)
{
	rl_clear_history();
	rl_cleanup_after_signal();
	env_destroy(sh->env);
	alias_destroy(sh->aliases);
	free(sh);
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
	t_redir	*next;

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
