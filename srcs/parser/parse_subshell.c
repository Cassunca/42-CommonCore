/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:16:58 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/14 13:38:36 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*parse_subshell(t_token **tokens)
{
	t_ast	*child;
	t_ast	*node;

	if (!*tokens || (*tokens)->type != TK_LPAREN)
		exit(1);
	*tokens = (*tokens)->next;
	child = parse_sequence(tokens);
	if (!*tokens || (*tokens)->type != TK_RPAREN)
	{
		printf("Error: unexpected ')'\n");
		exit(1);
	}
	*tokens = (*tokens)->next;
	node = malloc(sizeof(t_ast));
	node->type = NODE_SUB;
	node->left = child;
	node->right = NULL;
	node->content = NULL;
	return (node);
}
