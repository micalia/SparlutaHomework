#include <iostream>
using namespace std;

int A;
int N[100]; // 최대 ; 100 까지라고 가정
float _sum;
//함수를 사용하면 좋은점 : 함수를 사용하므로써 코드의 중복을 피할 수 있으며
// 이는 추후 유지보수를 할때 좋음.
float Avg(int Cnt) {
    return _sum / Cnt;
}
//5
// 2 4 6 8 10
// 4 8 10 2 6

//3
//1 2 3
void Sum(int val) {
     _sum+= val;   
}

void Sort(int mode) {
    if (mode == 1) { // 오름차순
        for (int j = 0; j < A-1; j++)
        {
		    for (int i = 0; i < A - j - 1; i++)
		    {
                if (N[i] > N[i + 1]) {
                    int temp = N[i];
                    N[i] = N[i+1];
                    N[i+1] = temp;
                }
		    }
        }
    }
	else if(mode == 2) {
		for (int j = 0; j < A - 1; j++)
		{
			for (int i = 0; i < A - j - 1; i++)
			{
				if (N[i] < N[i + 1]) {
					int temp = N[i + 1];
					N[i + 1] = N[i];
					N[i] = temp;
				}
            }
		}
    }
}

int main()
{
    cin >> A;
    for (int i = 0; i < A; i++)
    {
      cin >> N[i];
    }
    for (int i = 0; i < A; i++)
    {
        Sum(N[i]);
    }

    cout << "Sum : " << _sum<< "\n";
    cout << "Average : " << Avg(A) << "\n";


	for (int i = 0; i < A; i++)
	{
        cout << "Before Sort : " << N[i] << endl;
	}
    Sort(1);
	for (int i = 0; i < A; i++)
	{
		cout << "오름차순 정렬 : " << N[i] << endl;
	}
	Sort(2);
	for (int i = 0; i < A; i++)
	{
		cout << "내림차순 정렬 : " << N[i] << endl;
	}
}
