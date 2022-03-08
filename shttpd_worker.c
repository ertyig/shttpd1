#include "shttpd.h"
static struct worker_ctl *wctls=NULL;//线程选项
static int workersnum=0;//工作线程的数量
pthread_mutex_t thread_init=PTHREAD_MUTEX_INITIALIZER;//初始化互斥锁




//增加线程
//参数i是线程序号
static int Worker_Add(int i)
{
    DBGPRINT("==>Worker_Add\n");
    pthread_t th;
    int err=-1;
    if(wctls[i].opts.flags==WORKER_RUNNING)
            return 1;//如果线程已经在工作，则返回

    pthread_mutex_lock(&thread_init);
    wctls[i].opts.flags=WORKER_INITED;;//状态已经初始化
    //建立线程
    //worker为线程处理函数
    err= pthread_create(&th,NULL,worker,(void*)&wctls[i]);
    pthread_mutex_unlock(&thread_init);
    //更新线程选项
    wctls[i].opts.th=th;
    workersnum++;//工作线程数量增加

    DBGPRINT("<==Worker_Add\n");
    return 0;
}


//减少线程
//参数i是线程序号
static void Worker_Delete(int i)
{
    DBGPRINT("==>Worker_Delete\n");
    //线程状态改为正在卸载
    wctls[i].opts.flags=WORKER_DETACHING;
    DBGPRINT("<==Worker_Delete\n");
}

//销毁线程
static void Worker_Destory()
{
    DBGPRINT("==>Worker_Destory\n");
    int i=0;
    int clean=0;

    for(i=0;i<conf_para.MaxClient;i++)
    {
        DBGPRINT("thread %d, status %d\n",i,wctls[i].opts.flags);
        if(wctls[i].opts.flags!=WORKER_DETACHED)
            //如果线程状态不是 已卸载，就调用Delete函数
            Worker_Delete(i);//修改线程状态为WORKER_DETACHING
    }

    while(!clean)
    {
        clean=1;
        for(i=0;i<conf_para.MaxClient;i++)
        {
            DBGPRINT("thread %d, status %d\n",i,wctls[i].opts.flags);
            if(wctls[i].opts.flags==WORKER_RUNNING
            ||wctls[i].opts.flags==WORKER_DETACHING)
                clean=0;
        }
        if(!clean)
            sleep(1);
    }

    DBGPRINT("<==Worker_Destory\n");
}


//查找线程状态为当前状态的线程序号
static int WORKER_ISSTATUS(int status)
{
    int i=0;
    for(i=0;i<conf_para.MaxClient;i++)
    {
        if(wctls[i].opts.flags==status)
            return i;
    }
    return -1;
}


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
        wctls[i].conn.con_req.req.ptr=wctls[i].conn.dreq;
        wctls[i].conn.con_req.head=wctls[i].conn.dreq;
        wctls[i].conn.con_req.uri=wctls[i].conn.dreq;
        //con_res初始化
        wctls[i].conn.con_res.fd=-1;
        wctls[i].conn.con_res.res.ptr=wctls[i].conn.dres;
    }
    for(i=0;i<conf_para.InitClient;i++)
    {
        //增加规定个数的业务线程，初始化客户端数量
        Worker_Add(i);
    }
    DBGPRINT("<==Worker_Init\n");
}






/*主调度过程,
//初始化多个处理客户端请求的业务线程
*	当有客户端连接到来的时候
*	将客户端连接分配给空闲客户端
*	由客户端处理到来的请求
*/

//定义调度状态
#define STATUS_RUNNING 1
#define STATUS_STOP 0
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
    Worker_Destory();//销毁业务线程
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
















