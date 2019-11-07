/*
 * by howif
 * 2019/11/7 14 : 22
 * modbus tcp master demo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "modbus_tcp_poll.h"
#define PORT 502


int xfer_init(char *addr, int port)
{
    int s,ct;

    struct sockaddr_in server_addr;
 
    s=socket(AF_INET,SOCK_STREAM,0);
    if(s<0)
    {
        printf("socket error\n");
        return -1;
    }
 
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=inet_addr(addr);
    server_addr.sin_port=htons(port);

    ct=connect(s,(struct sockaddr *)&server_addr,sizeof(struct sockaddr));
    if(ct<0)
    {
        printf("connect error\n");
        return -1;
    }
    
    return s;
}

/*
*  should add error detection
*/
int build_msg(modbus_poll_tx_msg *msg,
               unsigned int msg_id,
               unsigned int msg_len, /* is msg_len == buf_len + 6 ?? I am not sure */
               unsigned int slave_id,
               unsigned int function, 
               unsigned int start_addr,
               unsigned int xfer_len,
               unsigned char *data,
               unsigned int buf_len
               )
{
    msg->msg_id[0] = (msg_id >> 8) & 0xff;
    msg->msg_id[1] = msg_id & 0xff;

    msg->identification[0] = 0;
    msg->identification[1] = 0;

    msg->len[0] = ((msg_len - 6) >> 8) & 0xff;
    msg->len[1] = (msg_len - 6) & 0xff;
    
    msg->slave_id = slave_id & 0xff;

    msg->function = function & 0xff;
    
    msg->start_addr[0] = (start_addr >> 8) & 0xff;
    msg->start_addr[1] = start_addr & 0xff;
    
    msg->xfer_len[0] = (xfer_len >> 8) & 0xff;
    msg->xfer_len[1] = xfer_len & 0xff;
    
    if (data != NULL && buf_len != 0)
    {
        memcpy(msg->data, data, buf_len);
    }
    
    return 0;
}

void xfer_end(int s)
{
    close(s);
}

/*
* read coils every 2 seconds
*/

int demo_fun_01(void)
{
    int s;
    int recv,send;
    unsigned char buff[1024];
    modbus_poll_tx_msg msg;
    unsigned int msg_id = 0;
    unsigned int msg_len = 12;
    unsigned int start_addr = 0;
    unsigned int xfer_len = 0x0a;
    int cnt;
    s = xfer_init("192.168.17.171", 502);
    
    build_msg(&msg, msg_id, msg_len, 1, 1, start_addr, xfer_len, NULL, 0);

    while(1)
    {
        send=write(s,(char *)&msg,msg_len);
        if(send<0)
        {
            printf("send error\n");
            return -1;
        }
        
        recv=read(s,buff,1024); 
        if(recv>0)
        {
            write(1,buff,recv);
        }
        
#ifdef DEBUG_TX
        for (cnt=0; cnt < msg_len; cnt ++)
        {
           printf("%d : tx  msg[0x%x] = 0x%x\n", msg_id, cnt, ((unsigned char *)(&msg))[cnt]);
        }
#endif
#ifdef DEBUG_RX
        
        for (cnt=0; cnt < recv; cnt ++)
        {
           printf("%d : rx buff[0x%x] = 0x%x\n", msg_id, cnt, buff[cnt]);
        }
#endif
        msg_id++;
        msg.msg_id[0] = ((msg_id) >> 8) & 0xff;
        msg.msg_id[1] = (msg_id) & 0xff;
        sleep(2);
    }

    xfer_end(s);

    return 0;
}


int demo_fun_02(void)
{
    int s;
    int recv,send;
    unsigned char buff[1024];
    char request[12];
    modbus_poll_tx_msg msg;
    unsigned int msg_id = 0;
    unsigned int msg_len = 12;
    unsigned int start_addr = 0;
    unsigned int xfer_len = 0x0a;
    unsigned int slave_id = 1;
    unsigned int function = 0x2;
    int cnt;
    s = xfer_init("192.168.17.171", 502);
    
    build_msg(&msg, msg_id, msg_len, slave_id, function, start_addr, xfer_len, NULL, 0);

    while(1)
    {
        send=write(s,(char *)&msg,msg_len);
        if(send<0)
        {
            printf("send error\n");
            return -1;
        }
        
        recv=read(s,buff,1024); 
        if(recv>0)
        {
            write(1,buff,recv);
        }
#ifdef DEBUG_TX      
        for (cnt=0; cnt < msg_len; cnt ++)
        {
           printf("%d : tx  msg[0x%x] = 0x%x\n", msg_id, cnt, ((unsigned char *)(&msg))[cnt]);
        }
#endif
#ifdef DEBUG_RX
        
        for (cnt=0; cnt < recv; cnt ++)
        {
           printf("%d : rx buff[0x%x] = 0x%x\n", msg_id, cnt, buff[cnt]);
        }
#endif
        msg_id++;
        msg.msg_id[0] = ((msg_id) >> 8) & 0xff;
        msg.msg_id[1] = (msg_id) & 0xff;
        sleep(2);
    }
    
    xfer_end(s);
    
    return 0;
}


int demo_fun_03(void)
{
    int s;
    int recv,send;
    unsigned char buff[1024];
    modbus_poll_tx_msg msg;
    unsigned int msg_id = 0;
    unsigned int msg_len = 12;
    unsigned int start_addr = 0;
    unsigned int xfer_len = 0x0a;
    unsigned int slave_id = 1;
    unsigned int function = 0x3;
    int cnt;
    s = xfer_init("192.168.17.171", 502);
    
    build_msg(&msg, msg_id, msg_len, slave_id, function, start_addr, xfer_len, NULL, 0);

    while(1)
    {
        send=write(s,(char *)&msg,msg_len);
        if(send<0)
        {
            printf("send error\n");
            return -1;
        }
        
        recv=read(s,buff,1024); 
        if(recv>0)
        {
            write(1,buff,recv);
        }
#ifdef DEBUG_TX     
        for (cnt=0; cnt < msg_len; cnt ++)
        {
           printf("%d : tx  msg[0x%x] = 0x%x\n", msg_id, cnt, ((unsigned char *)(&msg))[cnt]);
        }
#endif
#ifdef DEBUG_RX
        for (cnt=0; cnt < recv; cnt ++)
        {
           printf("%d : rx buff[0x%x] = 0x%x\n", msg_id, cnt, buff[cnt]);
        }
#endif
        
        msg_id++;
        msg.msg_id[0] = ((msg_id) >> 8) & 0xff;
    msg.msg_id[1] = (msg_id) & 0xff;
        sleep(2);
    }
    
    xfer_end(s);
    
    return 0;
}

int demo_fun_04(void)
{
    int s;
    int recv,send;
    unsigned char buff[1024];
    modbus_poll_tx_msg msg;
    unsigned int msg_id = 0;
    unsigned int msg_len = 12;
    unsigned int start_addr = 0;
    unsigned int xfer_len = 0x0a;
    unsigned int slave_id = 1;
    unsigned int function = 0x4;
    int cnt;
    s = xfer_init("192.168.17.171", 502);
    
    build_msg(&msg, msg_id, msg_len, slave_id, function, start_addr, xfer_len, NULL, 0);

    while(1)
    {
        send=write(s,(char *)&msg,msg_len);
        if(send<0)
        {
            printf("send error\n");
            return -1;
        }
        
        recv=read(s,buff,1024); 
        if(recv>0)
        {
            write(1,buff,recv);
        }
#ifdef DEBUG_TX  
        for (cnt=0; cnt < msg_len; cnt ++)
        {
           printf("%d : tx  msg[0x%x] = 0x%x\n", msg_id, cnt, ((unsigned char *)(&msg))[cnt]);
        }
#endif
#ifdef DEBUG_RX
        
        for (cnt=0; cnt < recv; cnt ++)
        {
           printf("%d : rx buff[0x%x] = 0x%x\n", msg_id, cnt, buff[cnt]);
        }
#endif
        
        msg_id++;
        msg.msg_id[0] = ((msg_id) >> 8) & 0xff;
        msg.msg_id[1] = (msg_id) & 0xff;
        sleep(2);
    }
    
    xfer_end(s);
    
    return 0;
}


int demo_fun_05(void)
{
    int s;
    int recv,send;
    unsigned char buff[1024];
    modbus_poll_tx_msg msg;
    unsigned int msg_id = 0;
    unsigned int msg_len = 12;
    unsigned int start_addr = 0;
    unsigned int xfer_len = 0xff00; // 0xff00 open ;  0x0000 close
    unsigned int slave_id = 1;
    unsigned int function = 0x5;
	
    int cnt;
    s = xfer_init("192.168.17.171", 502);
	
    build_msg(&msg, msg_id, msg_len, slave_id, function, start_addr, xfer_len, NULL, 0);

    while(1)
    {
        send=write(s,(char *)&msg,msg_len);
        if(send<0)
        {
            printf("send error\n");
            return -1;
        }
        
        recv=read(s,buff,1024); 
        if(recv>0)
        {
            write(1,buff,recv);
        }
#ifdef DEBUG_TX  
        for (cnt=0; cnt < msg_len; cnt ++)
        {
           printf("%d : tx  msg[0x%x] = 0x%x\n", msg_id, cnt, ((unsigned char *)(&msg))[cnt]);
        }
#endif
#ifdef DEBUG_RX
        
        for (cnt=0; cnt < recv; cnt ++)
        {
           printf("%d : rx buff[0x%x] = 0x%x\n", msg_id, cnt, buff[cnt]);
        }
#endif
        
        msg_id++;
        msg.msg_id[0] = ((msg_id) >> 8) & 0xff;
        msg.msg_id[1] = (msg_id) & 0xff;
        msg.xfer_len[0] = ((msg_id % 2) ? 0 : 0xff);
        sleep(2);
    }
    
    xfer_end(s);
    
    return 0;
}



int main(void)
{
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
        case 1: demo_fun_01(); break;
        case 2: demo_fun_02(); break;
        case 3: demo_fun_03(); break;
        case 4: demo_fun_04(); break;
        case 5: demo_fun_05(); break;
        default: break;
    }    



    return 0;
}
