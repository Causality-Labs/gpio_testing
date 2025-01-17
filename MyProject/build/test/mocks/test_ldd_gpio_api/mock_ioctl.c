#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "mock_ioctl.h"


static struct mock_ioctlInstance
{
  unsigned char placeHolder;
} Mock;

extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void mock_ioctl_Verify(void)
{
}

void mock_ioctl_Init(void)
{
  mock_ioctl_Destroy();
}

void mock_ioctl_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

