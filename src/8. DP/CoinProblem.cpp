#include "../Header.cpp"

// Number of ways of reaching a quantity n from a set of coins c

int main()
{

	int c[5] = {1, 5, 10, 25, 50};
	int n;
	while(cin >> n)
	{
		int m[n+1];
		m[0] = 1;
		for(int i = 1; i <= n+1; i++) m[i] = 0;
		for(int j = 0; j < 5; j++)
		{
			for(int i = 1; i <= n+1; i++)
			{
				if(i - c[j] >= 0)
				{
					m[i] += m[i - c[j]];
					//m[i]=min(m[i],m[i-c[j]]+1); for minimum coins
				}
			}

		}
		cout << m[n] << "\n";
	}

	return 0;
}
