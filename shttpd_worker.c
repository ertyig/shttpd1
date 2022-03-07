
#include "shttpd.h"
static struct worker_ctl *wctls=NULL;


struct woker_opts{
	pthread_t th;//线程id
	int flags;//线程状态
	pthread_mutex_t mutex;//线程任务互斥
	struct worker_ctl *work;//本线程的总控结构
};

//HTTP协议的方法
typedef enum SHTTPD_METHOD_TYPE
{
    METHOD_GET,
    METHOD_POST,
    METHOD_PUT,
    METHOD_DELETE,
    METHOD_HEAD,
    METHOD_CGI,
    METHOD_NOTSUPPORT
}SHTTPD_METHOD_TYPE;

//代表一个子串，用于解析
typedef struct vec
{
    char *ptr;
    int len;
    SHTTPD_METHOD_TYPE type;
}vec;


//用来保存任何类型的值
//这里来存储解析HTTP头部的值
union variant{
    char *v_str;
    int v_int;
    big_int_t v_big_int;
    time_t v_time;
    void (*v_func)(void);
    void *v_void;
    struct vec v_vec;
};


//保存解析的HTTP头部
struct headers {
    union variant cl;
    union variant ct;
    union variant connection;
    union variant ims;
    union variant user;
    union variant auth;
    union variant useragent;
    union variant cookie;
    union variant location;
    union variant range;
    union variant status;
    union transenc;
};













#define URI_MAX 16384
//请求结构
struct conn_request{
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
    int err;
};

//响应结构
struct conn_response{
    struct vec res;//响应向量
    time_t birth_time;//建立时间
    time_t expire_time;//超时时间

    int status;//响应状态值
    int cl;//响应内容长度

    int fd;//请求文件描述符
    struct stat fstate;//请求文件状态

    struct worker_conn *conn;//连接结构指针
};


struct worker_conn{
#define K 1024
    char dreq[16*K];//请求缓冲区
    char dres[16*K];//响应缓冲区

    int cs;//与客户端连接的套接字文件描述符
    int to;//超时时间

    struct conn_response con_res;//响应结构
    struct conn_request con_req;//请求结构

    struct worker_ctl *work;//本线程的总控结构
};


struct worker_ctl{
    struct woker_opts opts;//表示线程的状态
    struct worker_conn conn;//客户端请求的状态和值
};








//初始化线程
static void Worker_Init()
{
    DBGPRINT("==>Worker_Init\n");
    int i=0;
    //初始化总控参数
    wctls=(struct worker_ctl*)malloc(sizeof(struct worker_ctl)*conf_para.MaxClient);
    //清零
    memset(wctls,0,sizeof(struct worker_ctl)*conf_para.MaxClient);

    //初始化一些参数
    for(i=0;i<conf_para.MaxClient;i++)
    {
        //opts & conn结构与worker_ctl结构形成回指针
        wctls[i].opts.work=&wctls[i];
        wctls[i].conn.work=&wctls[i];

        //opts结构的初始化
        wctls[i].opts.flags=WORKER_DETACHED;//表示可以建立线程挂接到此结构上
        //wctls[i].opts.mutex=PTHREAD_MUTEX_INITIALIZER;
        pthread_mutex_init(&wctls[i].opts.mutex,NULL);
        pthread_mutex_lock(&wctls[i].opts.mutex);

        //conn结构的初始化
        //con_res & con_req与conn结构形成回指针
        wctls[i].conn.con_res.conn=&wctls[i].conn;
        wctls[i].conn.con_req.conn=&wctls[i].conn;
        wctls[i].conn.cs=-1;//与客户端连接的socket为空
        //con_req初始化

        //con_res初始化


    }

}


/*主调度过程,
//初始化多个处理客户端请求的业务线程
*	当有客户端连接到来的时候
*	将客户端连接分配给空闲客户端
*	由客户端处理到来的请求
*/
#define STATUS_RUNNING 1
#define STATUS_STOP 0
//调度状态
static int SCHEDULESTATUS=STATUS_RUNNING;

int  Worker_ScheduleRun(int ss)
{
    DBGPRINT("==>Worker_ScheduleRun\n");
    struct sockaddr_in client;
    socklen_t len=sizeof(client);
    //初始化业务线程
    Worker_Init();

    int i=0;
    //当调度状态为running时，select()等待客户端的连接
    for(;SCHEDULESTATUS==STATUS_RUNNING;)
    {
        struct timeval tv;//超时时间
        fd_set rds;//读文件集
        //printf("SCHEDULE_STATUS:%d\n",SCHEDULESTATUS);
        int retval=-1;
        //初始化文件集，将客户端连接文件描述符放入集合中
        FD_ZERO(&rfds);
        FD_SET(ss,&rfds);

        tv.tv_sec=0;
        tv.tv_usec=500000;

        retval=select(ss+1,&rfds,NULL,NULL,&tv);
        switch(retval)
        {
            case -1://错误
            case 0://超时
                continue;
                break;
            default:
                if(FD_ISSET(ss,&rfds))
                {
                    int sc=accept(ss,(struct sockaddr*)&client,&len);
                    printf("Client coming\n");
                    i=WORKER_ISSTATUS(WORKER_IDEL);//查找空闲线程
                    if(i==-1)//未找到空闲线程
                    {
                        //是否达到最大客户端连接数
                        i=WORKER_ISSTATUS(WORKER_DETACHED);
                        if(i!=-1)//没有达到最大客户端数，增加一个空闲的业务线程
                            Worker_Add(i);
                    }
                    else//有空闲业务处理线程，分配任务
                    {
                        wctls[i].conn.cs=ss;
                        //告诉业务线程有任务
                        pthread_mutex_unlock(&wctls[i].opts.mutex);
                    }
                }
        }
    }
    DBGPRINT("<==Worker_ScheduleRun\n");
    return 0;
}

//停止调度过程
int Worker_ScheduleStop()
{
    DBGPRINT("==>Woker_ScheduleStop\n");
    SCHEDULESTATUS=STATUS_STOP;//给任务分配线程设置终止条件

    int i=0;
    Worker_Destroy();//销毁业务线程
    int  allfired=0;
    for(;!allfired;)//查询并等待业务线程终止
    {
        allfired=1;
        for(i=0;i<conf_para.MaxClient;i++)
        {
            int flags=wctls[i].opts.flags;
            //线程正在活动
            if(flags==WORKER_DETACHING||flags==WORKER_IDEL)
                allfired=0;
        }
    }

    pthread_mutex_destroy(&thread_init);//销毁互斥变量
    for(i=0;i<conf_para.MaxClient;i++)//销毁业务处理线程的互斥
        pthread_mutex_destroy(&wctls[i].opts.mutex);
    free(wctls);//销毁业务数据

    DBGPRINT("<==Worker_ScheduleStop\n");
    return 0;
}
















