/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 12:28:27 by cassunca          #+#    #+#             */
/*   Updated: 2026/01/06 13:58:30 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	handle_and(t_ast *root, t_env_table *env)
{
	int	status;

	status = execute_ast(root->left, env);
	if (status == 0)
		return (execute_ast(root->right, env));
	return (status);
}
