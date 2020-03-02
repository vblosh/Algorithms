// CoinChange.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

vector<long long> memo;

long long make_change(vector<int>& coins, int money) 
{
	memo[0] = 1;
	for (int coin : coins)
	{
		for (int i = coin; i <= money; i++)
		{
			memo[i] += memo[i - coin];
		}
	}

	return memo[money];
}

int main() {
	int n;
	int m;
	cin >> n >> m;
	vector<int> coins(m);
	for (int coins_i = 0; coins_i < m; coins_i++) {
		cin >> coins[coins_i];
	}
	sort(coins.begin(), coins.end());

	memo.resize(n+1);

	cout << make_change(coins, n) << endl;
	return 0;
}