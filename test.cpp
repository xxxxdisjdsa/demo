#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define TT 0
char aa[20]=" ";
int pp=0;
# if TT
char  VN[5]={'E','e','T','t','F'}; //非终结符表
int    length_vn=5; //非终结符的个数
char  VT[10]={'*','l','m','+','-','(',')','i','n','#'}; //终结符表 l->/ m->% i->id n->num
int    length_vt=10; //终结符的个数
char  Fa[12][6]={"Te","+Te","-Te","NULL","Ft","*Ft","nFt","mFt","NULL","(E)","i","n"};
//产生式表:0:E->Te 1:e->+Te 2:e->-Te 3:e->空 
char  F[12][6]={"E->","e->","e->","e->","T->","t->","t->","t->","t->","F->","F->","F->"};
int    analysis_table[5][10]={-2,-2,-2,-2,-2,0,-1,0,0,-1,
             -2,-2,-2,1,2,-2,3,-2,-2,3,
             -2,-2,-2,-1,-1,4,-1,4,4,-1,
             5,6,7,8,8,-2,8,-2,-2,8,
             -1,-1,-1,-1,-1,9,-1,10,11,-1};
# else
char  VN[4]={'A','Z','B','Y'}; //非终结符表
int    length_vn=4; //非终结符的个数
char  VT[5]={'a','l','d','b','#'}; //终结符表
int    length_vt=5; //终结符的个数
char  Fa[6][6]={"aZ","ABl","NULL","dY","bY","NULL"};
char  F[6][6]={"A->","Z->","B->","Y->"};
int    analysis_table[4][5]={0,-2,-1,-2,-1,
             1,-2,2,-2,2,
             -2,-1,3,-2,-2,
             -2,5,-2,4,-2};
# endif
char stack[50];
int top=-1;
void initscanner() //程序初始化：输入并打开源程序文件
{	
    int i=0;
    FILE *fp;
    if((fp=fopen("a.txt","r"))==NULL) 
    {
       printf("Open error!");
       exit(0);
    }
    
    char ch=fgetc(fp);
    while(ch!=EOF)
    {
      aa[i]=ch;
      i++;
      ch=fgetc(fp);
    }
    fclose(fp);
}
void push(char a)

{
	
    top++;
    stack[top]=a;
}
char pop()
{
    return stack[top--];
}
int includevt(char x)
{
    for(int i=0;i<length_vt;i++)
    {
       if(VT[i]==x) return 1;
    }
    return 0;
}
int includean(char x,char a)
{
    int i,j;
    for(i=0;i<length_vn;i++)
    if(VN[i]==x) break;
    for(j=0;j<length_vt;j++)
    if(VT[j]==a) break;
    return analysis_table[i][j];
}
void destory()
{
    int flag=0;
    int flagg=0;
    push('#'); //将"#"和文法开始符依次压入栈中
    push(VN[0]);
    char a=aa[pp]; //把第一个输入符号读入a
    char x;
    do{
      if(flag==0)
      x=pop(); //把栈顶符号弹出并放入x中
      flag=0;
      printf("%c\t\t\t%c\t",x,a);
      if(includevt(a)==1)
      {
      	
        if(includevt(x)==1)
        {
          if(x==a) 
         {
            if(a=='#') 
            {
              flagg=1;
              printf("结束\n");
            }
            
            else printf("匹配终结符%c\n",x);
            pp++;
            a=aa[pp]; //将下一输入符号读入a;
         }
        else
        {
        	
            flag=1;
            printf("出错,跳过%c\n",a);
            pp++;
            a=aa[pp];    
        }
     }
     
     else if(includean(x,a)>=0)
     {
       int h=includean(x,a);
       printf("展开非终结符%s%s\n",F[h],Fa[h]);
       int k;
       for(k=0;k<10;k++)
       if(Fa[h][k]=='\0') break;
       if(k==4)
       {
         //printf("+++++++++++pop %c \n",x);
       }
       else
       {
         while(k!=0) //按逆序依次把yk、yk?1、…、y1压入栈中
         {
           k--;
           push(Fa[h][k]);
         }
       }
     }
     else if(includean(x,a)==-1)
     {
       flag=1;
       printf("出错,从栈顶弹出%c\n",x);
       x=pop();
     }
     else
     {
       flag=1;
       printf("出错,跳过%c\n",a);
       pp++;
       a=aa[pp];
     }
   } 
   else 
   {
     flag=1;
     printf("出错,跳过%c\n",a);
     pp++;
     a=aa[pp];
   }
 }while(x!='#');
 
 if(flagg==0)
 {
   printf("%c\t\t\t%c\t",x,a);
   printf("结束\n");
 }
}
int main()
{
   printf("请输入1 or 0:\n");
   //scanf("%d",TT);
   printf("语法分析工程如下:\n");
   initscanner();
   printf("要分析的语句是:%s\n",aa);
   printf("语法分析工程如下:\n");
   printf("栈顶元素\t\t当前单词记号\t\t\t动作\n");
   printf("--------------------------------------------------------------------\n");
   destory();
   return 0;
}
