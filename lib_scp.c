#include "examples_common.h"

int open_location(ipinfo iplist,int flag){
    
    return 0;
}

int libssh_scp(ipinfo iplist){
    if (open_location(iplist,WRITE)<0)
    {
        fprintf(stderr, "open_location失败\n");
        return -1;        
    }
    return 0;
}
