#include "include/main.h"
#include <math.h>
#include "object/test_shape.h"
#include "include/parser.h"

void error_exit(char *error_msg)
{
    printf("%s\n", error_msg);
    exit(1);
}

int main(int argc, char *argv[]) 
{
    (void)argc;
    (void)argv;
    t_world *world = NULL;

    if (argc != 2)
        return 0;
    world = read_and_parse(argv);
    mlx_initialisation(world);  
    render(world);

    return 0;
}
