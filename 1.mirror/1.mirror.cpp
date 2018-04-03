// ewoosoft_1.mirror.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <stdlib.h>

#define MIN_POS		(-1000000)
#define MAX_POS		(1000000)

struct point_tag
{
	int x;
	int y;
};

struct fence_tag
{
	struct point_tag point;
	char mirror;
	bool used;
};

enum x_or_y_axis_tag
{
	X_AXIS,
	Y_AXIS,
};

enum plus_minus_way_tag
{
	PLUS_WAY,
	MINUS_WAY,
};

struct fence_tag *fences = NULL;
int N;
int a, b;

int get_input()
{
	int i;

	scanf("%d %d %d", &N, &a, &b);
	if ((N < 1) || (N > 200)) {
		return -1;
	}

	fences = (struct fence_tag *)malloc(sizeof(struct fence_tag) * (N + 1));
	if (fences == NULL) {
		return -1;
	}

	i = 0;
	fences[0].point.x = a;	fences[0].point.y = b;

	for (i = 1; i < (N + 1); i++) {
		scanf("%d %d %c", &fences[i].point.x, &fences[i].point.y, &fences[i].mirror);

		if (((fences[i].point.x < MIN_POS) ||
			(fences[i].point.x > MAX_POS) ||
			(fences[i].point.y < MIN_POS) ||
			(fences[i].point.y > MAX_POS)) ||
			((fences[i].mirror != '/') &&
			(fences[i].mirror != '\\'))) {
			free(fences);
			return -1;
		}

		fences[i].used = false;
	}

	return 0;
}

int find_next_fence(struct point_tag *point, enum x_or_y_axis_tag xy_way, enum plus_minus_way_tag sign_way)
{
	const int MAX_DIST = MAX_POS - MIN_POS;
	int i;
	struct fence_tag *fence;
	int distance;
	int min_distance = MAX_DIST;
	int min_i = (N + 1);

	for (i = 0; i < (N + 1); i++) {
		fence = &fences[i];

		distance = MAX_DIST;
		if ((xy_way == X_AXIS) && (point->y == fence->point.y)) {
			if ((sign_way == PLUS_WAY) && (fence->point.x > point->x)) {
				distance = fence->point.x - point->x;
			}
			else if ((sign_way == MINUS_WAY) && (point->x > fence->point.x)) {
				distance = point->x - fence->point.x;
			}
		}
		else if ((xy_way == Y_AXIS) && (point->x == fence->point.x)) {
			if ((sign_way == PLUS_WAY) && (fence->point.y > point->y)) {
				distance = fence->point.y - point->y;
			}
			else if ((sign_way == MINUS_WAY) && (point->y > fence->point.y)) {
				distance = point->y - fence->point.y;
			}
		}

		if (min_distance > distance) {
			min_distance = distance;
			min_i = i;
		}
	}

	if (min_i == (N + 1)) {
		min_i = -1;
	}
	else if (fences[min_i].used == true) {
		min_i = -1;
	}

	return min_i;
}

enum plus_minus_way_tag calculate_next_sign_way(enum x_or_y_axis_tag xy_way, struct point_tag *point, struct fence_tag *fence)
{
	int point_sign;
	int mirror_sign;

	point_sign = (xy_way == X_AXIS) ? fence->point.x - point->x : fence->point.y - point->y;
	mirror_sign = (fence->mirror == '/') ? 1 : -1;

	return ((point_sign * mirror_sign) > 0) ? PLUS_WAY : MINUS_WAY;
}

int move_next_fence(struct point_tag *point, enum x_or_y_axis_tag xy_way, enum plus_minus_way_tag sign_way, int turn_cnt)
{
	int next_i;
	enum x_or_y_axis_tag next_xy_way;
	enum plus_minus_way_tag next_sign_way;
	struct fence_tag *fence;
	int result_i;

	next_i = find_next_fence(point, xy_way, sign_way);
	if ((next_i == 0) || (next_i == -1)) {
		return next_i;
	}

	fence = &fences[next_i];
	fence->used = true;
	next_xy_way = (xy_way == X_AXIS) ? Y_AXIS : X_AXIS;
	if (turn_cnt < 1) {
		next_sign_way = calculate_next_sign_way(xy_way, point, fence);
		next_sign_way = (next_sign_way == PLUS_WAY) ? MINUS_WAY : PLUS_WAY;
		result_i = move_next_fence(&fence->point, next_xy_way, next_sign_way, turn_cnt + 1);
		if (result_i == 0)
			return next_i;
	}

	next_sign_way = calculate_next_sign_way(xy_way, point, fence);
	result_i = move_next_fence(&fence->point, next_xy_way, next_sign_way, turn_cnt);
	return result_i;
}


int main(int argc, char* argv[])
{
	int result;
	struct point_tag house_point;
	int turn_cnt;
	int result_i;

	result = get_input();
	if (result < 0) {
		return result;
	}

	house_point.x = 0;
	house_point.y = 0;
	turn_cnt = 0;

	result_i = move_next_fence(&house_point, X_AXIS, PLUS_WAY, turn_cnt);

	printf("%d \n", result_i);

	free(fences);

	return 0;
}
