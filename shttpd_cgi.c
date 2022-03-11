//
// Created by leechain on 2022/3/5.
//

#include "shttpd.h"

#define CGISTR "/cgi-bin" //cgi目录的字符串
#define ARGNUM 16  //cgi程序变量的最大个数
#define READIN 0  //读出管道
#define WRITEOUT 1 //写入管道

int cgiHandler(struct worker_ctl *wctl)
{
    struct conn_request *req=&wctl->conn.con_req;
    struct conn_response *res=&wctl->conn.con_res;
    char *command=strstr(req->uri,CGISTR)+strlen(CGISTR);

}

