/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 13:29:23 by kyork             #+#    #+#             */
/*   Updated: 2016/10/04 22:28:02 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ws_split_wordcount(const char *str, char splitchr)
{
	size_t	word_count;
	int		last_status;

	last_status = 1;
	word_count = 0;
	while (*str)
	{
		if (last_status != (*str == splitchr))
			if (last_status)
				word_count++;
		last_status = (*str == splitchr);
		str++;
	}
	return (word_count);
}

static char		*ft_strdup_space(const char *str, char splitchr)
{
	size_t	len;
	int		dest_idx;
	char	*dest;

	len = 0;
	while (str[len] && !(str[len] == splitchr))
		len++;
	dest = (char*)malloc(len + 1);
	if (!dest)
		return (0);
	len = 0;
	dest_idx = 0;
	while (str[len] && !(str[len] == splitchr))
	{
		dest[dest_idx++] = str[len++];
	}
	dest[dest_idx] = 0;
	return (dest);
}

static void		ft_destroy_tab(char **tab)
{
	char **t;

	t = tab;
	while (*t)
	{
		free(*t++);
	}
	free(tab);
}

static int		ft_addtotab(
		char **tab,
		size_t word_count,
		const char *strptr,
		char splitchr)
{
	char	*n;

	n = ft_strdup_space(strptr, splitchr);
	if (!n)
	{
		tab[word_count] = 0;
		ft_destroy_tab(tab);
		return (0);
	}
	tab[word_count] = n;
	return (1);
}

char			**ft_strsplit(const char *str, char splitchr)
{
	size_t		word_count;
	int			last_status;
	const char	*s;
	char		**tab;

	if (!str)
		return (0);
	word_count = ws_split_wordcount(str, splitchr);
	tab = (char**)malloc(sizeof(char*) * (word_count + 1));
	if (!tab)
		return (NULL);
	s = str;
	last_status = 1;
	word_count = 0;
	while (*s)
	{
		if (last_status != (*s == splitchr))
			if (last_status && !ft_addtotab(tab, word_count++, s, splitchr))
				return (0);
		last_status = (*s == splitchr);
		s++;
	}
	tab[word_count] = 0;
	return (tab);
}
