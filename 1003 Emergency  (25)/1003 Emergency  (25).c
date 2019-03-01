#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


struct city_st {
	int dist, path_cnt, team_cnt, total_team_cnt;
};


void exchange(int *a, int *b);
int get_min(const struct city_st *cities, int *ready, int ready_cnt);

void exchange(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int get_min(const struct city_st *cities, int *ready, int ready_cnt)
{
	int i, rslt;

	for(i = rslt = 0; i < ready_cnt; ++i)
		if(cities[ready[i]].dist < cities[ready[rslt]].dist)
			rslt = i;

	return rslt;
}

int main()
{
	int map[500][500] = {{0}};
	struct city_st cities[500];
	int i, city_cnt, road_cnt, src, dest, c1, c2, len, ready[500], ready_cnt, u, v;

	scanf("%d%d%d%d", &city_cnt, &road_cnt, &src, &dest);

	for(i = 0; i < city_cnt; ++i) {
		cities[i].dist = INT_MAX;
		scanf("%d", &cities[i].team_cnt);
		cities[i].path_cnt = cities[i].total_team_cnt = 0;
	}

	for(i = 0; i < road_cnt; ++i) {
		scanf("%d%d%d", &c1, &c2, &len);
		map[c1][c2] = map[c2][c1] = len;
	}

	for(i = 0, ready_cnt = city_cnt; i < ready_cnt; ++i)
		ready[i] = i;

	cities[src].dist = 0;
	cities[src].path_cnt = 1;
	cities[src].total_team_cnt = cities[src].team_cnt;

	while(ready_cnt) {
		i = get_min(cities, ready, ready_cnt);

		for(u = ready[i], v = 0; v < city_cnt; ++v) {
			if(map[u][v] && cities[v].dist > cities[u].dist + map[u][v]) {
				cities[v].dist = cities[u].dist + map[u][v];
				cities[v].path_cnt = cities[u].path_cnt;
				cities[v].total_team_cnt = cities[u].total_team_cnt + cities[v].team_cnt;
			}
			else if(map[u][v] && cities[v].dist == cities[u].dist + map[u][v]) {
				cities[v].path_cnt += cities[u].path_cnt;

				if(cities[v].total_team_cnt < cities[u].total_team_cnt + cities[v].team_cnt)
					cities[v].total_team_cnt = cities[u].total_team_cnt + cities[v].team_cnt;
			}
		}

		exchange(&ready[i], &ready[--ready_cnt]);
	}

	printf("%d %d\n", cities[dest].path_cnt, cities[dest].total_team_cnt);

	return 0;
}
