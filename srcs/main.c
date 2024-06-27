#include "../includes/cub3d.h"

int read_map(int fd)
{
    char *line;
    line = get_next_line(fd);
    while (line)
    {
		line = get_next_line(fd);
    }
}

int main(int argc, char **argv)
{
    int fd;

    fd = open(argv[1]);
    if (read_map(fd))
        // error check here
}