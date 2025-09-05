/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:13:49 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/05 14:13:51 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*read_and_store(int fd, char *backup, t_gc *gc)
{
	ssize_t	bytes_read;
	char	*buffer;

	buffer = gc_malloc(gc, ((size_t)BUFFER_SIZE + 1) * sizeof(char));
	bytes_read = 1;
	while (!ft_strchr(backup, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		buffer[bytes_read] = '\0';
		backup = ft_strjoin(backup, buffer, gc);
	}
	return (backup);
}

char	*reset_backup(char *backup, t_gc *gc)
{
	int		i;
	int		j;
	char	*new_backup;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
		return (NULL);
	if (backup[i] == '\n')
		i += 1;
	new_backup = gc_malloc(gc, (ft_strlen(backup) - i + 1) * sizeof(char));
	j = 0;
	while (backup[i])
		new_backup[j++] = backup[i++];
	new_backup[j] = '\0';
	return (new_backup);
}

char	*extract_line(char *backup, t_gc *gc)
{
	char	*str_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!*backup)
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	if (backup[i] == '\n')
		i += 1;
	str_line = (char *)gc_malloc(gc, (i + 1) * sizeof(char));
	while (j < i && backup[j])
	{
		str_line[j] = backup[j];
		j++;
	}
	str_line[i] = '\0';
	return (str_line);
}

char	*get_next_line(int fd, t_gc *gc)
{
	char		*line;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	backup = read_and_store(fd, backup, gc);
	line = extract_line(backup, gc);
	backup = reset_backup(backup, gc);
	return (line);
}
