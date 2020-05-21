#include <bits/stdc++.h>

#define print(args...) fprintf(stderr, args)

using namespace std;
using pii = pair<int, int>;

const int MAXP = 103;
const int MAXN = 8;
const int MAXM = 33;
const int DAYS = 1500;

const int LOCKDOWN_RATIO = 2000;
const int CONT_PROB = 3;
const int CURE_PROB = 8;

char city_map[MAXN][MAXM] = {
	{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', },
	{'.', '#', '#', '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#', '.', },
	{'.', '#', '#', '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#', '.', },
	{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', },
	{'.', '#', '#', '#', '#', '#', '#', '.', '.', '.', '@', '@', '@', '@', '.', '.', '.', '.', '.', '@', '@', '@', '@', '.', '.', '#', '#', '#', '#', '#', '.', '#', '.', },
	{'.', '#', '.', '.', '.', '.', '#', '.', '.', '.', '.', '@', '.', '@', '.', '.', '.', '.', '.', '@', '.', '@', '.', '.', '.', '#', '.', '.', '.', '#', '.', '#', '.', },
	{'.', '#', '#', '#', '#', '#', '#', '.', '.', '.', '.', '@', '@', '@', '@', '@', '@', '@', '@', '@', '@', '@', '.', '.', '.', '#', '#', '#', '#', '#', '.', '#', '.', },
	{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', },
};

int prob_map[MAXN][MAXM] = {	
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 18, 18,  0,  0,  0,  0,  0, 18, 18, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 18, 18,  0,  0,  0,  0,  0, 18, 18, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
}

int dist[MAXN][MAXM][MAXP];
int timing[MAXN][MAXM][MAXP];
int marc[MAXN][MAXM][MAXP];
pii pred[MAXN][MAXM][MAXP];

pii positions[MAXP];
int got_out[MAXP];

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int infected_status[MAXP];
int recovered[MAXP];

int total = 1;

const int little_lockdown = 500;
int big_lockdown = 0;

pii random_coord() {
	int x = rand()%10000;
	int sum = 0;
	for (int i = 0; i < MAXN; ++i) {
		for (int j = 0; j < MAXM; ++j) {
			sum += prob_map[i][j];
			if (sum > x) return {i, j};
		}
	}
	return {MAXN-1, MAXM-1};
}

void bfs(int i, int j, int x, int y, int p) {
	queue<pii> q;
	q.push({i, j});
	marc[i][j][p] = 1;
	while (!q.empty()) {
		auto [x0, y0] = q.front(); q.pop();
		for (int k = 0; k < 4; ++k) {
			int nx = x0 + dx[k];
			int ny = y0 + dy[k];
			if (nx < 0 || nx > MAXN) continue;
			if (ny < 0 || ny > MAXM) continue;
			if (marc[nx][ny][p]) continue;
			if (city_map[nx][ny] != '.') continue;
			marc[nx][ny][p] = 1;
			dist[nx][ny][p] = dist[x0][y0][p] + 1;
			pred[nx][ny][p] = {x0, y0};
			q.push({nx, ny});
		}
	}

	pii actual = {x, y};
	int k = 0;
	pii start = {i, j};
	while (actual != start) {
		++k;
		actual = pred[actual.first][actual.second][p];
		timing[actual.first][actual.second][p] = k;
	}
}

int lockdown() {
	if (total < 10) return 10;
	return big_lockdown;
}

int main() {
	srand(time(0));
	scanf("%d", &big_lockdown);
	infected_status[0] = -1;
	for (int day = 1; day <= DAYS; ++day) {
		for (int i = 0; i < MAXN; ++i)
			for (int j = 0; j < MAXM; ++j)
				for (int p = 0; p < MAXP; ++p) {
					dist[i][j][p] = 0;
					timing[i][j][p] = 0;
					marc[i][j][p] = 0;
					pred[i][j][p] = {0, 0};
					got_out[p] = 0;
				}

		int p = 0;
		for (int i = 0; i < MAXN; ++i) {
			for (int j = 0; j < MAXM; ++j) {
				if (city_map[i][j] != '#') continue;
				if (recovered[p]) continue;
				int k = rand()%1000;
				if (k < lockdown()) continue;
				auto [x, y] = random_coord();
				bfs(i, j, x, y, p);
				got_out[p] = 1;
				++p;
			}
		}


		for (int i = 0; i < MAXN; ++i) {
			for (int j = 0; j < MAXM; ++j) {
				for (int p1 = 0; p1 < MAXP; ++p1) {
					if (!got_out[p1] || infected_status[p1] <= 0 || recovered[p1]) continue;
					for (int p2 = 0; p2 < MAXP; ++p2) {
						if (p2 == p1) continue;
						int x = rand()%70000;
						if ((abs(timing[i][j][p1] - timing[i][j][p2]) <= 1) 
							&& x < CONT_PROB
							&& infected_status[p2] == 0
							&& !recovered[p2]
							&& got_out[p2])
							infected_status[p2] = -1;
					}
				}
			}
		}

		/*for (int p1 = 0; p1 < MAXP; ++p1) {
			for (int i = 0; i < MAXN; ++i) {
				for (int j = 0; j < MAXM; ++j)
					print("%3.d ", timing[i][j][p1]);
				print("\n");
			}
			print("\n\n");
		}*/	

		total = 0;
		int rec = 0;
		for (int i = 0; i < MAXP; ++i) {
			if (recovered[i]) ++rec;
			if (recovered[i] || infected_status[i] == 0) continue;
			if (infected_status[i] < 0) {
				--infected_status[i];
				if (infected_status[i] == -3) infected_status[i] = 1;
			}
			else {
				++infected_status[i];
				int x = rand()%100;
				if (x < CURE_PROB) {
					infected_status[i] = 0;
					recovered[i] = 1;
					++rec;
					continue;
				}
			}

			++total;
		}
		//print("Day #%3d: %2d ", day, total);
		for (int i = 0; i < total; ++i)
			print("*");
		for (int i = 0; i < rec; ++i)
			print("-");
		print("\n");
		if (total <= 5 && day > 20 || total == 0) break;
	}
}