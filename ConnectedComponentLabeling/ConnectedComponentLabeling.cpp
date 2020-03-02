// ConnectedComponentLabeling.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

using int_matrix = vector< vector<int> >;
using bit_matrix = vector< vector<bool> >;

void Visit(int_matrix& grid, bit_matrix& visited, int_matrix& ccomp, vector<int>& ccount, int row, int col, int ccnum)
{
	visited[row][col] = true;
	ccomp[row][col] = ccnum;
	if (ccnum > (int)ccount.size() - 1)
		ccount.resize(ccnum + 10);
	ccount[ccnum]++;

	for (int rd = -1; rd <= 1; rd++)
	{
		for (int cd = -1; cd <= 1; cd++)
		{
			int r = row + rd;
			int c = col + cd;
			if ((0 <= r && r < grid.size())
				&& (0 <= c && c < grid[0].size())
				)
			{
				if (!visited[r][c] && grid[r][c])
				{
					Visit(grid, visited, ccomp, ccount, r, c, ccnum);
				}
			}
		}
	}
}

int get_biggest_region(int_matrix& grid, bit_matrix& visited, int_matrix& ccomp, vector<int>& ccount)
{
	int ccnum = 1;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[0].size(); j++)
		{
			if (!visited[i][j] && grid[i][j])
			{
				Visit(grid, visited, ccomp, ccount, i, j, ccnum);
				ccnum++;
			}
		}
	}

	return *max_element(ccount.cbegin(), ccount.cend());
}

void print_matrix(int_matrix& mat)
{
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[0].size(); j++)
		{
			cout << mat[i][j] << '\t';
		}
		cout << endl;
	}
}

int main() {
	int n;
	cin >> n;
	int m;
	cin >> m;
	int_matrix grid(n, vector<int>(m));
	bit_matrix visited(n, vector<bool>(m));
	int_matrix ccomp(n, vector<int>(m));
	vector<int> ccount;
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++) 
		{
			cin >> grid[i][j];
		}
	}

	print_matrix(grid);
	cout << "biggest region " << get_biggest_region(grid, visited, ccomp, ccount) << endl;
	print_matrix(ccomp);
	return 0;
}