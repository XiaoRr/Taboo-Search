#ifndef PATH_H
#define PATH_H
#include <windows.h>
#include <string>
//存储路径的类
class Path {
public:
	static const int NUM = 48;
	static const int TABLE_LENGTH = 14;
	std::string filename = "att48.tsp";//"test.txt";
	int path[NUM];	//当前存储的路径
	int length;		//当前路径的长度
	int bestpath[NUM];	//存储当前最优解
	int bestlength;	//存储当前最优长度

	int table[NUM][NUM];	//禁忌表，包含短禁忌和中禁忌

	std::pair<int, int> point[50];		//存储点的坐标
	int maxx, maxy;	//坐标的最大值

	int map[50][50];	//存储点之间的距离

	std::string log[3];	//存储debug信息
	int used[NUM] = { 0 };	//临时变量，生成第一条路径时用
	//构造函数
	Path();

	//初始化路线，按照贪心思想设计一条较优路线
	void genPath(int nowp, int num);

	//交换两个节点位置
	void pSwap(int i, int j);

	//读取数据
	void readMap();

	//绘制数据
	void draw(HDC &hdc);

	//更新
	void update();


private:
	//画圆函数
	void Draw_Ellipse(HDC &hdc, int x, int y);

	//存储最优解
	void setBestPath();

	//计算变化量
	int trySwap(int x,int y);

	//计算长度
	int calLength();
};
#endif // Path_H
