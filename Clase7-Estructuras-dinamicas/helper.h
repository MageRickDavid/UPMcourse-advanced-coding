/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 09:22:41 by rortiz            #+#    #+#             */
/*   Updated: 2026/07/07 12:46:55 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_node
{
    int             value;
    struct s_node   *left;
    struct s_node   *right;
} t_node;

typedef t_node	*ptree;

ptree  create_node(int value);
ptree	insert_node(ptree tree, int value);
ptree   vec2tree(ptree tree, int *vector, int num_elem);
void	destroy_tree(ptree tree);
void	tree2vec(ptree tree, int *vector, int *pos);
void	sort(int *vector, int num_elem);