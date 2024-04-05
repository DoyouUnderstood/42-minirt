#include "libft.h"

int ft_atod(const char *str, double *nbr)
{
    double result = 0;
    double fraction = 0.0;
    int divisor = 1;
    bool negative = false;

    while (ft_isspace(*str)) 
        str++;
    if (*str == '+' || *str == '-')
    {
        negative = (*str == '-');
        str++;
    }

    while (ft_isdigit(*str))
    {
        result = result * 10.0 + (*str - '0');
        str++;
    }

    if (*str == '.')
    {
        str++;
        while (ft_isdigit(*str))
        {
            fraction = fraction * 10.0 + (*str - '0');
            divisor *= 10;
            str++;
        }
    }

    result += fraction / divisor;

    if (negative)
        result = -result;

    *nbr = result;

    return (str != NULL);
}