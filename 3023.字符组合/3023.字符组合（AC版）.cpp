#include <bits/stdc++.h>
using namespace std;

int T, cnt;
char str[20];
struct data
{
    char ans[100];
}d[1<<17];

bool cmp(data x, data y)
{
    return strcmp(x.ans,y.ans)<0;
}
int main()
{
    cin>>T;
    char ch=getchar();
    while(T--){
        gets(str);
        int len=strlen(str);

        //����ȥ��
        sort(str,str+len);
        int len1=1;
        for(int i=0, j=0;j<len;++j)
            if(str[j]!=str[i]) {str[++i]=str[j];len1++;}
        str[len1]='\0';

        //������ö��
        int len2=(1<<len1);
        for(int i=1;i<len2;++i){//��1��ʼ���ռ�������
            int l=0;
            for(int j=0;j<len1;++j)
                if(i & (1 << j)) d[i-1].ans[l++]=str[j];
            d[i-1].ans[l]='\0';
        }

        //ÿ����ϰ��ֵ����źú����
        sort(d,d+len2-1,cmp);
        printf("case #%d:\n",cnt++);
        for(int i=0;i<len2-1;++i)
            printf("%s\n",d[i].ans);
        memset(str,0,sizeof(str));
        memset(d,0,sizeof(d));
    }
    return 0;
}
