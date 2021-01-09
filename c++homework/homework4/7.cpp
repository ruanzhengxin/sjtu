#include <cstring>
#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

const int maxlen = 129;

char s1[maxlen], s2[maxlen];
int s3[maxlen], s4[maxlen];
int ans[maxlen];

int main()
{
	int point1, point2, dig1, dig2;
	cin >> s1;
	int len1 = strlen(s1);
	cin >> s2;
	int len2 = strlen(s2);
	for (int i=0;i<len1;i++) if (s1[i] == '.') point1 = i;
	for (int i=0;i<len2;i++) if (s2[i] == '.') point2 = i; 
	dig1 = len1-point1-1, dig2 = len2-point2-1;
	if (dig1 < dig2)
	{
		for (int i=dig1+1;i<=dig2;i++) s1[point1+i] = '0'; 
		s1[point1+dig2+1] = 0;
	}
	else
	{
		for (int i=dig2+1;i<=dig1;i++) s2[point2+i] = '0'; 
		s2[point2+dig1+1] = 0;
	}
	len1 = strlen(s1), len2 = strlen(s2);
	int point = max(dig1,dig2)+1;
	for (int i=len1-1;i>=0;i--) if (s1[i] != '.')
		s3[len1-i] = s1[i]-48;
	for (int i=len2-1;i>=0;i--) if (s2[i] != '.')
		s4[len2-i] = s2[i]-48;
	int len = max(len1,len2);
	for (int i=1;i<=len;i++)
	{
		ans[i+1] += (s3[i]+s4[i])/10;
		ans[i] += (s3[i]+s4[i])%10;
	}
	if (ans[len+1]) len++;
	if (ans[point]) ans[point+1]++;
	int t_point = point;
	while (ans[t_point+1] == 10)
	{
		t_point++;
		ans[t_point] = 0;
		ans[t_point+1]++;
	}
	for (int i=len;i>=1;i--) 
		if (i == point) cout << ".";
		else cout << ans[i];
	cout << endl;
	return 0;
} 
