#include "examples_common.h"

int open_location(ipinfo iplist,int flag){
    if (iplist->is_ssh && flag==WRITE)      // scp写
    {
        // ssh连接
        if(!(iplist->session=connect_ssh(iplist->ip,iplist->user,iplist->port,iplist->pawd))){
            fprintf(stderr, "ssh连接失败\n");
            return -1;
        }
        // 新建scp会话
        if (!(iplist->scp=ssh_scp_new(iplist->session,SSH_SCP_WRITE,iplist->path)))
        {
            fprintf(stderr, "scp会话新建失败\n");
            return -1;
        }
        // 初始化scp会话
        if (ssh_scp_init(iplist->scp)==SSH_ERROR)
        {
            fprintf(stderr, "scp会话初始化失败\n");
            ssh_scp_free(iplist->scp);
            return -1;
        }
        return 0;
    }else if (iplist->is_ssh && flag==READ)     // scp读
    {
        // ssh连接
        if(!(iplist->session=connect_ssh(iplist->ip,iplist->user,iplist->port,iplist->pawd))){
            fprintf(stderr, "ssh连接失败\n");
            return -1;
        }
        // 新建scp会话
        if (!(iplist->scp=ssh_scp_new(iplist->session,SSH_SCP_READ,iplist->path)))
        {
            fprintf(stderr, "scp会话新建失败\n");
            return -1;
        }
        // 初始化scp会话
        if (ssh_scp_init(iplist->scp)==SSH_ERROR)
        {
            fprintf(stderr, "scp会话初始化失败\n");
            ssh_scp_free(iplist->scp);
            return -1;
        }
        return 0;        
    }else{      // scp文件
        if (!(iplist->file=fopen(iplist->path,flag==READ ? "r":"w")))
        {
            if (errno==EISDIR)
            {
                if (chdir(iplist->path))
                {
                    fprintf(stderr, "改变目录失败\n");
                    return -1;
                }
                return 0;
            }
            fprintf(stderr, "fopen打开path文件失败\n");
            return -1;
        }
        return 0;
    }
    return -1;
}

int libssh_scp(ipinfo iplist){
    if (open_location(iplist,WRITE)<0)
    {
        fprintf(stderr, "open_location失败\n");
        return -1;        
    }
    extern ipinfo location;
    printf("%s\n", location->ip);
    return 0;
}
