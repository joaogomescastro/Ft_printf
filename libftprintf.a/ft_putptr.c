/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocast <joaocast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 17:41:09 by joaocast          #+#    #+#             */
/*   Updated: 2026/11/24 10:38:29 by joaocast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdint.h>

static int	ft_hex(uintptr_t n)
{
	char	*base;
	int		len;

	len = 0;
	base = "0123456789abcdef";
	if (n >= 16)
		len += ft_hex(n / 16);
	len += write(1, &base[n % 16], 1);
	return (len);
}

int	ft_putptr(void *ptr)
{
	uintptr_t	addr;
	int			len;

	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	addr = (uintptr_t)ptr;
	len = write(1, "0x", 2);
	len += ft_hex(addr);
	return (len);
}
