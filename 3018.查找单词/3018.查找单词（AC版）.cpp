#include <bits/stdc++.h>
using namespace std;
//ģ�⣺ע���жϼ����߽�����

int T, cnt, flag, ans;
char obj[200];//����˵��w���Ȳ�����10�� ������Ե�10�ͳ���10���������黹�ǿ���ĺ�
char str[1000005];

void conver(char *s)//��������ĸȫ��ת���ɴ�д
{
    int len=strlen(s);
    for(int i=0;i<len;++i)
        if(s[i]>='a'&&s[i]<='z') s[i]-=32;
}

void modify(char * s){
    int len=strlen(s);
    s[len+2]='\0';s[len+1]=' ';
    for(int i=len-1;i>=0;i--)
        s[i+1]=s[i];
    s[0]=' ';
}

int main()
{
    scanf("%d\n",&T);
    while(T--){
        gets(obj);
        gets(str);

        conver(obj);
        conver(str);

        modify(obj);
        modify(str);

        char* p=strstr(str,obj);
        printf("case #%d:\n",cnt++);
        if(p!=NULL) printf("%d\n",p-&str[0]+1);
        else printf("None\n");
    }
    return 0;
}
