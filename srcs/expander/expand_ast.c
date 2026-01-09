/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:01:18 by kamys             #+#    #+#             */
/*   Updated: 2026/01/22 11:49:33 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expand_ast(t_ast *root, t_env_table *env)
{
	if (!root)
		return ;
	if (root->type == NODE_CMD)
		expand_cmd((t_cmd *)root->content, env);
	else if (root->type == NODE_REDIR)
		expand_redir((t_redir *)root->content, env);
	expand_ast(root->left, env);
	expand_ast(root->right, env);
}
