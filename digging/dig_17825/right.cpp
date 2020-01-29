#include <iostream>
#include <algorithm>

using namespace std;
typedef pair<int, int> pii;
int arr[4][27] = { {-1,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40},{10,13,16,19,25,30,35,40},{20,22,24,25,30,35,40},{ 30,28,27,26,25,30,35,40 } };
int turn[10];
int my_turn[10];
pii where_horse[4] = { {0,0},{0,0},{0,0},{0,0} };
int horse_sum[4];
bool check_horse(pii wher)
{
   for (int i = 0; i < 4; i++)
   {
      if (where_horse[i] == wher)
         return false;
   }
   return true;
}
int maxx = 0;
void dfs(int cnt)
{

   if (cnt == 10)
   {
      int sum2 = 0;
      for (int i = 0; i < 4; i++)
      {
         sum2 += horse_sum[i];
      }
      
      
      maxx = max(maxx, sum2);
      return;
   }
   for (int i = 0; i < 4; i++)
   {
      pii before;
      pii here = where_horse[i];
      if ((here.first==1e9 && here.second==1e9))
      {
         continue;
      }
      before = here;
      here.second += turn[cnt];
      //getchar();
      if (arr[here.first][here.second] == 10)
      {
         here.first = 1;
         here.second = 0;
      }
      else if(arr[here.first][here.second] == 20)
      {
         here.first = 2;
         here.second = 0;
      }
      else if (arr[here.first][here.second] == 30 &&here.first==0)
      {
         here.first = 3;
         here.second = 0;
      }
      else if (arr[here.first][here.second] == 25)
      {
         here.first = 1;
         here.second = 4;
      }
      else if (arr[here.first][here.second] == 30)
      {
         here.first = 1;
         here.second = 5;
      }
      else if (arr[here.first][here.second] == 35)
      {
         here.first = 1;
         here.second = 6;
      }
      else if (arr[here.first][here.second] == 40)
      {
         here.first = 1;
         here.second = 7;
      }


      if (arr[here.first][here.second] == 0) {
         //마지막 까지 왔다.
         where_horse[i] = { 1e9,1e9 };
         my_turn[cnt] = i;
         dfs(cnt + 1);
         where_horse[i] = before;

      }
      else if (check_horse({ here.first,here.second }))
      {
         where_horse[i] = here;
         horse_sum[i] += arr[here.first][here.second];
         my_turn[cnt] = i;
         dfs(cnt+1);
         where_horse[i] = before;
         horse_sum[i] -= arr[here.first][here.second];
      }

   }
}
int main(void)
{

   ios_base::sync_with_stdio(0);
   cin.tie(0);
   cout.tie(0);
   for (int i = 0; i < 10; i++)
   {
      cin >> turn[i];
   }
   dfs(0);

   cout << maxx;
   return 0;
}
