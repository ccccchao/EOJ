#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define RAND(X) (rand()%(X))
#define NUM_ORDER	(30)
#define NUM_CAR    (10)
#define GENERATIONS	(5000)
#define MAX_SIZE	(50)
#define LOWEST_ALIVE	(1.0/MAX_SIZE)

class Point{
//�����
public:
    double x,y;
};

class Order{
//��������ʾ��������ϵ�Ͷ�����������
public:
    Point shop,customer;
    bool has_taken, is_finish;
};

class Car{
//���֣����;��2*NUM_ORDER�������
public:
    int _order;
    Order orders[NUM_ORDER];
    Point points[2*NUM_ORDER];
};

class Solution{
//�������ͷ���������ÿ�����ֵ�·����Ϣ
//�൱�������еġ����塱�������Լ�����Ӧֵ�ʹ����
public:
    Car cars[NUM_CAR];
    double adapt,pAlive;
};

Solution solutions[MAX_SIZE];//one generation

float	Pm = 0.1;//�������
float	Pc = 0.8;//�������
int bestOne;//�ô����Ž��id

void getFitness(Solution &solution) // �õ���Ӧֵ����Ŀ�꺯���йأ�
{
    double cost;
    cost=;
    solution.adapt=cost;
    solution.pAlive=1.0/cost;
//	int distance = 0;
//	int temp;
//	int x1, x2, y1, y2;
//	int tdistance;
//	for (int i = 1; i < NUM_CITY; i++)
//	{
//		distance += cityDistance[group.city[i - 1]][group.city[i]];
//	}
//	group.adapt = distance;
//	group.pAlive = 1 / (float)distance;
}

void Swap(int &a, int &b) // ����abֵ
{
    int c;
	c = a;
	a = b;
	b = c;
}

void Init() // ��ʼ��
{
	srand((unsigned int)time(0));

	for (int i = 0; i < MAX_SIZE; i++){ // ��ʼ������
		for (int j = 0; j < NUM_CITY; j++){
			g_Group[i].city[j] = j;
		}
	}
	int r;
	for (int i = 0; i < MAX_SIZE; i++) {// ����˳��
		for (int j = 0; j < NUM_CITY; j++){
			r = RAND(NUM_CITY);
			Swap(g_Group[i].city[j], g_Group[i].city[r]);
		}
	}
	printf("������ʼ��Ⱥ���£�\n");
	for (int i = 0; i < MAX_SIZE; i++){
		printf("��%d������:\n", i + 1);
		for (int j = 0; j < NUM_CITY; j++){
			printf("%3d ", g_Group[i].city[j]);
		}
		printf("\n");
	}
}

void GetAliveP() //�������ʼ���&����
{
    double totalAlive = 0;
	for (int i = 0; i < MAX_SIZE; i++){// ���������Ӧֵ
		getFitness(solutions[i]);
		totalAlive += solutions.pAlive;
	}
	for (int i = 0; i < MAX_SIZE; i++) {// ������������ ���ܺ�Ϊ1
		solutions[i].pAlive /= totalAlive;
	}
}

void ShowBest()//ѡ��չʾ�ô����Ÿ���
{
	bestOne = 0;
	for (int i = 1; i < MAX_SIZE; i++){
		if (solutions[i].pAlive > solutions[bestOne].pAlive)
			bestOne = i;
	}
	printf("Ŀǰ��Ѹ���Ϊ��%d, �����Ϊ%lf ,��켣���£�\n", bestOne+1, solutions[bestOne].adapt);
	for(int i=0;i<NUM_CAR;i++){
        int num_of_points=2*solutions[bestOne].cars[i]._order;
        for(int j=0;j<num_of_points;j++){
            printf("(%lf,%lf) ",solutions[bestOne].cars[i].points[j].x,
                                          solutions[bestOne].cars[i].points[j].y);
        }
	}
	printf("\n");
}

int isOnIt(int num, int Array[NUM_CITY], int ignorePos, int pos1, int pos2){ // num�Ƿ���Array[]��pos1��pos2֮�� ��������ignorePos(�����ֵ�ԭλ��)
	for (int i = pos1; i <= pos2; i++){
		if (Array[i] == num)
			return i;
	}
	return -1;
}

void Swap(int sel1,int sel2,int pos1, int pos2)// ���滥��
{
    int temp;
	//int maxSize = pos2 - pos1 + 1;
	//printf("��ʼ�������滥��\n");
	//printf("%d %d\n", pos1, pos2);
	for (int i = pos1; i <= pos2; i++){
		temp = g_Group[sel1].city[i];
		g_Group[sel1].city[i] = g_Group[sel2].city[i];
		g_Group[sel2].city[i] = temp;
	}
	int pos;
	//printf("��ʼ�����ظ�ֵ\n");
	int times = 0;
	for (int i = 0; i < NUM_CITY; i++){// �����ظ�ֵ
		times = 0;
		if (i >= pos1 && i <= pos2){
			i = pos2;
			continue;
		}
		do{
			times++;
			pos = isOnIt(g_Group[sel1].city[i], g_Group[sel1].city, i, pos1, pos2);
			if (pos != -1){
			/*
				for (int j = 0; j < NUM_CITY; j++)
					printf("%4d", g_Group[sel1].city[j]);
				printf("\n");
				for (int j = 0; j < NUM_CITY; j++)
					printf("%4d", g_Group[sel2].city[j]);
				printf("\n");
				printf("%d %d %d %d %d\n",pos1,pos2,pos, g_Group[sel1].city[i], g_Group[sel2].city[pos]);*/
				g_Group[sel1].city[i] = g_Group[sel2].city[pos];
				//printf("pos:%d,pos1:%d,pos2:%d\n", pos, pos1, pos2);
			}
		} while (pos != -1);
		do{
			pos = isOnIt(g_Group[sel2].city[i], g_Group[sel2].city, i, pos1, pos2);
			if (pos != -1)
			{
				g_Group[sel2].city[i] = g_Group[sel1].city[pos];
				//printf("pos:%d,pos1:%d,pos2:%d\n", pos, pos1, pos2);
			}
		} while (pos != -1);
	}
//	printf("���滥���������\n");
}

void Mutation(int sel, int pos1,int pos2)//����ͻ��
{
    int maxSize = pos2 - pos1 + 1;
	for (int i = 0; i < maxSize / 2; i++)
	{
		Swap(g_Group[sel].city[pos1+i], g_Group[sel].city[pos2-i]);
	}
}

void Genetic()// ������һ����Ⱥ
{
	int maxNum = 0, minNum = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (g_Group[i].pAlive > g_Group[maxNum].pAlive)
			maxNum = i;
		if (g_Group[i].pAlive < g_Group[maxNum].pAlive)
			minNum = i;
	}
	g_Group[minNum] = g_Group[maxNum]; // ʹ���ֱ���滻��С
	//printf("��ʼ����\n");
	// �������
	int selNum;
	int maxTimes = 0, nowTimes = 0;
	int canSelected[MAX_SIZE]; // �������ڽ���ĸ���
	bool isCanSelected[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++){
		if (i == maxNum) // ����������ĸ���������
			continue;
		else if ((RAND(100)) / 100.0 < Pc){// ���ݸ����ж��Ƿ�������
			canSelected[maxTimes++] = i;
		}
	}
	for (int i = 0; i < maxTimes; i++){
		selNum = RAND(maxTimes);

		Swap(canSelected[i], canSelected[selNum]);
	}
	int pos1, pos2;
	for (int i = 0; i < maxTimes; i+=2){
		selNum = i + 1;
		if (selNum >= maxTimes)
			break;
		pos1 = RAND(NUM_CITY); // ѡ������λ��
		pos2 = RAND(NUM_CITY - pos1) + pos1;
		if (pos1 == pos2){
			if (pos1 > 0)
				pos1--;
			else
				pos2++;
		}/*
		printf("%d��%d��ʼ���滥��\n", canSelected[i], canSelected[selNum]);*/
		Swap(canSelected[i], canSelected[selNum], pos1, pos2);
		/*
				printf("��%d�������%d������н�����ԣ��õ��µ�������������:\n", canSelected[i] + 1, canSelected[selNum] + 1);
				printf("��%d����:\n", canSelected[i] + 1);
				for (int j = 0; j < NUM_CITY; j++)
				printf("%4d", g_Group[canSelected[i]].city[j]);
				printf("\n��%d����:\n", canSelected[selNum] + 1);
				for (int j = 0; j < NUM_CITY; j++)
				printf("%4d", g_Group[canSelected[selNum]].city[j]);
				printf("\nselNum:%d, maxTimes:%d\n",selNum,maxTimes);*/
	}
/*
	printf("��ʼͻ��\n");*/
	// ͻ��
	for (int i = 0; i < MAX_SIZE; i++){
		if (i == maxNum || i == minNum){
			continue;
		}
		if (RAND(100) / 100.0 < Pm){ // ����ͻ�����
			pos1 = RAND(NUM_CITY); // ѡ��λ��
			pos2 = RAND(NUM_CITY - pos1) + pos1;
			if (pos1 == pos2){
				if (pos1 > 0)
					pos1--;
				else
					pos2++;
			}
			/*printf("��%d����ͻ��ǰ��\n", i + 1);
			for (int j = 0; j < NUM_CITY; j++)
				printf("%4d", g_Group[i].city[j]);
			printf("\n");*/
			Mutation(i, pos1, pos2);
		//	printf("��%d����ͻ�䣺\n", i + 1);/*
		//	for (int j = 0; j < NUM_CITY; j++)
		//		printf("%4d", g_Group[i].city[j]);
		//	printf("\n");
		}
	}
}

void Train(){
	int nowGenerations = 0;
	float totalAlive = 0;
	do{
		printf("��%d����Ⱥ\n", nowGenerations + 1);
		GetAliveP();// ��������
		Genetic();// �����Ŵ����ɵõ���һ��
		nowGenerations++;
	} while (nowGenerations < GENERATIONS);
	printf("����%d�η��ܣ��õ����������Ϊ:\n", nowGenerations);
	printf("�����Ϊ%d,��켣���£�\n", g_Group[bestOne].adapt);
	for (int i = 0; i < NUM_CITY; i++)
		printf("%d ", g_Group[bestOne].city[i]);
	printf("\n");
	printf("�����������£�\n");
	for (int i = 0; i < MAX_SIZE; i++){
		printf("�����Ϊ%d,��켣���£�\n", g_Group[i].adapt);
		for (int j = 0; j < NUM_CITY; j++){
			printf("%d ", g_Group[i].city[j]);
		}
		printf("\n");
	}
}
int main(){
	Init();
	Train();
	return 0;
}



