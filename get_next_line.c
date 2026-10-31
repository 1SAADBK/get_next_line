/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenkass <sbenkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:43:47 by sbenkass          #+#    #+#             */
/*   Updated: 2026/01/19 12:50:57 by sbenkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*append_to_stash(char **stash, char *buffer)
{
	char	*new_stash;
	int		len;
	int		i;
	int		j;

	len = ft_str_len(*stash) + ft_str_len(buffer);
	i = 0;
	j = 0;
	new_stash = malloc((len + 1) * sizeof(char));
	if (!new_stash)
		return (free(*stash), *stash = NULL);
	while ((*stash) && (*stash)[i])
	{
		new_stash[i] = (*stash)[i];
		i++;
	}
	while (buffer[j])
	{
		new_stash[i + j] = buffer[j];
		j++;
	}
	new_stash[i + j] = '\0';
	free(*stash);
	return (new_stash);
}

static char	*append_to_line(char **stash)
{
	int		i;
	int		j;
	char	*line;

	if (!*stash)
		return (NULL);
	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i])
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (free(*stash), (*stash) = NULL);
	j = 0;
	while (j < i)
	{
		line[j] = (*stash)[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static void	prepare_stash_buffer(char **stash, char **buffer)
{
	char	*new_stash;
	int		i;
	int		j;
	int		len;

	free(*buffer);
	*buffer = NULL;
	if (!*stash)
		return ;
	i = 0;
	len = ft_str_len(*stash);
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i])
		i++;
	new_stash = malloc((len - i + 1) * sizeof(char));
	if (!new_stash)
		return (clear_stash(stash));
	j = 0;
	while ((*stash)[i])
		new_stash[j++] = (*stash)[i++];
	new_stash[j] = '\0';
	free(*stash);
	*stash = new_stash;
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;
	int			readed;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(stash), stash = NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(stash), stash = NULL);
	readed = 1;
	while (readed && !ft_strnl(stash))
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed < 0)
			return (clear_stash_str(&stash, &buffer));
		buffer[readed] = '\0';
		stash = append_to_stash(&stash, buffer);
	}
	line = append_to_line(&stash);
	prepare_stash_buffer(&stash, &buffer);
	if (line && line[0] == '\0')
		return (clear_stash_str(&stash, &line));
	return (line);
}
