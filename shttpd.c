//
// Created by leechain on 2022/3/5.
//
#include "shttpd.h"

static void sig_int(int num);
static void sig_pipe(int num);
int do_listen();



//主函数
int main(int argc,char *argv[])
{
    signal(SIGINT,sig_int);//挂接信号
    Para_Init(argc,argv);//参数初始化
    int s=do_listen();//套接字初始化
    Worker_ScheduleRun(s);//任务调度
    return 0;
}





//SIGINT信号截取函数
static void sig_int(int num) {
    Worker_ScheduleStop();
    return;
}

//SIGPIPE信号截取函数
static void sig_pipe(int num) {
    return;
}


//套接字初始化
int do_listen() {
    struct sockaddr_in server;
    int ss = -1;
    int err = -1;
    int reuse = 1;
    int ret = -1;

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sinport = htons(conf_para.ListenPort);

    signal(SIGINT, sig_int);
    signal(SIGPIPE, sig_pipe);

    ss = socket(AF_INET, SOCK_STREAM, 0);
    if (ss == -1) {
        printf("socket() error!\n");
        ret = -1;
        goto EXITshttpd_listen;
    }
    //设置套接字地址和端口复用
    err = setsockopt(ss, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    if (err == -1) {
        printf("setsockopt SO_REUSEADDR failed\n");
    }
    //绑定IP和套接字描述符
    err = bind(ss, (struct sockaddr *) &server, sizeof(server));
    if (err == -1) {
        printf("bind() error!\n");
        ret = -2;
        goto EXITshttpd_listen;
    }
    //设置服务器监听队列长度
    err = listen(ss, conf_para.MaxClient * 2);
    if (err == -1) {
        printf("listen() error!\n");
        ret = -3;
        goto EXITshttpd_listen;
    }

    ret = ss;
    EXITshttpd_listen:
    return ret;
}


int l_main()
{
    int ss=-1;
    ss=do_listen();
    return 0;
}











