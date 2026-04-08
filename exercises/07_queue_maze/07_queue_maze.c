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

typedef struct {
	int row;
	int col;
} Node;

int main(void)
{
	Node queue[MAX_ROW * MAX_COL];
	int visited[MAX_ROW][MAX_COL] = {0};
	Node parent[MAX_ROW][MAX_COL];
	int head = 0;
	int tail = 0;
	Node end = {-1, -1};
	static const int dr[] = {1, 0, -1, 0};
	static const int dc[] = {0, 1, 0, -1};

	for (int r = 0; r < MAX_ROW; r++) {
		for (int c = 0; c < MAX_COL; c++) {
			parent[r][c].row = -1;
			parent[r][c].col = -1;
		}
	}

	queue[tail++] = (Node){0, 0};
	visited[0][0] = 1;

	while (head < tail) {
		Node current = queue[head++];

		if (current.row == MAX_ROW - 1 && current.col == MAX_COL - 1) {
			end = current;
			break;
		}

		for (int i = 0; i < 4; i++) {
			int nr = current.row + dr[i];
			int nc = current.col + dc[i];

			if (nr < 0 || nr >= MAX_ROW || nc < 0 || nc >= MAX_COL) {
				continue;
			}
			if (maze[nr][nc] != 0 || visited[nr][nc]) {
				continue;
			}

			visited[nr][nc] = 1;
			parent[nr][nc] = current;
			queue[tail++] = (Node){nr, nc};
		}
	}

	if (end.row == -1) {
		printf("No path!\n");
		return 1;
	}

	while (end.row != -1 && end.col != -1) {
		printf("(%d, %d)\n", end.row, end.col);
		end = parent[end.row][end.col];
	}

	return 0;
}
