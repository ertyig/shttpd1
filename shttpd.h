//
// Created by leechain on 2022/3/5.
//
#ifndef SHTTPD_SHTTPD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <getopt.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>

#define big_int_t long

int Worker_ScheduleRun(int ss);
int Worker_ScheduleStop();
void Para_Init(int argc, char *argv[]);
int Request_Parse(struct worker_ctl *wctl);
int Request_Handle(struct worker_ctl *wctl);



//SHTTPD 配置文件结构
struct conf_opts {
    char CGIRoot[128];
    char DefaultFile[128];
    char DocumentRoot[128];
    char ConfigFile[128];
    int ListenPort;
    int MaxClient;
    int TimeOut;
    int InitClient;
};

//默认的配置参数
struct conf_opts conf_para = {
        "/user/local/var/www/cgi-bin/",
        "index.html",
        "/usr/local/var/www",
        "/etc/SHTTPD.conf",
        8080,
        4,
        3,
        2
};

//
//struct option{
//    char *name;
//    int has_arg;
//    int *flag;
//    int val;
//};

//短选项
static char *shortopts = "c:d:f:h:o:l:m:t:";
//长选项
static struct option longopts[] =
        {
                {"CGIRoot",      required_argument, NULL, 'c'},
                {"ConfigFile",   required_argument, NULL, 'f'},
                {"DefaultFile",  required_argument, NULL, 'd'},
                {"DocumentRoot", required_argument, NULL, 'o'},
                {"ListenPort",   required_argument, NULL, 'l'},
                {"MaxClient",    required_argument, NULL, 'm'},
                {"TimeOut",      required_argument, NULL, 't'},
                {"Help",         required_argument, NULL, 'h'},
                {0,              0, 0,                    0},
        };


//表示文件内容的文件格式
struct mine_type {
    char *extension;//扩展名
    int type; //类型
    int ext_len; //扩展名长度
    char *mine_type; //内容类型
};


//HTTP协议的方法
typedef enum SHTTPD_METHOD_TYPE {
    METHOD_GET,
    METHOD_POST,
    METHOD_PUT,
    METHOD_DELETE,
    METHOD_HEAD,
    METHOD_CGI,
    METHOD_NOTSUPPORT
} SHTTPD_METHOD_TYPE;


//代表一个子串，用于解析
//请求方法的结构
typedef struct vec {
    char *ptr;//字符串
    int len;//字符串长度
    SHTTPD_METHOD_TYPE type;//字符串表示类型
} vec;


//将各种请求方法的结构放在结构数组中
struct vec _shttpd_methods[] = {
        {"GET",    3, METHOD_GET},
        {"POST",   4, METHOD_POST},
        {"PUT",    3, METHOD_PUT},
        {"DELETE", 6, METHOD_DELETE},
        {"HEAD",   4, METHOD_HEAD},
        {NULL,     0}
};


//用来保存任何类型的值
//这里来存储解析HTTP头部的值
union variant {
    char *v_str;
    int v_int;
    big_int_t v_big_int;
    time_t v_time;

    void (*v_func)(void);

    void *v_void;
    struct vec v_vec;
};


//不含第一行的HTTP头部
struct headers {
    union variant cl;   //Content-Length内容长度
    union variant ct;   //Content-Type内容类型
    union variant connection;   //Connection连接状态
    union variant ims;    //If-Modified-Since最后修改时间
    union variant user;   //Remote user name用户名称
    union variant auth;   //Authorization权限
    union variant useragent;    //User-Agent用户代理
    union variant cookie;   //Cookie
    union variant location;  //Location位置
    union variant range;   //Range范围
    union variant status;  //Status状态值
    union variant transenc;    //Transfer-Encoding编码类型
};


//http头部类型
enum {
    HDR_DATE, HDR_INT, HDR_STRING
};


struct http_header {
    int len; //头部名字长度
    int type; //头部类型
    size_t offset; //值占位符
    char *name; //头部名字
};

//x在headers中的偏移
#define OFFSET(x) offsetof(struct headers,x)


//业务线程的状态值
//   已初始化，      正在工作，       正在卸载，        已卸载，          空闲状态
enum {
    WORKER_INITED, WORKER_RUNNING, WORKER_DETACHING, WORKER_DETACHED, WORKER_IDEL
};


struct worker_opts {
    pthread_t th;//线程id
    int flags;//线程状态
    pthread_mutex_t mutex;//线程任务互斥
    struct worker_ctl *work;//本线程的总控结构
};

#define URI_MAX 16384
//请求结构
struct conn_request {
    struct vec req;//请求向量
    char *head;//请求头部，‘\0’结尾
    char *uri;//请求URI，'\0'结尾
    char rpath[URI_MAX];//请求文件的真实地址，'\0'结尾
    int method;//请求类型

    //HTTP的版本信息
    unsigned long major;//主版本
    unsigned long minor;//副版本

    struct headers ch;//头部结构

    struct worker_conn *conn;//连接结构指针
    int err;//错误代码
};

//响应结构
struct conn_response {
    struct vec res;//响应向量
    time_t birth_time;//建立时间
    time_t expire_time;//超时时间

    int status;//响应状态值
    int cl;//响应内容长度

    int fd;//请求文件描述符
    struct stat fstate;//请求文件状态

    struct worker_conn *conn;//连接结构指针
};


struct worker_conn {
#define K 1024
    char dreq[16 * K];//请求缓冲区
    char dres[16 * K];//响应缓冲区

    int cs;//与客户端连接的套接字文件描述符
    int to;//超时时间

    struct conn_response con_res;//响应结构
    struct conn_request con_req;//请求结构

    struct worker_ctl *work;//本线程的总控结构
};


struct worker_ctl {
    struct worker_opts opts;//表示线程的状态
    struct worker_conn conn;//客户端请求的状态和值
};


#define SHTTPD_SHTTPD_H

#endif //SHTTPD_SHTTPD_H
