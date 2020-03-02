#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = INT_MAX / 10;

#define min(a, b) (a<b?a:b)

int main()
{
	int N, M;
	cin >> N >> M;
	vector< vector<int> > adjMatrix(N, vector<int>(N, INF));
	int start, end, length;
	for (size_t i = 0; i < M; i++)
	{
		cin >> start >> end >> length;
		// it's 1-based, correct nodes
		--start;
		--end;
		adjMatrix[start][end] = length;
	}

	// path to the same node is zero length
	for (size_t i = 0; i < N; i++)
	{
		adjMatrix[i][i] = 0;
	}

	// Floyd algorithm
	for (size_t k = 0; k < N; ++k)
	{
		for (size_t i = 0; i < N; ++i)
		{
			for (size_t j = 0; j < N; ++j)
			{	
				adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);
			}
		}
	}

	int Q;
	cin >> Q;
	for (size_t i = 0; i < Q; i++)
	{
		cin >> start >> end;
		// it's 1-based, correct nodes
		--start;
		--end;
		length = adjMatrix[start][end] == INF ? -1 : adjMatrix[start][end];
		cout << length << endl;
	}

    return 0;
}

