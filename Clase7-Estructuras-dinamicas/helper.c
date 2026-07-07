/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 09:39:57 by rortiz            #+#    #+#             */
/*   Updated: 2026/07/07 12:56:07 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"
#include <stdlib.h>
#include <stdio.h>


ptree   create_node(int value)
{
    ptree   node;

    node = malloc(sizeof(t_node));
    if (node == NULL)
    {
        perror("Malloc did not work");
        return ((void*)0);   
    }
    node -> value =  value;
    node -> left  =  (void*)0;
    node -> right =  (void*)0;
    return (node);
}

ptree	insert_node(ptree tree, int value)
{
	ptree   new_tree;
    
    if (tree == (void*)0)
    {
        new_tree = create_node(value);
        return (new_tree);   
    }
    if (value < tree -> value)
        tree -> left = insert_node(tree -> left, value);  
    else
        tree -> right = insert_node(tree -> right, value);
    return (tree);
}

ptree   vec2tree(ptree tree, int *vector, int num_elem)
{
    int i;

    i = 0;
    while (i < num_elem)
    {
        tree = insert_node(tree, vector[i]);
        i++;
    }
    return (tree);
}

void	tree2vec(ptree tree, int *vector, int *pos)
{
	if (tree == (void *)0)
		return ;
	tree2vec(tree->left, vector, pos);
	vector[*pos] = tree->value;
	(*pos)++;
	tree2vec(tree->right, vector, pos);
}

void	destroy_tree(ptree tree)
{
	if (tree == (void *)0)
		return ;
	destroy_tree(tree->left);
	destroy_tree(tree->right);
	free(tree);
}

void	sort(int *vector, int num_elem)
{
	ptree	tree;
	int		pos;

	tree = (void *)0;
	pos = 0;
	tree = vec2tree(tree, vector, num_elem);
	tree2vec(tree, vector, &pos);
	destroy_tree(tree);
}




