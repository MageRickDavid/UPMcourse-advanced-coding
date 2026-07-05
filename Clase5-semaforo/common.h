/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 19:11:23 by rortiz            #+#    #+#             */
/*   Updated: 2026/07/06 01:31:58 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H_
# define COMMON_H_

#include    <stdlib.h>
#include    <unistd.h>

#define SEM_1   0
#define SEM_2   1
#define CLAVE   1


/**
 * @brief Implements a pause between 1 and 3 seconds
 * @param {int} memory_id: The id of the shared memory.
 */
void pausa()
{
    int     pausa;
    
    pausa = 1000 + (int)(2000 * (random() / (float)RAND_MAX));
    usleep(pausa * 1000);
}
#endif