#ifndef MEMORY_H
# define MEMORY_H

# include <stdio.h>
# include <stdlib.h>

typedef struct s_memoryAllocationInfo
{
	void	*ptr;
	size_t	size;
	char	*description;
}			t_memoryAllocationInfo;

void		*custom_malloc(size_t size, char *description);
void		custom_free(void *ptr);
void		print_memory_usage(void);
void		*allocate_and_report(size_t size, char *description);
void		cleanup_memory_tracking(void);
#endif
