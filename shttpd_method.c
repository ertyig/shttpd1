////
//// Created by leechain on 2022/3/5.
////
////服务器请求方法解析
//
//#include "shttpd.h"
//
//
//static int Method_DoGet(struct worker_ctl *wctl);
//static int Method_DoPut(struct worker_ctl *wctl);
//static int Method_DoPost(struct worker_ctl *wctl);
//static int Method_DoHead(struct worker_ctl *wctl);
//static int Method_DoList(struct worker_ctl *wctl);
//struct mine_type* Mine_Type(char *uri,int len,struct worker_ctl *wctl);
//
//
////方法的总函数，匹配方法
//void Method_Do(struct worker_ctl *wctl) {
//    DBGPRINT("==>Mehod_Do\n");
////    if(0)
////        Method_DoCGI(wctl);
//    //识别请求方法
//    switch (wctl->conn.con_req.method) {
//        case METHOD_GET:
//            Method_DoGet(wctl);
//            break;
//        case METHOD_PUT:
//            Method_DoPut(wctl);
//            break;
//        case METHOD_POST:
//            Method_DoPost(wctl);
//            break;
//        case METHOD_HEAD:
//            Method_DoHead(wctl);
//            break;
//        default:
//            Method_DoList(wctl);
//    }
//    DBGPRINT("<==Method_Do\n");
//}
//
//
//
//
//
///*   Method_DoGet()函数得到的响应的头部信息
//[HTTP/1.1 200 OK
//Date: Thu, 11 Dec 2008 11:25:33 GMT
//Last-Modified: Wed, 12 Nov 2008 09:00:01 GMT
//Etag: "491a2a91.2afe"
//Content-Type: text/plain
//Content-Length: 11006
//Accept-Ranges: bytes
//]
//*/
//
//
////只实现了get方法和head方法的解析
//static int Method_DoGet(struct worker_ctl *wctl) {
//    DBGPRINT("==>Method_DoGet\n");
//    struct conn_response *res = &wctl->conn.con_res;
//    struct conn_request *req = &wctl->conn.con_req;
//
//    char path[URI_MAX];
//    memset(path, 0, URI_MAX);
//    size_t n;
//    unsigned long r1, r2;
//    //时间格式
//    char *fmt = "%a, %d %b %Y %H:%M:%s GMT";
//
//    //需要确定的参数
//    size_t status = 200; //状态值，已确定
//    char *msg = "OK"; //状态信息，已确定
//    char date[64] = ""; //时间
//    char lm[64] = ""; //请求文件最后修改时间
//    char etag[64] = ""; //etag信息
//    big_int_t cl; //内容长度
//    char range[64] = ""; //范围
//    struct mine_type *mine = NULL;//mine类型
//
//
//    //获得构建头部需要的数据
//    //当前时间
//    time_t t = time(NULL);
//    //根据fmt指向字符串的命令将localtime(&t)中的时间信息储存在date中
//    (void) strftime(date, sizeof(date), fmt, localtime(&t));
//
//    //最后修改时间
//    (void) strftime(lm, sizeof(lm), fmt, localtime(&res->fstate.st_mtime));
//
//    //etag
//    (void) sprintf(etag, sizeof(etag), "%lx.%lx", (unsigned long) res->fstate.st_mtime,
//                   (unsigned long) res->fstate.st_size);
//
//    //发送的mine类型
//    mine = Mine_Type(req->uri, strlen(req->uri), wctl);
//
//    //内容长度
//    cl = (big_int_t) res->fstate.st_size;
//
//    //范围
//    memset(range, 0, sizeof(range));
//    n = -1;
//    //取出请求范围
//    if (req->ch.range.v_vec.len > 0) {
//        printf("request range:%d\n", req->ch.range.v_vec.len);
//        //从ptr里读进数据，依照第二个参数的格式将数据写入到后面的参数里
//        n = sscanf(req->ch.range.v_vec.ptr, "bytes=%lu-%lu", &r1, &r2);
//    }
//    printf("n:%d\n", n);
//    if (n > 0) {
//        status = 206;
//        lseek(res->fd, r1, SEEK_SET);
//        cl = n == 2 ? r2 - r1 + 1 : cl - r1;
//        (void) snprintf(range, sizeof(range),
//                        "Content-Range:bytes %lu-%lu/%lu\r\n",
//                        r1,
//                        r1 + cl - 1,
//                        (unsigned long) res->fstate.st_size);
//        msg = "Partial Content";
//    }
//
//    //构建输出的头部
//    memset(res->res.ptr, 0, sizeof(wctl->conn.dres));
//    snprintf(
//            res->res.ptr,
//            sizeof(wctl->conn.dres),
//            "HTTP/1.1 %d %s\r\n"
//            "Date: %s\r\n"
//            "Last-Modified: %s\r\n"
//            "Etag: \"%s\"\r\n"
//            "Content-Type: %.*s\r\n"
//            "Content-Length: %lu\r\n"
//            //"Connection:close\r\n"
//            "Accept_Ranges: bytes\r\n"
//            "%s\r\n",
//            status,
//            msg,
//            date,
//            lm,
//            etag,
//            mine->mime_type,
//            cl,
//            range
//    );
//
//    res->cl = cl;
//    res->status = status;
//    printf("content length:%d, status:%d\n", res->cl, res->status);
//    DBGPRINT("<==Method_DoGet\n");
//    return 0;
//}
//
//
//static int Method_DoHead(struct worker_ctl *wctl) {
//    Method_DoGet(wctl);
//    close(wctl->conn.con_res.fd);
//    wctl->conn.con_res.fd = -1;
//    return 0;
//}
//
//static int Method_DoPost(struct worker_ctl *wctl) {
//    return 0;
//}
//
//static int Method_DoPut(struct worker_ctl *wctl) {
//    return 0;
//}
//
//static int Method_DoList(struct worker_ctl *wctl) {
//    return 0;
//}
//



//@brief： 服务器SHTTPD请求方法解析
#include "shttpd.h"
/******************************************************
函数名： Method_DoGet(struct worker_ctl *wctl)
参数：
功能：GET方法
*******************************************************/
static int Method_DoGet(struct worker_ctl *wctl)
{
    DBGPRINT("LCW==>Method_DoGet\n");
    struct conn_response *res = &wctl->conn.con_res;
    struct conn_request *req = &wctl->conn.con_req;
    char path[URI_MAX];
    memset(path, 0, URI_MAX);
    size_t    n;
    unsigned long r1, r2;
    char *fmt = "%a, %d %b %Y %H:%M:%S GMT";//时间格式
    //需要确定的参数
    int status = 200;//状态值,已确定
    char *msg = "OK";    //状态信息,已确定
    char date[64] = "";//时间
    char lm[64] = "";    //请求文件最后修改信息
    char etag[64] = "";//etag信息
    big_int_t cl;        //内容长度
    char range[64] = "";//范围
    struct mine_type *mine = NULL;
    time_t t = time(NULL);//取得当前时间
    //根据fmt指向字符串的命令将localtime(&t)中的时间信息储存在date中
    (void)strftime(date, sizeof(date),fmt,localtime(&t));
    //最后修改时间
    (void) strftime(lm, sizeof(lm), fmt,localtime(&res->fstate.st_mtime));
    //ETAG 将可变个参数(...)按照"%lx.%lx"格式化成字符串，然后将其复制到etag中
    (void) snprintf(etag, sizeof(etag), "%lx.%lx",(unsigned long)res->fstate.st_mtime,(unsigned long)res->fstate.st_size);
    //发送的MIME类型
    mine = Mine_Type(req->uri, strlen(req->uri), wctl);
    //内容长度
    cl = (big_int_t) res->fstate.st_size;
    //范围range
    memset(range, 0, sizeof(range));
    n = -1;
    if (req->ch.range.v_vec.len > 0 )//取出请求范围
    {
        printf("request range:%d\n",req->ch.range.v_vec.len);
        //从ptr里读进数据，依照第二个参数的格式将数据写入到后面的参数里
        n = sscanf(req->ch.range.v_vec.ptr,"bytes=%lu-%lu",&r1, &r2);
    }

    if(n > 0)
    {
        status = 206;
        lseek(res->fd, r1, SEEK_SET);
        //n==2取前一个
        cl = n == 2 ? r2 - r1 + 1: cl - r1;
        (void) snprintf(range, sizeof(range),"Content-Range: bytes %lu-%lu/%lu\r\n",r1, r1 + cl - 1, (unsigned long) res->fstate.st_size);
        msg = "Partial Content";
    }
    //构建输出的头部
    memset(res->res.ptr, 0, sizeof(wctl->conn.dres));
    snprintf(
            res->res.ptr,
            sizeof(wctl->conn.dres),
            "HTTP/1.1 %d %s\r\n"
            "Date: %s\r\n"
            "Last-Modified: %s\r\n"
            "Etag: \"%s\"\r\n"
            "Content-Type: %s\r\n"
            "Content-Length: %lu\r\n"
            //"Connection:close\r\n"
            "Accept_Ranges: bytes\r\n"
            "%s\r\n",
            status,
            msg,
            date,
            lm,
            etag,
            mine->mime_type,
            cl,
            range
    );
    res->cl = cl;
    res->status = status;
    printf("content length:%d, status:%d\n",res->cl, res->status);
    DBGPRINT("LCW<==Method_DoGet\n");
    return 0;
}
/******************************************************
未实现的方法
*******************************************************/
static int Method_DoPost(struct worker_ctl *wctl)
{
    return 0;
}
static int Method_DoHead(struct worker_ctl *wctl)
{
    Method_DoGet(wctl);
    close(wctl->conn.con_res.fd);
    wctl->conn.con_res.fd = -1;
    return 0;
}
static int Method_DoPut(struct worker_ctl *wctl)
{
    return 0;
}
static int Method_DoDelete(struct worker_ctl *wctl)
{
    return 0;
}
static int Method_DoCGI(struct worker_ctl *wctl)
{
    return 0;
}
static int Method_DoList(struct worker_ctl *wctl)
{
    return 0;
}
/******************************************************
函数名：Method_Do(struct worker_ctl *wctl)
参数：业务和线程状态结构
功能：匹配方法
*******************************************************/
void Method_Do(struct worker_ctl *wctl)
{
    DBGPRINT("LCW==>Method_Do\n");
    if(0)//????什么意思 不执行？
        Method_DoCGI(wctl);
    switch(wctl->conn.con_req.method)//匹配请求类型
    {
        case METHOD_PUT://PUT方法
            Method_DoPut(wctl);
            break;
        case METHOD_DELETE://DELETE方法
            Method_DoDelete(wctl);
            break;
        case METHOD_GET://GET方法(这里只实现GET方法)
            Method_DoGet(wctl);
            break;
        case METHOD_POST://POST方法
            Method_DoPost(wctl);
            break;
        case METHOD_HEAD://HEAD方法
            Method_DoHead(wctl);
            break;
        default:
            Method_DoList(wctl);
    }

    DBGPRINT("LCW<==Method_Do\n");
}