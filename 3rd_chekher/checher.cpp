/*
ID: tianlin2
PROG: checker
LANG: C++
*/
#include "iostream"
using namespace std;
#include "time.h"
#include <fstream>

// sum������¼�ʺ���óɹ��Ĳ�ͬ��������upperlim������������ж��Ѿ����ú��˻ʺ�
//g_lctn�洢λ��
long sum = 0, upperlim = 1;
int g_lctn[13] = {0};
const int mulDeBruijnBitPosition[32]=
{
	0, 1, 28, 2, 29, 14, 24 ,3, 30, 22, 20, 15,
	25, 17, 4, 8, 31, 27, 13, 23, 21, 19, 16,
	7, 26, 12, 18, 6, 11, 5, 10, 9
};
int prntNum = 0;
ifstream fin("checker.in");
ofstream fout("checker.out");

// ��̽�㷨�����ұߵ��п�ʼ��
void test(long row, long ld, long rd, int locationIndex)
{
	if (row != upperlim)
	{
		// row��ld��rd���С������㣬������п��Է��ûʺ����,��ӦλΪ0��
		// Ȼ����ȡ�����롱��ȫ1����������õ�ǰ���п��Է��ûʺ��λ�ã���Ӧ�и�Ϊ1
		// Ҳ������ȡ��ǰ��Щ�п��Է��ûʺ�
		long pos = upperlim & ~(row | ld | rd); 
		while (pos)    // 0 -- �ʺ�û�еط��ɷţ�����
		{
			// ����pos���ұ�Ϊ1��bit������bit��0
			// Ҳ����ȡ�ÿ��ԷŻʺ�����ұߵ���
			long p = pos & -pos;                                              
			g_lctn[locationIndex] = 
				mulDeBruijnBitPosition[((unsigned)p*0x077CB532U)>>27];
			// ��pos���ұ�Ϊ1��bit����
			// Ҳ����Ϊ��ȡ��һ�ε����ҿ�����ʹ����׼����
			// ����������ݵ����λ�ü�����̽
			pos -= p;                           

			// row + p������ǰ����1����ʾ��¼��λʺ���õ��С�
			// (ld + p) << 1����ǵ�ǰ�ʺ�������ڵ��в�������һ���ʺ���á�
			// (ld + p) >> 1����ǵ�ǰ�ʺ��ұ����ڵ��в�������һ���ʺ���á�
			// �˴�����λ����ʵ�����Ǽ�¼�Խ����ϵ����ƣ�ֻ����Ϊ���ⶼ����
			// ��һ������������������Ա�ʾΪ�е����ƾͿ����ˡ���Ȼ��������λ
			// ��ÿ��ѡ����֮ǰ���У�ԭ��N��N������ĳ���ѷ��õĻʺ������Խ���
			// �ϲ��������ƶ�����¼������
			test(row + p, (ld + p) << 1, (rd + p) >> 1, locationIndex + 1);
		}
	}
	else   
	{
		// row������λ��Ϊ1�����ҵ���һ���ɹ��Ĳ��֣�����
		sum++;
		if(prntNum < 3)
		{
			for(int i = 0; i < locationIndex; ++i)
			{
				if(!i)
					fout<<g_lctn[i]+1;
				else
					fout<<' '<<g_lctn[i]+1;
			}
			fout<<endl;
			++prntNum;
		}
	}
}

int main(int argc, char *argv[])
{
	time_t tm;
	int n;
	
	fin>>n;

	tm = time(0);

	// ��Ϊ�����������ƣ����ֻ��32λ��
	// ����봦��N����32�Ļʺ����⣬��Ҫ
	// ��bitset���ݽṹ���д洢
	if ((n < 1) || (n > 32))                 
	{
		printf(" ֻ�ܼ���1-32֮��\n");
		exit(-1);
	}

	// N���ʺ�ֻ��Nλ�洢��N����ĳ���лʺ����Ӧbit��1��
	upperlim = (upperlim << n) - 1;

	test(0, 0, 0, 0);
	//printf("����%ld������, ����ʱ��%d�� \n", sum, (int) (time(0) - tm));
	fout<<sum<<endl;
	//system("pause");
	return 0;
}