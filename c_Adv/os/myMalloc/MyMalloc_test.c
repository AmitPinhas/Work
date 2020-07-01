#include <stdio.h>

#include "MyMalloc.h"
#define FOREVER 1
void testCreate()
{
	void* ptr;
	ptr = MyMallocPoolCreate(5, 4);
	MyMallocDestroy(&ptr);
}

void testAllocate()
{
	void* ptr;
	int* buffInt[5];
	int i;
	ptr = MyMallocPoolCreate(5, 4 );
	while (FOREVER)
	{
		for (i = 0;i < 5;++i)
		{
			buffInt[i] = (void*)MyMallocAllocateBuffer(ptr);
			*buffInt[i] = 5 + i;
			printf("check for allocate if %d == %d, allocation work\n", *buffInt[i], 5 + i);
		}
		for (i = 0;i < 5;++i)
		{
			if (MyMallocFreeBuffer(ptr, (void*)buffInt[i]) != POOL_SUCCESS)
			{
				printf("Return Buffer fail\n");
			}
			else
			{
				printf("Return Buffer succes\n");
			}
		}
		for (i = 0;i < 6;++i)
		{
			buffInt[i] = (void*)MyMallocAllocateBuffer(ptr);
			*buffInt[i] = 5 + i;
			printf("check for allocate if %d == %d, allocation work\n", *buffInt[i], 5 + i);
		}
		for (i = 0;i < 5;++i)
		{
			if (MyMallocFreeBuffer(ptr, (void*)buffInt[i]) != POOL_SUCCESS)
			{
				printf("Return Buffer fail\n");
			}
			else
			{
				printf("Return Buffer succes\n");
			}
		}
	}
	MyMallocDestroy(&ptr);
}










int main()
{
	testCreate();
	testAllocate();
	return 1;
}
