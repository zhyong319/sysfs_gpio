#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

int SetValue(int sn, int v) //设置商品高OR低
{
    char*  pPathStr= malloc(50);
    memset(pPathStr, 0, malloc_usable_size(pPathStr));
    snprintf(pPathStr, malloc_usable_size(pPathStr), "/sys/class/gpio/gpio%d/value", sn);
    int fdValue = open(pPathStr, O_WRONLY);
    if(fdValue < 0) 
    {
        printf("open direction file failse\n");
        return 1;
    }
    // echo out > export
    char* pcmdstr = malloc(20);
    memset(pcmdstr, 0, malloc_usable_size(pcmdstr));
    snprintf(pcmdstr, 20, "%d", v);
    write(fdValue, pcmdstr, malloc_usable_size(pcmdstr));
    free(pcmdstr);
    free(pPathStr);
    close(fdValue);
    return 0;
}

int SetDirection(int sn, char* pstr) //设置端口out  in
{
    char* pPathStr = malloc(50);
    memset(pPathStr, 0, malloc_usable_size(pPathStr));                  
    int len = snprintf(pPathStr, malloc_usable_size(pPathStr), "/sys/class/gpio/gpio%d/direction", sn);
    printf ("len: %d\n", malloc_usable_size(pPathStr));
    printf("len: %d  cmd: %s\n", len, pPathStr);
    int fdDirection = open(pPathStr, O_WRONLY);
    if(fdDirection < 0) 
    {
        printf("open direction file failse\n");
        return 1;
    }
    char* pcmdstr = malloc(20);
    memset(pcmdstr, 0, malloc_usable_size(pcmdstr));
    snprintf(pcmdstr, 20, "%s",pstr);
    write(fdDirection, pcmdstr, malloc_usable_size(pcmdstr));
    free(pcmdstr);
    free(pPathStr);
    close(fdDirection);
    return 0;
}

int ExportGPIO(int sn) //导出指定端口
{
    int fdGPIO = open("/sys/class/gpio/export", O_WRONLY);
    if(fdGPIO < 0) 
    {
        printf("open export file failse\n");
        return 1;
    }
    char* pcmdstr = malloc(20);
    memset(pcmdstr, 0, malloc_usable_size(pcmdstr));
    snprintf(pcmdstr, 20, "%d",sn);
    write(fdGPIO, pcmdstr, malloc_usable_size(pcmdstr));
    free(pcmdstr);
    close(fdGPIO);
    return 0;
}

int UnExportGPIO(int sn) //释放指定端口
{
    int fdGPIO = open("/sys/class/gpio/unexport", O_WRONLY);
    if(fdGPIO < 0) 
    {
        printf("open unexport file failse\n");
        return 1;
    }
    char* pcmdstr = malloc(20);
    memset(pcmdstr, 0, malloc_usable_size(pcmdstr));
    snprintf(pcmdstr, 20, "%d",sn);
    write(fdGPIO, pcmdstr, malloc_usable_size(pcmdstr));
    free(pcmdstr);
    close(fdGPIO);
    return 0;
}



int main (int argc, char* argv[])
{
   int gpioSN = 20;
   ExportGPIO(gpioSN); 
   SetDirection(gpioSN, "out");
   SetValue(gpioSN, 1);
   sleep(10);
   SetValue(gpioSN, 0);
   UnExportGPIO(gpioSN);

   return 0;
} 