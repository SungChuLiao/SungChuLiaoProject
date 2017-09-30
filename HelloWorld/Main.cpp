#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	int myNum;

	cout << "Hello, World!" << endl;
	srand(time(NULL));
	myNum = (rand() % 6) + 1;
	if (myNum >= 4)
	{
		cout << "Good Morning!" << endl;
		printf("myNum: %d\n", myNum);
	}
	else
	{
		cout << "Good Night!" << endl;
		printf("myNum: %d\n", myNum);
	}
	system("pause");
	return 0;

}
