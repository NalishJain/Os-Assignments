#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>


int main()
{


    float testCaseArray[4][3] = {{1.0,2.5,3.0}, {4.0,5.0,6.0}, {7.0,8.0,9.0}, {10.0,11.0,12.0}};

    float generatedArray[4][3];

    long sys_call_status;

    sys_call_status = syscall(451, testCaseArray, generatedArray, 4, 3);

    if (sys_call_status != EFAULT)
    {
        printf("System Call 451 twodcopy_system_call was successfuly invoked \n");
        printf("TestCaseArray was - \n");

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 3; j++){
                printf("%f ", testCaseArray[i][j]);
            }
            printf("\n");
        }

        printf("CopiedArray was - \n");

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 3; j++){
                printf("%f ", generatedArray[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}