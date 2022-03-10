//
// Created by leechain on 2022/3/5.
//
//服务器请求方法解析
#include "shttpd.h"



/*   Method_DoGet()函数得到的响应的头部信息
[HTTP/1.1 200 OK
Date: Thu, 11 Dec 2008 11:25:33 GMT
Last-Modified: Wed, 12 Nov 2008 09:00:01 GMT
Etag: "491a2a91.2afe"
Content-Type: text/plain
Content-Length: 11006
Accept-Ranges: bytes
]
*/


//只实现了get方法和head方法的解析
static int Method_DoGet(struct worker_ctl *wctl)
{
    DBFPRINT("==>Method_DoGet\n");
    struct conn_response *res=&wctl->conn.con_res;
    struct conn_request *req=&wctl->conn.con_req;

    char path[URI_MAX];
    memset(path,0,URI_MAX);
    size_t n;
    unsigned long r1,r2;
    //时间格式
    char *fmt="%a, %d %b %Y %H:%M:%s GMT";

    //需要确定的参数
    size_t status=200; //状态值，已确定
    char *msg="OK"; //状态信息，已确定
    char date[64]=""; //时间
    char lm[64]=""; //请求文件最后修改时间
    char etag[64]=""; //etag信息
    big_int_t cl; //内容长度
    char range[64]=""; //范围
    struct mine_type *mine=NULL;//mine类型

    //当前时间
    time_t t=time(NULL);
    //根据fmt指向字符串的命令将localtime(&t)中的时间信息储存在date中
    (void) strftime(date,sizeof(date),fmt, localtime(&t));

    //最后修改时间
    (void) strftime(lm,sizeof(lm),fmt, localtime(&res->fstate.st_mtime));

    //etag
    (void) sprintf(etag,sizeof(etag),"%lx.%lx",(unsigned long)res->fstate.st_mtime,
                   (unsigned long)res->fstate.st_size);

    //发送的mine类型
    mine=Mine_Type(req->uri,strlen(req->uri),wctl);

    //内容长度
    cl=(big_int_t)res->fstate.st_size;

    //范围
    memset(range,0,sizeof(range));
    n=-1;
    //取出请求范围
    if(req->ch.range.v_vec.len>0)
    {
        printf("request range:%d\n",req->ch.range.v_vec.len);
        //从ptr里读进数据，依照第二个参数的格式将数据写入到后面的参数里
        n= sscanf(req->ch.range.v_vec.ptr,"bytes=%lu-%lu",&r1,&r2);
    }
    printf("n:%d\n",n);
    if(n>0)
    {
        status=206;
        lseek(res->fd,r1,SEEK_SET);
        cl=n==2?r2-r1+1:cl-r1;
        (void) snprintf(range,sizeof(range),
                        "Content-Range:bytes %lu-%lu/%lu\r\n",
                        r1,
                        r1+cl-1,
                        (unsigned long) res->fstate.st_size);
        msg="Partial Content";
    }


}




static int Method_DoHead(struct worker_ctl *wctl)
{

}

static int Method_DoPost(struct worker_ctl *wctl)
{
    return 0;
}

static int Method_DoPut(struct worker_ctl *wctl)
{
    return 0;
}

static int Method_DoList(struct worker_ctl *wctl)
{
    return 0;
}

//方法的总函数，匹配方法
void Method_Do(struct worker_ctl *wctl)
{
    DBGPRINT("==>Mehod_Do\n");
//    if(0)
//        Method_DoCGI(wctl);
    //识别请求方法
    switch(wctl->conn.con_req.method)
    {
        case METHOD_GET:
            Method_DoGet(wctl);
            break;
        case METHOD_PUT:
            Method_DoPut(wctl);
            break;
        case METHOD_POST:
            Method_DoPost(wctl);
            break;
        case METHOD_HEAD:
            Method_DoHead(wctl);
            break;
        default:
            Method_DoList(wctl);
    }
    DBGPRINT("<==Method_Do\n");
}
