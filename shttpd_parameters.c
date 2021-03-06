//#include "shttpd.h"
//
//
//void display_usage(void);
//
//static void display_para();
//
//static int Para_CmdParse(int argc, char *argv[]);
//
//void Para_FileParse(char *file);
//
//
////配置参数初始化
//void Para_Init(int argc, char *argv[]) {
//    //解析命令行输入参数
//    Para_CmdParse(argc, argv);
//    //解析配置文件配置参数
//    if (strlen(conf_para.ConfigFile))
//        Para_FileParse(conf_para.ConfigFile);
//    //打印配置的参数
//    display_para();
//
//    return;
//}
//
//
////展示命令行输入方式
//void display_usage(void) {
//    printf("-----------------------------------\n");
//    printf("sHTTPD -l number -m number -o path -c path -d filename -t seconds -o filename\n");
//    printf("sHTTPD --ListenPort number\n");
//    printf("       --MaxClient number\n");
//    printf("       --DocumentRoot) path\n");
//    printf("       --DefaultFile) filename\n");
//    printf("       --CGIRoot path \n");
//    printf("       --DefaultFile filename\n");
//    printf("       --TimeOut seconds\n");
//    printf("       --ConfigFile filename\n");
//}
//
////打印输入参数
//static void display_para() {
//    printf("sHTTPD ListenPort: %d\n", conf_para.ListenPort);
//    printf("       MaxClient: %d\n", conf_para.MaxClient);
//    printf("       DocumentRoot: %s\n", conf_para.DocumentRoot);
//    printf("       DefaultFile: %s\n", conf_para.DefaultFile);
//    printf("       CGIRoot: %s\n", conf_para.CGIRoot);
//    printf("       DefaultFile: %s\n", conf_para.DefaultFile);
//    printf("       TImeOut: %d\n", conf_para.TimeOut);
//    printf("       ConfigFile: %s\n", conf_para.ConfigFile);
//}
//
//
////读取配置文件中的一行
//static int conf_readline(int fd, char *buff, int len) {
//    int i = 0;
//    int n = -1;
//    int begin = 0;
//
//    memset(buff, 0, len);
//    for (i = 0; i < len; begin ? i++ : i) {
//        n = read(fd, buff + i, 1);
//
//        if (n == 0) {
//            *(buff + i) = '\0';
//            break;
//        } else if (*(buff + i) == '\r' || *(buff + i) == '\n') {
//            if (begin) {
//                *(buff + i) = '\0';
//                break;
//            }
//        } else {
//            begin = 1;
//        }
//
//    }
//    return i;
//}
//
//
////保存输入参数
//static char *l_opt_arg;
//
////命令行参数解析
//static int Para_CmdParse(int argc, char *argv[]) {
//    int c;
//    int len;
//    int value;
//
//    while ((c = getopt_long(argc, argv, shortopts, longopts, NULL)) != -1) {
//        switch (c) {
//            case 'c':
//                l_opt_arg = optarg;
//                if (l_opt_arg && l_opt_arg[0] != ':') {
//                    len = strlen(l_opt_arg);
//                    memcpy(conf_para.CGIRoot, l_opt_arg, len + 1);
//                }
//                break;
//
//            case 'd':
//                l_opt_arg = optarg;
//                if (l_opt_arg && l_opt_arg[0] != ':') {
//                    len = strlen(l_opt_arg);
//                    memcpy(conf_para.DefaultFile, l_opt_arg, len + 1);
//                }
//                break;
//
//            case 'f':
//                l_opt_arg = optarg;
//                if (l_opt_arg && l_opt_arg[0] != ':') {
//                    len = strlen(l_opt_arg);
//                    memcpy(conf_para.ConfigFile, l_opt_arg, len + 1);
//                }
//                break;
//
//            case 'o':
//                l_opt_arg = optarg;
//                if (l_opt_arg && l_opt_arg[0] != ':') {
//                    len = strlen(l_opt_arg);
//                    memcpy(conf_para.DocumentRoot, l_opt_arg, len + 1);
//                }
//                break;
//
//            case 'l':
//                l_opt_arg = optarg;
//                if (l_opt_arg && l_opt_arg[0] != ':') {
//                    len = strlen(l_opt_arg);
//                    value = strtol(l_opt_arg, NULL, 10);
//                    if (value != LONG_MAX && value != LONG_MIN)
//                        conf_para.ListenPort = value;
//                }
//                break;
//
//            case 'm':
//                l_opt_arg = optarg;
//                if (l_opt_arg && l_opt_arg[0] != ':') {
//                    len = strlen(l_opt_arg);
//                    value = strtol(l_opt_arg, NULL, 10);
//                    if (value != LONG_MAX && value != LONG_MIN)
//                        conf_para.MaxClient = value;
//                }
//                break;
//
//            case 't':
//                l_opt_arg = optarg;
//                if (l_opt_arg && l_opt_arg[0] != ':') {
//                    len = strlen(l_opt_arg);
//                    value = strtol(l_opt_arg, NULL, 10);
//                    if (value != LONG_MAX && value != LONG_MIN)
//                        conf_para.TimeOut = value;
//                }
//                break;
//
//            case '?':
//                printf("Invalid parameter\n");
//
//            case 'h':
//                display_usage();
//                break;
//        }
//    }
//
//    return 0;
//}
//
//
////配置文件参数解析
//void Para_FileParse(char *file) {
//#define LINELENGTH 256
//    char line[LINELENGTH];
//    char *name = NULL;
//    char *value = NULL;
//    int fd = -1;
//    int n = 0;
//
//    fd = open(file, O_RDONLY);
//    if (fd == -1)
//        goto EXITPara_FileParse;
//
//    while ((n = conf_readline(fd, line, LINELENGTH)) != 0) {
//        char *pos = line;
//        //key
//        while (isspace(*pos))
//            pos++;
//        if (*pos == '#')
//            continue;
//        name = pos;
//        while (!isspace(*pos) && *pos != '=')
//            pos++;
//        *pos = '\0';
//
//        //value
//        while (isspace(*pos))
//            pos++;
//        value = pos;
//        while (!isspace(*pos) && *pos != '\r' && *pos != '\n')
//            pos++;
//        *pos = '\0';
//
//        int ivalue;//int
//
//        if (strncmp("CGIRoot", name, 7)) {
//            memcpy(conf_para.CGIRoot, value, strlen(value) + 1);
//        } else if (strncmp("DefaultFile", name, 11)) {
//            memcpy(conf_para.DefaultFile, value, strlen(value) + 1);
//        } else if (strncmp("DocumentRoot", name, 12)) {
//            memcpy(conf_para.DocumentRoot, value, strlen(value) + 1);
//        } else if (strncmp("ListenPort", name, 10)) {
//            ivalue = strtol(value, NULL, 10);
//            conf_para.ListenPort = ivalue;
//        } else if (strncmp("MaxClient", name, 9)) {
//            ivalue = strtol(value, NULL, 10);
//            conf_para.MaxClient = ivalue;
//        } else if (strncmp("TimeOut", name, 7)) {
//            ivalue = strtol(value, NULL, 10);
//            conf_para.TimeOut = ivalue;
//        }
//    }
//    close(fd);
//
//    EXITPara_FileParse:
//    return;
//}
//




#include "shttpd.h"
//初始化时服务器的默认配置
extern struct conf_opts conf_para;

//短选项的配置为c:d:f:h:o:l:m:t:
static char* shortopts="c:d:f:h:o:l:m:t:";
//长选项的配置
//option是getop_long的一个结构体参数p531
static struct option longopts[]=
        {
                {"CGIRoot",required_argument,NULL,'c'},
                {"ConfigFile",required_argument,NULL,'f'},
                {"DefaultFile",required_argument,NULL,'d'},
                {"DocumentRoot",required_argument,NULL,'o'},
                {"ListenPort",required_argument,NULL,'l'},
                {"MaxClient",required_argument,NULL,'m'},
                {"TimeOut",required_argument,NULL,'t'},
                {"Help",no_argument,NULL,'h'},
                {0,0,0,0},
        };

/******************************************************
函数名：display_usage(void)
参数：无
功能：显示参数输入方法
*******************************************************/
void display_usage(void)
{
    printf("*******************Chuangwei Lin*******************\n");
    printf("sHTTPD -l number -m number -o path -c path -d filename -t seconds -o filename\n");
    printf("sHTTPD --ListenPort number\n");
    printf(" --MaxClient number\n");
    printf(" --DocumentRoot) path\n");
    printf(" --DefaultFile) filename\n");
    printf(" --CGIRoot path \n");
    printf(" --DefaultFile filename\n");
    printf(" --TimeOut seconds\n");
    printf(" --ConfigFile filename\n");
}
/******************************************************
函数名：conf_readline(int fd, char *buff, int len)
参数：文件描述符，缓冲区，长度
功能：读取配置文件的一行
*******************************************************/
static int conf_readline(int fd, char *buff, int len)
{
    int n = -1;
    int i = 0;
    int begin = 0;
    memset(buff, 0, len);//清缓冲区
    for(i =0; i<len;begin?i++:i)//当开头部分不为'\r'或者'\n'时i计数
    { //begin真则i++
        n = read(fd, buff+i, 1);//读一个字符
        if(n == 0)//文件末尾
        {
            *(buff+i) = '\0';
            break;
        }
        else if(*(buff+i) == '\r' ||*(buff+i) == '\n')
        {//是回车换行
            if(begin)
            {//为一行
                *(buff+i) = '\0';
                break;
            }
        }
        else
        {
            begin = 1;
        }
    }
    return i;
}

static char* l_opt_arg;//存输入参数
/******************************************************
函数名：Para_CmdParse(int argc,char* argv[])
参数：argc:参数个数 ，argv:参数的字符串数组，两个参数一般是从main()函数的输入参数中直接传来
功能：命令行解析函数，利用getopt_long函数实现
*******************************************************/
static int Para_CmdParse(int argc,char* argv[])
{
    int c;
    int len;
    int value;
    //遍历输入参数，设置配置参数
    while((c=getopt_long(argc,argv,shortopts,longopts,NULL))!=-1)
    {
        switch(c)
        { //getopt_long()如果有输入参数，则输入参数为optarg
            case 'c'://CGI跟路径
                l_opt_arg = optarg;
                if (l_opt_arg && l_opt_arg[0] != ':')
                {
                    len = strlen(l_opt_arg);
                    memcpy(conf_para.CGIRoot,l_opt_arg,len+1);//更新
                }
                break;
            case 'd'://默认文件名称
                l_opt_arg = optarg;
                if (l_opt_arg && l_opt_arg[0] != ':')
                {
                    len = strlen(l_opt_arg);
                    memcpy(conf_para.DefaultFile,l_opt_arg,len+1);
                }
                break;
            case 'f'://配置文件名称和路径
                l_opt_arg = optarg;
                if (l_opt_arg && l_opt_arg[0] != ':')
                {
                    len = strlen(l_opt_arg);
                    memcpy(conf_para.ConfigFile,l_opt_arg,len+1);
                }
                break;
            case 'o'://根文件路径
                l_opt_arg = optarg;
                if (l_opt_arg && l_opt_arg[0] != ':')
                {
                    len = strlen(l_opt_arg);
                    memcpy(conf_para.DocumentRoot,l_opt_arg,len+1);
                }
                break;
            case 'l'://侦听端口
                l_opt_arg = optarg;
                if (l_opt_arg && l_opt_arg[0] != ':')
                {
                    len = strlen(l_opt_arg);
                    value = strtol(l_opt_arg,NULL,10);//转化字符串为整形
                    if (value != LONG_MAX && value != LONG_MIN)
                    {
                        conf_para.ListenPort = value;//更新
                    }
                }
                break;
            case 'm'://最大客户端数量
                l_opt_arg = optarg;
                if (l_opt_arg && l_opt_arg[0] != ':')
                {
                    len = strlen(l_opt_arg);
                    value = strtol(l_opt_arg,NULL,10);//转化字符串为整形
                    if (value != LONG_MAX && value != LONG_MIN)
                    {
                        conf_para.MaxClient = value;//更新
                    }
                }
                break;
            case 't'://超时时间
                l_opt_arg = optarg;
                if (l_opt_arg && l_opt_arg[0] != ':')
                {
                    len = strlen(l_opt_arg);
                    value = strtol(l_opt_arg,NULL,10);//转化字符串为整形
                    if (value != LONG_MAX && value != LONG_MIN)
                    {
                        conf_para.TimeOut = value;//更新
                    }
                }
                break;
            case '?':
                printf("Invalid para \n");
            case 'h':
                display_usage();
                break;
        }
    }
    return 0;
}
/******************************************************
函数名：Para_FileParse(char* file)
参数：文件
功能：文件配置解析函数
*******************************************************/
void Para_FileParse(char* file)
{
#define LINELENGTH 256
    char line[LINELENGTH];//读取缓冲区
    char *name = NULL,*value = NULL;//用于获取关键字和值
    int fd = -1;//文件描述符
    int n = 0;
    fd = open(file,O_RDONLY);//只读方式打开配置文件
    if (-1 == fd)//错误检查
    {
        goto EXITPara_FileParse;//退出
    }
    //命令格式如下
    //[#注释|[空格]关键字[空格]=[空格]value]
    //
    while((n = conf_readline(fd,line,LINELENGTH))!= 0)//每次读取一行
    {
        char *pos = line;//文件位置指针
        while(isspace(*pos))
        {
            pos++;//跳过一行开头部分的空格
        }
        if(*pos == '#')//如果是注释
        {
            continue;//那就读取下一行
        }
        name = pos;//此时的位置就是关键字的开头
        while(!isspace(*pos) && *pos != '=')//不是空格也不是’=‘，则继续读直到读完关键字
        {
            pos++;
        }
        *pos = '\0';//得到关键字
        while(isspace(*pos))//再次跳过值前面的空格
        {
            pos++;
        }
        value = pos;
        while(!isspace(*pos) && *pos != '\r' && *pos != '\n')//读到结束
        {
            pos++;
        }
        pos = '\0';//得到值
        //根据关键字，将值赋给配置文件的结构
        int ivalue;
        if(strncmp("CGIRoot",name,7))
        {
            memcpy(conf_para.CGIRoot,value,strlen(value)+1);
        }
        else if(strncmp("DefaultFile",name,11))
        {
            memcpy(conf_para.DefaultFile,value,strlen(value)+1);
        }
        else if(strncmp("DocumentRoot",name,12))
        {
            memcpy(conf_para.DocumentRoot,value,strlen(value)+1);
        }
        else if(strncmp("ListenPort",name,10))
        {
            ivalue = strtol(value,NULL,10);//转化字符串为整形
            conf_para.ListenPort = ivalue;
        }
        else if(strncmp("MaxClient",name,9))
        {
            ivalue = strtol(value,NULL,10);//转化字符串为整形
            conf_para.MaxClient = ivalue;
        }
        else if(strncmp("TimeOut",name,7))
        {
            ivalue = strtol(value,NULL,10);//转化字符串为整形
            conf_para.TimeOut = ivalue;
        }

    }
    close(fd);//关闭文件
    EXITPara_FileParse:
    return ;
}
/******************************************************
函数名：display_para()
参数：无
功能：显示配置的参数
*******************************************************/
static void display_para()
{
    printf("*******************Chuangwei Lin*******************\n");
    printf("sHTTPD ListenPort: %d\n",conf_para.ListenPort);
    printf(" MaxClient: %d\n", conf_para.MaxClient);
    printf(" DocumentRoot: %s\n",conf_para.DocumentRoot);
    printf(" DefaultFile:%s\n",conf_para.DefaultFile);
    printf(" CGIRoot:%s \n",conf_para.CGIRoot);
    printf(" DefaultFile:%s\n",conf_para.DefaultFile);
    printf(" TimeOut:%d\n",conf_para.TimeOut);
    printf(" ConfigFile:%s\n",conf_para.ConfigFile);
}
/******************************************************
函数名：Para_Init(int argc, char *argv[])
参数：参数个数，和参数字符串
功能：初始化配置
*******************************************************/
void Para_Init(int argc, char *argv[])
{
    //解析命令行输入参数
    Para_CmdParse(argc, argv);
    //解析配置文件配置参数
    if(strlen(conf_para.ConfigFile))
    {
        Para_FileParse(conf_para.ConfigFile);
    }
    display_para();
    return ;//返回配置参数
}
