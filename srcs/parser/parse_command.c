/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:15:16 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/22 12:08:22 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir	*redirs(t_token **tokens, t_token_type type)
{
	t_redir			*redir;
	t_redir_type	rtype;

	rtype = redir_type(type);
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TK_WORD)
	{
		printf("Error: filename expected\n");
		exit (1);
	}
	redir = malloc(sizeof(t_redir));
	redir->type = rtype;
	redir->file = ft_strdup((*tokens)->value);
	redir->next = NULL;
	*tokens = (*tokens)->next;
	return (redir);
}

void	add_word_arg(t_cmd *cmd, t_token **tokens)
{
	cmd->argv = realloc(cmd->argv, sizeof(char *) * (cmd->argc + 2));
	cmd->argv[cmd->argc] = ft_strdup((*tokens)->value);
	cmd->argv[cmd->argc + 1] = NULL;
	cmd->argc++;
	*tokens = (*tokens)->next;
}

int	is_stop_token(t_token_type type)
{
	return (type == TK_PIPE || type == TK_AND || type == TK_OR
		|| type == TK_LIST || type == TK_RPAREN);
}

t_ast	*new_node(t_node_type type, t_ast *left, t_ast *right, void *content)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	node->type = type;
	node->left = left;
	node->right = right;
	node->content = content;
	return (node);
}

t_ast	*parse_command(t_token **tokens)
{
	t_token_type	type;
	t_cmd			*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	while (*tokens)
	{
		type = (*tokens)->type;
		if (is_stop_token(type))
			break ;
		if (type == TK_REDIR_IN || type == TK_REDIR_OUT
			|| type == TK_APPEND || type == TK_HEREDOC)
		{
			add_redir_back(&cmd->redir, redirs(tokens, type));
			continue ;
		}
		if (type == TK_WORD)
		{
			add_word_arg(cmd, tokens);
			continue ;
		}
	}
	cmd->alias_expanded = 0;
	return (new_node(NODE_CMD, NULL, NULL, cmd));
}
