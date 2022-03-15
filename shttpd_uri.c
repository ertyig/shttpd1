////
//// Created by leechain on 2022/3/5.
////
//#include "shttpd.h"
//
////将以 %开头的字符串进行转换，如将%20 转换为 空格
////参数：源字符串，长度，目标字符串，长度
//#define HEXTOI(x) (isdigit(x)?(x)-'0':x-'W')
//
//static int uri_decode(char *src, int src_len, char *dst, int dst_len) {
//    int i, j, a, b;
//    for (i = j = 0; i < src_len && j < dst_len - 1; i++, j++) {
//        //需要判断%后的两个字符是否为十六进制
//        switch (src[i]) {
//            case '%':
//                if (isxdigit(((unsigned char *) src)[i + 1])
//                    && isxdigit(((unsigned char *) src)[i + 2])) {
//                    //把字符转换为小写字母，非字母字符不做处理
//                    a = tolower(((unsigned char *) src)[i + 1]);
//                    b = tolower(((unsigned char *) src)[i + 2]);
//                    //用 或 拼接在一起
//                    dst[j] = (HEXTOI(a) << 4) | HEXTOI(b);
//                    i += 2;
//                } else {
//                    dst[j] = '%';
//                }
//                break;
//            default://没有%符号
//                dst[j] = src[i];
//                break;
//        }
//    }
//    dst[j] = '\0';//添加结束符
//    return j;
//}
//
////将目录中的双点 .. 进行转换，即进入当前目录的父目录
//static void remove_double_dots(char *s) {
//    char *p = s;
//    while (*s != '\0') {
//        *p++ = *s++;
//        if (s[-1] == '/' || s[-1] == '\\') {
//            while (*s == '.' || *s == '/' || *s == '\\') {
//                s++;
//            }
//        }
//    }
//    *p = '\0';//末尾添加结束符
//}
//
//
////完成两种uri解析
//void uri_parse(char *src, int len) {
//    uri_decode(src, len - 1, src, len);
//    remove_double_dots(src);
//}




//start from the very beginning,and to create greatness
//@author: Chuangwei Lin
//@E-mail：979951191@qq.com
//@brief： URI分析
#include "shttpd.h"
/******************************************************
函数名：uri_decode(char *src, int src_len, char *dst, int dst_len)
参数：源字符串，长度，目的字符串，长度
功能：将以%开头的字符进行转换（如果以%开头的字符，则将其后面的两个字符拼接后转换成一个字符）
*******************************************************/
static int uri_decode(char *src, int src_len, char *dst, int dst_len)
{

    //#include<ctype.h>
    //定义函数:int isdigit(char c)
    //函数说明:检查参数c是否为阿拉伯数字0到9。
    //返回值:若参数c为阿拉伯数字，则返回TRUE，否则返回NULL(0)。
#define    HEXTOI(x) (isdigit(x) ? x - '0' : x - 'W')
    int    i, j, a, b;
    for (i = j = 0; i < src_len && j < dst_len - 1; i++, j++)
    {
        switch (src[i])
        {
            case '%'://将%后面两个字符拼接成一个
                if (isxdigit(((unsigned char *) src)[i + 1]) && isxdigit(((unsigned char *) src)[i + 2]))
                { //把字符转换成小写字母,非字母字符不做出处理
                    a = tolower(((unsigned char *)src)[i + 1]);
                    b = tolower(((unsigned char *)src)[i + 2]);
                    dst[j] = (HEXTOI(a) << 4) | HEXTOI(b);//用或实现拼接
                    i += 2;
                }
                else
                {
                    dst[j] = '%';
                }
                break;
            default:
                dst[j] = src[i];
                break;
        }
    }

    dst[j] = '\0';    //结束符
    return (j);
}
/******************************************************
函数名：remove_double_dots(char *s)
参数：源字符串
功能：对目录中的双点".."进行转换，即进入当前目录的父目录
*******************************************************/
static void remove_double_dots(char *s)
{
    char* p = s;
    while (*s != '\0')
    {
        *p++ = *s++;
        if (s[-1] == '/' || s[-1] == '\\')
        {
            while (*s == '.' || *s == '/' || *s == '\\')
            {
                s++;
            }
        }
    }
    *p = '\0';
}
/******************************************************
函数名：uri_parse(char *src, int len)
参数：源字符串及其长度
功能：完成两种转换
*******************************************************/
void uri_parse(char *src, int len)
{
    uri_decode(src, len -1, src, len);
    remove_double_dots(src);
}