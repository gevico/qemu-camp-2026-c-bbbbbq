#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

static int visited[MAX_ROW][MAX_COL];
static int path[MAX_ROW * MAX_COL][2];
static int path_len;

static int dfs(int row, int col)
{
	static const int dr[] = {-1, 0, 1, 0};
	static const int dc[] = {0, 1, 0, -1};

	if (row < 0 || row >= MAX_ROW || col < 0 || col >= MAX_COL) {
		return 0;
	}

	if (maze[row][col] != 0 || visited[row][col]) {
		return 0;
	}

	visited[row][col] = 1;
	path[path_len][0] = row;
	path[path_len][1] = col;
	path_len++;

	if (row == MAX_ROW - 1 && col == MAX_COL - 1) {
		return 1;
	}

	for (int i = 0; i < 4; i++) {
		if (dfs(row + dr[i], col + dc[i])) {
			return 1;
		}
	}

	path_len--;
	return 0;
}

int main(void)
{
	if (!dfs(0, 0)) {
		printf("No path!\n");
		return 1;
	}

	for (int i = path_len - 1; i >= 0; i--) {
		printf("(%d, %d)\n", path[i][0], path[i][1]);
	}

	return 0;
}
