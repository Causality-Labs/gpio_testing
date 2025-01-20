#include "ime_lib.h"
#include "Display.h"
#include <fcntl.h>
#include <string.h>
#include <linux/gpio.h>


int add_numbers(int x, int y)
{
    return (x + y);
}

int DrawPoint(struct point pt)
{
    if(Draw_Int(pt.x) < 0)
    {
        return -1;
    }

    if(Draw_Int(pt.y) < 0)
    {
        return -1;
    }

   return 0;
}
struct point MakePoint(int x , int y)
{
   struct point pt = {
                     .x = x,
                     .y = y
                     };

    return pt;
}

int init_Display(int x, int y)
{
    struct point pt = MakePoint(x,y);
    if(Draw_Int(pt.x) < 0)
    {
        return -1;
    }

    if(Draw_Int(pt.y) < 0)
    {
        return -1;
    }

    return 0;    
}

int ime_open(const char * file_name)
{
    int ret = 0;

    ret = open(file_name, O_RDWR);

    if (ret < 0)
    {
        return -1;
    }
    
    return ret;
}

int ime_ioctl(int fd, unsigned long request)
{
    int ret = 0;
    struct gpiochip_info chip_info = {0};

    ret = ioctl(fd, request, &chip_info);
    if(ret != 0)
    {
        return -1;
    }

    return 0;
}