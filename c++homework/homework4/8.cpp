#include <iostream>

using namespace std;

const int maxn = 10001;

bool f[maxn];

int main()
{
	int n, p = 0;
	cin >> n;
	for (int i=1;i<=n-1;i++)
	{
		for (int j=1;j<=3;j++)
		{
			p = p%n+1;
			while (f[p]) p = p%n+1;
		}
		f[p] = true;
	}
	for (int i=1;i<=n;i++) if (!f[i]) cout << "Last code : " << i << endl;
	return 0;
} 
