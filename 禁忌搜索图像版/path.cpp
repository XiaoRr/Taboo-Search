#include "stdafx.h"
#include "Path.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;

Path::Path() {
	readMap();
	genPath(0,0);
	bestlength = length = calLength();
	//for (int i = 0; i < NUM; i++) {
	//	for (int j = 0; j < NUM; j++) {
	//		log[2] += to_string(map[i][j]);
	//	}
	//	log[2] += '\n';
	//}
}

void Path::genPath(int nowp, int num) {
	if (num == NUM)return;

	path[num] = nowp;
	used[nowp] = 1;
	int min = 0x7fffffff;
	int p = -1;
	for (auto i = 0; i < NUM; i++) {
		if (used[i])continue;
		if (map[i][nowp] <= min) {
			min = map[i][nowp];
			p = i;
		}
	}
	genPath(p, num + 1);
}

void Path::pSwap(int i, int j) {
	swap(path[i], path[j]);
	calLength();
}

int Path::calLength() {
	int ans = 0;
	for (auto i = 0; i < NUM - 1; i++) {
		ans += map[path[i]][path[i + 1]];
	}
	ans += map[path[0]][path[NUM - 1]];
	length = ans;
	return ans;
}

void Path::readMap() {
	ifstream fin(filename);
	int ignore;
	maxx = maxy = -1;
	//¼������
	for (auto i = 0; i < NUM; i++) {
		fin >> ignore >> point[i].first >> point[i].second;
		maxx = max(maxx, point[i].first);		//����ͼ������ֵ
		maxy = max(maxy, point[i].second);
	}
	//���¾��룬αŷ�Ͼ��룬���㷽������
	for (auto i = 0; i < NUM; i++) {
		for (auto j = 0; j <= i; j++) {
			double rij = sqrt((point[i].first - point[j].first)*
				(point[i].first - point[j].first) +
				(point[i].second - point[j].second) *
				(point[i].second - point[j].second));
			int tij = (int)round(rij);
			map[i][j] = map[j][i] = tij + ((tij<rij) ? 1 : 0);
		}
	}
}

void Path::draw(HDC &hdc) {
	//HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	double scalex = 500.0 / maxx,scaley = 500.0 / maxy;
	for (auto i = 0; i < NUM; i++) {
		Draw_Ellipse(hdc, point[i].first*scalex + 10, point[i].second*scaley + 10);
	}
	//SelectObject(hdc, hPen);
	MoveToEx(hdc, point[path[0]].first*scalex +10, point[path[0]].second*scaley +10,NULL);
	for (auto i = 1; i < NUM; i++) {
		LineTo(hdc, point[path[i]].first*scalex + 10, point[path[i]].second*scaley +10);
	}
	LineTo(hdc, point[path[0]].first*scalex + 10, point[path[0]].second*scaley + 10);	//�������

	log[0] = "��ǰ����Ϊ��" + to_string(length);
	string llog = log[0] + '\n' + log[1] + '\n' + log[2];
	tagRECT tag = tagRECT{ 50,600,700,700 };
	DrawText(hdc, llog.c_str(), -1, &tag, DT_LEFT);
	//DrawText(hdc, log.c_str(), -1, &tag, DT_LEFT);
}

void Path::Draw_Ellipse(HDC &hdc, int x, int y) {
	int color = RGB(0, 255, 0);
	HBRUSH brush = CreateSolidBrush(color);
	SelectObject(hdc, brush);
	Ellipse(hdc, x - 5, y - 5, x + 5, y + 5);
	DeleteObject(brush);
}

void Path::setBestPath() {
	for (auto i = 0; i < NUM; i++) {
		bestpath[i] = path[i];
	}
}

//x<y
//int Path::trySwap(int x,int y){
//	if (x > y)swap(x, y);
//	int ans = 0;
//	if (x == 0 && y == 3) {
//		int a = 1;
//	}
//	if (x + 1 != y && (y+1)%NUM != x) {
//		ans -= map[path[x]][path[(x + 1) % NUM]] + map[path[x]][path[(x - 1 + NUM) % NUM]] +
//			map[path[y]][path[(y + 1) % NUM]] + map[path[y]][path[(y - 1 + NUM) % NUM]];
//		ans += map[path[x]][path[(y + 1) % NUM]] + map[path[x]][path[(y - 1 + NUM) % NUM]] +
//			map[path[y]][path[(x + 1) % NUM]] + map[path[y]][path[(x - 1 + NUM) % NUM]];
//	}
//	else if(x+1 ==y){
//		ans -= map[path[x]][path[(x - 1 + NUM) % NUM]] + map[path[y]][path[(y + 1) % NUM]];
//		ans += map[path[y]][path[(x - 1 + NUM) % NUM]] + map[path[x]][path[(y + 1) % NUM]];
//	}
//	else {
//		ans -= map[path[x]][path[(x - 1 + NUM) % NUM]] + map[path[y]][path[(y + 1) % NUM]];
//		ans += map[path[y]][path[(x + 1) % NUM]] + map[path[x]][path[(y -1 + NUM) % NUM]];
//	}
//	return ans;
//}

void Path::update() {

	int Min = 0x7fffffff;	//�������Ž��¼
	int Min2 = length;	//������Ž��¼
	int minx = -1, miny = -1 ,min2x = -1, min2y = -1;
	//x>y
	for (auto y = 1; y < NUM; y++) {
		for (auto x = 0; x < y; x++) {
			if (table[x][y] > 0) {	//���ɱ��ڷ���������
				table[x][y]--;
			}
			//int tmp = trySwap(x, y);
			pSwap(x, y);
			//�������
			if (Min2 > length) {
				Min2 = length;
				min2x = x, min2y = y;
			}
			//��������
			if (Min > length && table[x][y] < 7) {
				Min = length;
				minx = x, miny = y;
			}
			pSwap(x, y);
		}
	}
	if (Min2 < length) {
		//����ɹ�
		table[min2x][min2y] = TABLE_LENGTH;	//����µĽ���ֵ
		pSwap(min2x, min2y);	//�����ڵ�
	}
	else {
		table[minx][miny] = TABLE_LENGTH;	//����µĽ���ֵ
		pSwap(minx, miny);	//�����ڵ�
	}

	int tmplength = length;
	//if (tmplength - length != Min) {
	//	log[1] = to_string(Min) + " " + to_string(tmplength) + " "+to_string(length) + " swap "+to_string(minx) + " " +to_string(miny);
	//}
	if (tmplength < bestlength) {
		bestlength = tmplength;
		setBestPath();	//�����µ�·��
	}

	log[0] = "��ǰ����Ϊ��" + to_string(length);

}