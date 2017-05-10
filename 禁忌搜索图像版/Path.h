#ifndef PATH_H
#define PATH_H
#include <windows.h>
#include <string>
//�洢·������
class Path {
public:
	static const int NUM = 48;
	static const int TABLE_LENGTH = 14;
	std::string filename = "att48.tsp";//"test.txt";
	int path[NUM];	//��ǰ�洢��·��
	int length;		//��ǰ·���ĳ���
	int bestpath[NUM];	//�洢��ǰ���Ž�
	int bestlength;	//�洢��ǰ���ų���

	int table[NUM][NUM];	//���ɱ������̽��ɺ��н���

	std::pair<int, int> point[50];		//�洢�������
	int maxx, maxy;	//��������ֵ

	int map[50][50];	//�洢��֮��ľ���

	std::string log[3];	//�洢debug��Ϣ
	int used[NUM] = { 0 };	//��ʱ���������ɵ�һ��·��ʱ��
	//���캯��
	Path();

	//��ʼ��·�ߣ�����̰��˼�����һ������·��
	void genPath(int nowp, int num);

	//���������ڵ�λ��
	void pSwap(int i, int j);

	//��ȡ����
	void readMap();

	//��������
	void draw(HDC &hdc);

	//����
	void update();


private:
	//��Բ����
	void Draw_Ellipse(HDC &hdc, int x, int y);

	//�洢���Ž�
	void setBestPath();

	//����仯��
	int trySwap(int x,int y);

	//���㳤��
	int calLength();
};
#endif // Path_H
