/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 17:35:41 by arochard          #+#    #+#             */
/*   Updated: 2016/06/10 17:35:44 by arochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

size_t				limit_alloc(size_t size)
{
	struct rlimit	rl;

	if (getrlimit(RLIMIT_AS, &rl) == -1)
		return (-1);
	return (size);
}
