#include <bits/stdc++.h>
using namespace std;

int main(){
    int T; scanf("%d",&T);
    for(int cas=0;cas<T;cas++){
        int n=0,ans=0,min_diviso=0;
        scanf("%d",&n);
        for(int i=1;i<=(int)sqrt(n);i++){if(n%i==0){min_diviso=i;break;} }
        for(int i=2;i<=(n/min_diviso);i++){//����n�ֳܷ�i����������
            if(i%2==0){//i��ż�������n��i�ԡ�0.5����β��n/i��Χ�Ϸ���n�ֳܷ�����i������
                if((n+i/2)%i==0&&(n/i)>=(i/2))
                    ans++;
            }
            else{//i�����������i����n��n/i��Χ�Ϸ���n�ֳܷ�����i������
                if(n%i==0&&(n/i)>=(i+1)/2)
                    ans++;
            }
        }
        printf("case #%d:\n%d\n",cas,ans);
    }
    return 0;
}
