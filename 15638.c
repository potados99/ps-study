#include <stdio.h>
int main(){int i,n;scanf("%d",&n);for(i=2;i*i<=n;++i)if(n%i==0)return puts("No")*0;puts("Yes");}

