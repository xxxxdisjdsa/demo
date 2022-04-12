#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define TT 0
char aa[20]=" ";
int pp=0;
# if TT
char  VN[5]={'E','e','T','t','F'}; //���ս����
int    length_vn=5; //���ս���ĸ���
char  VT[10]={'*','l','m','+','-','(',')','i','n','#'}; //�ս���� l->/ m->% i->id n->num
int    length_vt=10; //�ս���ĸ���
char  Fa[12][6]={"Te","+Te","-Te","NULL","Ft","*Ft","nFt","mFt","NULL","(E)","i","n"};
//����ʽ��:0:E->Te 1:e->+Te 2:e->-Te 3:e->�� 
char  F[12][6]={"E->","e->","e->","e->","T->","t->","t->","t->","t->","F->","F->","F->"};
int    analysis_table[5][10]={-2,-2,-2,-2,-2,0,-1,0,0,-1,
             -2,-2,-2,1,2,-2,3,-2,-2,3,
             -2,-2,-2,-1,-1,4,-1,4,4,-1,
             5,6,7,8,8,-2,8,-2,-2,8,
             -1,-1,-1,-1,-1,9,-1,10,11,-1};
# else
char  VN[4]={'A','Z','B','Y'}; //���ս����
int    length_vn=4; //���ս���ĸ���
char  VT[5]={'a','l','d','b','#'}; //�ս����
int    length_vt=5; //�ս���ĸ���
char  Fa[6][6]={"aZ","ABl","NULL","dY","bY","NULL"};
char  F[6][6]={"A->","Z->","B->","Y->"};
int    analysis_table[4][5]={0,-2,-1,-2,-1,
             1,-2,2,-2,2,
             -2,-1,3,-2,-2,
             -2,5,-2,4,-2};
# endif
char stack[50];
int top=-1;
void initscanner() //�����ʼ�������벢��Դ�����ļ�
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
    push('#'); //��"#"���ķ���ʼ������ѹ��ջ��
    push(VN[0]);
    char a=aa[pp]; //�ѵ�һ��������Ŷ���a
    char x;
    do{
      if(flag==0)
      x=pop(); //��ջ�����ŵ���������x��
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
              printf("����\n");
            }
            
            else printf("ƥ���ս��%c\n",x);
            pp++;
            a=aa[pp]; //����һ������Ŷ���a;
         }
        else
        {
        	
            flag=1;
            printf("����,����%c\n",a);
            pp++;
            a=aa[pp];    
        }
     }
     
     else if(includean(x,a)>=0)
     {
       int h=includean(x,a);
       printf("չ�����ս��%s%s\n",F[h],Fa[h]);
       int k;
       for(k=0;k<10;k++)
       if(Fa[h][k]=='\0') break;
       if(k==4)
       {
         //printf("+++++++++++pop %c \n",x);
       }
       else
       {
         while(k!=0) //���������ΰ�yk��yk?1������y1ѹ��ջ��
         {
           k--;
           push(Fa[h][k]);
         }
       }
     }
     else if(includean(x,a)==-1)
     {
       flag=1;
       printf("����,��ջ������%c\n",x);
       x=pop();
     }
     else
     {
       flag=1;
       printf("����,����%c\n",a);
       pp++;
       a=aa[pp];
     }
   } 
   else 
   {
     flag=1;
     printf("����,����%c\n",a);
     pp++;
     a=aa[pp];
   }
 }while(x!='#');
 
 if(flagg==0)
 {
   printf("%c\t\t\t%c\t",x,a);
   printf("����\n");
 }
}
int main()
{
   printf("������1 or 0:\n");
   //scanf("%d",TT);
   printf("�﷨������������:\n");
   initscanner();
   printf("Ҫ�����������:%s\n",aa);
   printf("�﷨������������:\n");
   printf("ջ��Ԫ��\t\t��ǰ���ʼǺ�\t\t\t����\n");
   printf("--------------------------------------------------------------------\n");
   destory();
   return 0;
}
