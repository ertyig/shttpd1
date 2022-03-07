#include <celib.h>
#include "shttpd.h"

struct woker_opts{
	pthread_t th;//线程id
	int flags;//线程状态
	pthread_mutex_t mutex;//线程任务互斥
	struct worker_ctl *work;//本线程的总控结构
};





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












struct woker_conn{
	#define K 1024
	char dreq[16*K];
	char dres[16*K];
	
	int cs;
	int to;
	
	struct conn_response con_res;
	struct conn_request con_req;
	
	struct worker_ctl *work;
};

struct conn_request{
	struct vec req;
	char *head;
	char *uri;
	char rpath[URI_MAX];
	int method;
	
	unsigned long major;
	unsigned long minor;
	
	struct headers ch;
	
	struct worker_conn *conn;
	int err;
};

struct conn_response{
	struct vec res;
	time_t birth_time;
	time_t expire_time;
	
	int status;
	int cl;
	
	int fd;
	struct stat fstate;
	
	struct worker_conn *conn;
};

struct worker_ctl{
	struct woker_opts opts;
	struct worker_conn conn;
};
