/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:59:58 by amyrodri          #+#    #+#             */
/*   Updated: 2025/12/05 16:58:20 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

// TODO: Revisar o comportamento do comando `env`
// O comando `env` NÃO deve usar `env_export()` porque:
// 1. `env_export()` pode incluir variáveis sem valor (Bash não mostra no env).
// 2. `env_export()` imprime variáveis ordenadas e formatadas para o export.
// 3. `env_export()` aloca memória (não existe free aqui → vazamento de memória).
//
// O `env` deve:
// - Iterar diretamente pela hash table (`env->buckets`)
// - Imprimir apenas variáveis que possuem valor (KEY=value)
// - Não imprimir "declare -x" nem ordenar
//
// Exemplo de correção:
// percorrer env->buckets e fazer:
//   if (curr->value != NULL)
//       printf("%s=%s\n", curr->key, curr->value);
//

void	print_env(t_env_table *env)
{
	char	**new_env;
	int		i;
	// slk vamo revisar tudo quando o Big Bang esturar novamente !_!
	new_env = env_export(env);
	i = 0;
	while (new_env[i])
		printf("%s\n", new_env[i++]);
}
