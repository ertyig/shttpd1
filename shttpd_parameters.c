#include "shttpd.h"







//展示命令行输入方式
void display_usage(void)
{
	printf("-----------------------------------\n");
	printf("sHTTPD -l number -m number -o path -c path -d filename -t seconds -o filename\n");
	printf("sHTTPD --ListenPort number\n");
	printf("       --MaxClient number\n");
	printf("       --DocumentRoot) path\n");
	printf("       --DefaultFile) filename\n");
	printf("       --CGIRoot path \n");
	printf("       --DefaultFile filename\n");
	printf("       --TimeOut seconds\n");
	printf("       --ConfigFile filename\n");
}

//打印输入参数
static void display_para()
{
	printf("sHTTPD ListenPort: %d\n",conf_para.ListenPort);
	printf("       MaxClient: %d\n",conf_para.MaxClient);
	printf("       DocumentRoot: %s\n",conf_para.DocumentRoot);
	printf("       DefaultFile: %s\n",conf_para.DefaultFile);
	printf("       CGIRoot: %s\n",conf_para.CGIRoot);
	printf("       DefaultFile: %s\n",conf_para.DefaultFile);
	printf("       TImeOut: %d\n",conf_para.TimeOut);
	printf("       ConfigFile: %s\n",conf_para.ConfigFile);
}


//读取配置文件中的一行
static int conf_readline(int fd,char *buff,int len)
{
    int i=0;
	int n=-1;
	int begin=0;
	
	memset(buff,0,len);
	for(i=0;i<len;begin?i++:i)
	{
		n=read(fd,buff+i,1);
		
		if(n==0)
		{
			*(buff+i)='\0';
			break;
		}
		else if(*(buff+i)=='\r'||*(buff+i)=='\n')
		{
			if(begin)
			{
				*(buff+i)='\0';
				break;
			}
		}
		else
			begin=1;
	}
	return i;
}


//保存输入参数
static char* l_opt_arg;

//命令行参数解析
static int Para_CmdParse(int argc,char *argv[])
{
	int c;
	int len;
	int value;
	
	while((c=getopt_long(argc,argv,shortopts,longopts,NULL))!=-1)
	{
		switch(c)
		{
			case 'c':
				l_opt_arg=optarg;
				if(l_opt_arg&&l_opt_arg[0]!=':')
				{
					len=strlen(l_opt_arg);
					memcpy(conf_para.CGIRoot,l_opt_arg,len+1);
				}
				break;
				
			case 'd':
				l_opt_arg=optarg;
				if(l_opt_arg&&l_opt_arg[0]!=':')
				{
					len=strlen(l_opt_arg);
					memcpy(conf_para.DefaultFile,l_opt_arg,len+1);
				}
				break;
				
			case 'f':
				l_opt_arg=optarg;
				if(l_opt_arg&&l_opt_arg[0]!=':')
				{
					len=strlen(l_opt_arg);
					memcpy(conf_para.ConfigFile,l_opt_arg,len+1);
				}
				break;
				
			case 'o':
				l_opt_arg=optarg;
				if(l_opt_arg&&l_opt_arg[0]!=':')
				{
					len=strlen(l_opt_arg);
					memcpy(conf_para.DocumentRoot,l_opt_arg,len+1);
				}
				break;
				
			case 'l':
				l_opt_arg=optarg;
				if(l_opt_arg&&l_opt_arg[0]!=':')
				{
					len=strlen(l_opt_arg);
					value=strtol(l_opt_arg,NULL,10);
					if(value!=LONG_MAX&&value!=LONG_MIN)
						conf_para.ListenPort=value;
				}
				break;
				
			case 'm':
				l_opt_arg=optarg;
				if(l_opt_arg&&l_opt_arg[0]!=':')
				{
					len=strlen(l_opt_arg);
					value=strtol(l_opt_arg,NULL,10);
					if(value!=LONG_MAX&&value!=LONG_MIN)
						conf_para.MaxClient=value;
				}
				break;
				
			case 't':
				l_opt_arg=optarg;
				if(l_opt_arg&&l_opt_arg[0]!=':')
				{
					len=strlen(l_opt_arg);
					value=strtol(l_opt_arg,NULL,10);
					if(value!=LONG_MAX&&value!=LONG_MIN)
						conf_para.TimeOut=value;
				}
				break;
				
			case '?':
				printf("Invalid parameter\n");
			
			case 'h':
				display_usage();
				break;
		}
	}
	
	return 0;
}


//配置文件参数解析
void Para_FileParse(char *file)
{
	#define LINELENGTH 256
	char line[LINELENGTH];
	char *name=NULL;
	char *value=NULL;
	int fd=-1;
	int n=0;
	
	fd=open(file,O_RDONLY);
	if(fd==-1)
		goto EXITPara_FileParse;
	
	while((n=conf_readline(fd,line,LINELENGTH))!=0)
	{
		char *pos=line;
		//key
		while(isspace(*pos))
			pos++;
		if(*pos=='#')
			continue;			
		name=pos;
		while(!isspace(*pos)&&*pos!='=')
			pos++;
		*pos='\0';
		
		//value
		while(isspace(*pos))
			pos++;
		value=pos;
		while(!isspace(*pos)&&*pos!='\r'&&*pos!='\n')
			pos++;
		*pos='\0';
		
		int ivalue;//int
		
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
			ivalue=strtol(value,NULL,10);
			conf_para.ListenPort=ivalue;
		}
		else if(strncmp("MaxClient",name,9))
		{
			ivalue=strtol(value,NULL,10);
			conf_para.MaxClient=ivalue;
		}
		else if(strncmp("TimeOut",name,7))
		{
			ivalue=strtol(value,NULL,10);
			conf_para.TimeOut=ivalue;
		}
	}
	close(fd);

EXITPara_FileParse:
	return;
}

//配置参数初始化
void Para_Init(int argc,char *argv[])
{
	Para_CmdParse(argc,argv);
	
	if(strlen(conf_para.ConfigFile))
		Para_FileParse(conf_para.ConfigFile);
	
	display_para();
	
	return;
}





