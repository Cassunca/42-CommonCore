/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:40:05 by kamys             #+#    #+#             */
/*   Updated: 2025/12/09 14:14:22 by amyrodri         ###   ########.fr       */
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
}	t_node_type;

typedef struct s_ast
{
	t_node_type			type;
	struct s_ast		*left;
	struct s_ast		*right;
	void				*content;
}	t_ast;

typedef struct s_cmd
{
	char		**argv;
	int			argc;
}	t_cmd;

typedef enum s_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_token	t_token;

void	parser(t_token *tokens);

#endif