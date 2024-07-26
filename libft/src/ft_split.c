/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:22:47 by plang             #+#    #+#             */
/*   Updated: 2024/02/12 17:02:13 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	void	ft_get_start(const char **s, char c)
{
	while (**s && **s == c)
	{
		(*s)++;
	}
}

static	int	ft_word_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static	int	ft_word_position(char const *s, char sep)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		while (s[i] == sep)
			i++;
		while (s[i] != '\0')
		{
			if (s[i] != sep)
			{
				while (s[i] != sep && s[i] != '\0')
				{
					len++;
					i++;
				}
				return (len);
			}
		}
	}
	return (len);
}

static	char	**ft_free(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		string_index;
	char	**strings;
	int		word_len;
	int		count;

	if (!s)
		return (NULL);
	count = ft_word_count(s, c);
	string_index = 0;
	strings = (char **)malloc((count + 1) * sizeof(char *));
	if (strings == 0)
		return (NULL);
	while (string_index < count)
	{
		ft_get_start(&s, c);
		word_len = ft_word_position(s, c);
		strings[string_index] = ft_substr(s, 0, word_len);
		if (strings[string_index] == 0)
			return (ft_free(strings));
		s += word_len;
		string_index++;
	}
	strings[string_index] = 0;
	return (strings);
}
