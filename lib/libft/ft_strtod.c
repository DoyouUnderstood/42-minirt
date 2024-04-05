#include "libft.h"

static void	make_double(char *s, double *integer, double *fractional, int *neg);
static void	make_fractional(char *s, double *fractional);

double	ft_strtod(char *s)
{
	double	integer;
	double	fractional;
	int		neg;

	integer = 0;
	fractional = 0;
	neg = 0;
	make_double(s, &integer, &fractional, &neg);
	if (neg)
		return (-integer - fractional);
	else
		return (integer + fractional);
}

static void	make_double(char *s, double *integer, double *fractional, int *neg)
{
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			*neg = 1;
		s++;
	}
	if (!ft_isdigit(*s))
	{
        printf("File Format Error");
        exit(1);
    }	
	while (ft_isdigit(*s))
	{
		if (*integer >  2147483647 / 10 || (*integer ==  2147483647 && *s > '7'))
        {
            printf("File Format Error (Integer Overflow)");
            exit(1);
        }
		*integer = *integer * 10 + *s - '0';
		++s;
	}
	make_fractional(s, fractional);
}

static void	make_fractional(char *s, double *fractional)
{
	double	len;

	len = 0;
	if (*s == '.')
	{
		++s;
		while (ft_isdigit(*s))
		{
			*fractional = *fractional * 10 + *s - '0';
			++len;
			++s;
		}
		if (len == 0)
		{
            printf("File Format Error");
            exit(1);
        }	    
		while (len > 0)
		{
			*fractional /= 10;
			--len;
		}
	}
	// if (*s != '\0')
	// {
	// 	printf("fsdfsdfds\n");
    //     printf("File Format Error");
    //     exit(1);
    // }	
}