/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:40:05 by kamys             #+#    #+#             */
/*   Updated: 2026/01/13 13:28:09 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum s_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_REDIR,
	NODE_AND,
	NODE_OR,
	NODE_SEQ,
	NODE_SUB
}							t_node_type;

typedef struct s_ast
{
	t_node_type				type;
	struct s_ast			*left;
	struct s_ast			*right;
	void					*content;
}							t_ast;

typedef enum s_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}							t_redir_type;

typedef struct s_redir
{
	t_redir_type			type;
	char					*file;
	struct s_redir			*next;
}							t_redir;

typedef struct s_cmd
{
	char					**argv;
	int						argc;
	t_redir					*redir;
	int						alias_expanded;
}							t_cmd;

typedef enum s_token_type	t_token_type;

typedef struct s_token		t_token;
typedef enum s_token_type	t_token_type;

t_ast						*parser(t_token *tokens);
int							check_syntax(t_token *tokens);

t_ast						*parse_sequence(t_token **tokens);
t_ast						*parse_or(t_token **tokens);
t_ast						*parse_and(t_token **tokens);
t_ast						*parse_pipe(t_token **tokens);
t_ast						*parse_simple(t_token **tokens);
t_ast						*parse_subshell(t_token **tokens);
t_redir_type				redir_type(t_token_type type);
t_ast						*parse_command(t_token **tokens);

int							token_op(t_token_type token);
int							check_in_end(t_token *start, t_token *end);
int							check_inside(t_token *head, t_token *end);

#endif
