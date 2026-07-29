#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=1e6+5;
ll m,arr[N][2],n;
void pre(ll nd)
{
	cout<<nd<<' ';
	if(arr[nd][0]!=0) pre(arr[nd][0]);
	if(arr[nd][1]!=0) pre(arr[nd][1]);
	return ;
}
void per(ll nd1)
{
	
	if(arr[nd1][0]!=0) per(arr[nd1][0]);
	cout<<nd1<<' ';
	if(arr[nd1][1]!=0) per(arr[nd1][1]);
}
void rpe(ll nd2)
{
	
	if(arr[nd2][1]!=0) rpe(arr[nd2][1]);
	if(arr[nd2][0]!=0) rpe(arr[nd2][0]);
	cout<<nd2<<' ';
}

int main(){
	
	cin>>n; 
	for(ll i=1;i<=n;i++)for(ll j=1;j<=2;j++)cin>>arr[i][j];
	pre(1);
	cout<<endl;
	per(1);
	cout<<endl;
	rpe(1);
	cout<<endl;
	return 0;


}
