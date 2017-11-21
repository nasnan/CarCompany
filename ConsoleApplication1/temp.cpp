//#include <iostream>
//
//using namespace std;
//
//template <class T>
//T inputint()
//{
//	T i;
//	while (1)
//	{
//		cout << "input:";
//		cin >> i;
//		if (cin.fail())
//		{
//			cin.clear();
//			cin.sync();
//			cin.ignore(numeric_limits<streamsize>::max(), '\n');
//			continue;
//		}
//		else
//			break;
//	}
//	return i;
//}
//
//int main()
//{
//	float a;
//	a = inputint<float>();
//}
//
