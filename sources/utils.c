/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:50:30 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/06 08:11:22 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <threads.h>

#ifndef FT_IO_BUFSIZE
# define FT_IO_BUFSIZE 4096
#endif

static
size_t	ft_strlen(const char *str)
{
	const char	*ostr = str;

	while (*str != 0)
		str++;
	return ((size_t)(str - ostr));
}

// Copies a null terminated array of strings into a single buffer
// Returns: NULL on full copy, or the mutated vec array for incomplete copies
static
const char	**ft_strvcpy(
	char **restrict			wdst	/*mutable pointer to a buffer*/,
	const char **restrict	vec		/*null terminated array of cstrings*/,
	char *restrict			end		/*end = pointer to the end of the buffer*/)
{
	const char	*restrict	src;
	char		*restrict	dst;
	size_t					length;
	size_t					space_left;

	dst = (char *restrict)*wdst;
	while (*vec != NULL)
	{
		src = (const char *restrict)*vec++;
		length = ft_strlen(src) + (*vec == NULL);
		while (length > 0)
		{
			if (dst >= end)
				return (vec - 1);
			space_left = (size_t)(end - dst);
			if (length < space_left)
				space_left = length;
			length -= space_left;
			while (space_left-- > 0)
				*dst++ = *src++;
			*wdst = dst;
			vec[-1] = src;
		}
	}
	return (NULL);
}

ssize_t	ft_writev(int fd, const char **vec, char endl)
{
	char		buffer[FT_IO_BUFSIZE];
	ssize_t		bytes_written;
	ssize_t		bytes_total;
	const char	**src = vec;
	char		*dst;

	if (vec == NULL || *vec == NULL)
		return (-1);
	bytes_total = 0;
	dst = buffer;
	src = ft_strvcpy(&dst, src, buffer + FT_IO_BUFSIZE);
	while (src != NULL)
	{
		bytes_written = write(fd, buffer, (size_t)(dst - buffer));
		if (bytes_written < 0)
			return (-1);
		bytes_total += bytes_written;
		dst = buffer;
		src = ft_strvcpy(&dst, src, buffer + FT_IO_BUFSIZE);
	}
	dst[-1] = endl;
	bytes_written = write(fd, buffer, (size_t)(dst - buffer - (endl == 0)));
	if (bytes_written < 0)
		return (-1);
	return (bytes_total + bytes_written);
}

char	*ft_itoa_r(int64_t number, char *ptr)
{
	const int8_t	sign = (number >= 0) - (number < 0);

	*ptr = 0;
	*(--ptr) = sign * (number % 10) + '0';
	number = sign * (number / 10);
	while (number != 0)
	{
		*(--ptr) = (number % 10) + '0';
		number /= 10;
	}
	if (sign == -1)
		*(--ptr) = '-';
	return (ptr);
}

// To do: set errno on overflow
int64_t	ft_strtol(const char *str)
{
	int64_t	number;
	int64_t	sign;

	number = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	sign = -1 + ((*str == '-') << 1);
	str += (sign == 1) || (*str == '+');
	while (*str >= '0' && *str <= '9')
		number = number * 10 - (*str++ - '0');
	return (sign * number);
}
