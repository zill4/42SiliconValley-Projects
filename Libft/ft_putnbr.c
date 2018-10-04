
void ft_putnbr(int n)
{
	int sign;
	sign = 1;
	if (n < 0)
	{
		ft_putchar('-');
		sign = -1;
	}

	if(-9 <= n && n <= 9)
	{
		ft_putchar(n * sign + '0');
	}
	else
	{
		ft_putnbr((n / 10) * sign);
		ft_putnbr((n % 10) * sign);
	}
}
