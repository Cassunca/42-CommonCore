/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 02:32:19 by cassunca          #+#    #+#             */
/*   Updated: 2025/12/18 10:58:09 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef struct s_ast		t_ast;
typedef struct s_redir		t_redir;
typedef enum s_node_type	t_node_type;
typedef enum s_redir_type	t_redir_type;
typedef struct s_cmd		t_cmd;

int		execute_cmd(t_ast *cmd_node, char **envp);
int		apply_redirect(t_redir *redirs);
int		handle_redirect(t_ast *redir_node, char **envp);
int		execute_ast(t_ast *root, char **envp);
int		exec_simple_command(char *path_cmd, char **av, char **envp);

int		is_builtin(char **av);
int		execute_builtin(char **av);
char	*resolve_path(char *cmd, char **envp);
t_ast	*built_ast(t_token *tokens);
t_ast	*new_ast_node(t_node_type type, t_ast *left, t_ast *right, void *content);
t_cmd	*new_cmd_content(char **av);
int		is_exit (char **av);
int		execute_exit(char **av, char **env);
void	free_char_array(char **arr);
t_ast	*built_ast(t_token *tokens);
t_ast	*new_redir_node(t_ast *cmd_node, t_redir_type type, char *file);

#endif
