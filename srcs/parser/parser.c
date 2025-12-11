/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:42:06 by kamys             #+#    #+#             */
/*   Updated: 2025/12/11 05:42:14 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*parse_simple(t_token **tokens)
{
	if (*tokens && (*tokens)->type == TK_LPAREN)
		return (parse_subshell(tokens));
	return (parse_command(tokens));
}

t_ast	*parser(t_token *tokens)
{
	t_ast	*ast;

	if (check_syntax(tokens))
		return (NULL);
	ast = parse_sequence(&tokens);
	return (ast);
}
