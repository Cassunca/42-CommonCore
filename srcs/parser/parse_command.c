/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:15:16 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/20 13:55:09 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir	*redirs(t_token **tokens, t_token_type type)
{
	t_redir			*redir;
	t_redir_type	rtype;
	t_redir			*r;

	redir = NULL;
	rtype = redir_type(type);
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TK_WORD)
	{
		printf("Error: filename expected\n");
		exit (1);
	}
	r = malloc(sizeof(t_redir));
	r->type = rtype;
	r->file = ft_strdup((*tokens)->value);
	r->next = redir;
	redir = r;
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
	t_redir			*redir;
	t_cmd			*cmd;

	redir = NULL;
	cmd = ft_calloc(1, sizeof(t_cmd));
	while (*tokens)
	{
		type = (*tokens)->type;
		if (is_stop_token(type))
			break ;
		if (type == TK_REDIR_IN || type == TK_REDIR_OUT || type == TK_APPEND || type == TK_HEREDOC)
		{
			redir = redirs(tokens, type);
			continue ;
		}
		if (type == TK_WORD)
		{
			add_word_arg(cmd, tokens);
			continue ;
		}
	}
	cmd->redir = redir;
	cmd->alias_expanded = 0;
	return (new_node(NODE_CMD, NULL, NULL, cmd));
}
