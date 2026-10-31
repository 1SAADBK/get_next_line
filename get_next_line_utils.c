/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenkass <sbenkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:43:51 by sbenkass          #+#    #+#             */
/*   Updated: 2026/01/17 17:52:35 by sbenkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_str_len(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_strnl(char *stash)
{
	int	i;

	i = 0;
	if (!stash)
		return (0);
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	clear_stash(char **stash)
{
	free(*stash);
	*stash = NULL;
}

char	*clear_stash_str(char **stash, char **str_ptr)
{
	free(*stash);
	*stash = NULL;
	free(*str_ptr);
	*str_ptr = NULL;
	return (NULL);
}
