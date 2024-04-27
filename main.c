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
    world = read_and_parse(argv);
    mlx_initialisation(&world->mlx);  
    render(world);

    return 0;
}
