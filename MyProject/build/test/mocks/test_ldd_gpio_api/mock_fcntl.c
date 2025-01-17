#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "mock_fcntl.h"


static struct mock_fcntlInstance
{
  unsigned char placeHolder;
} Mock;

extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void mock_fcntl_Verify(void)
{
}

void mock_fcntl_Init(void)
{
  mock_fcntl_Destroy();
}

void mock_fcntl_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

