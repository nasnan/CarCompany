#include<iostream>
using namespace std;


//可借车节点
template<class T>
struct availNode
{
	availNode<T> *next;
	T license;
	T miles;

	availNode() {}

	availNode(const T& license, T& miles, availNode<T> *next)
	{
		this->license = license;
		this->miles = miles;
		this->next = next;
	}
};


//已借车节点
template<class T>
struct rentedNode
{
	rentedNode<T>* next;
	T license;
	T rentedtime;
	T rentedmiles;

	rentedNode(){}

	rentedNode(const T& license, T& rentedtieme, T& rentedmiles, rentedNode<T> *next)
	{
		this->license = license;
		this->rentedtime = rentedtieme;
		this->rentedmiles = rentedmiles;
		this->next = next;
	}

	rentedNode(const T& license, T& rentedmiles, rentedNode<T> *next)
	{
		this->license = license;

		this->rentedmiles = rentedmiles;
		this->next = next;
	}
	
};


template<class T>
struct allCarsNode
{
	allCarsNode<T>* next;
	T license;
	T ranMiles;
	T status;
	T returnTime;
	T repairedTime;
	float income;

	allCarsNode(const T& license, allCarsNode<T> *next)
	{
		this->license = license;
		this->next = next;
	}
};

template<class T>
class cars
{
public:
	void addNewCar(int license, int ranmiles = 0, int status = 0, int returnTime = 0, int repairedTime = 0);

protected:
	int listSize;
	allCarsNode<T>* firstNode;

};




//可借车的类
template<class T>
class availableCar //: public chain<T>
{
public:
	availableCar(int initialCapacity = 1);

	void newAvaCar(int lic, int mile);
	void outputAvaCar();
	void eraseCar(int lic);

protected:
	int listSize;
	availNode<T>* firstNode;
};


//可借车 构造函数
template<class T>
availableCar <T>::availableCar(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		cout << "Illegalparametervalues.\n";
	}
	firstNode = NULL;
	listSize = 0;
}

//可借车 引入新车
template<class T>
void availableCar <T>::newAvaCar(int lic, int mile)
{
	firstNode = new availNode<T>(lic, mile, firstNode);
	listSize++;
}

//可借车 输出列表
template<class T>
void availableCar <T>::outputAvaCar()
{
	for (availNode<T>*p = firstNode; p != NULL; p = p->next)
		cout << "ID license : " << p->license << "; miles : " << p->miles << endl;
}

template<class T>
void availableCar <T>::eraseCar(int license)
{
	//availNode <T> *deleteNode;
	////	checkIndex(theIndex);
	//if (license == 0)
	//{
	//	deleteNode = firstNode;
	//	firstNode = firstNode->next;
	//}
	//else
	//{
	//	chainNode <T> *p = firstNode;
	//	for (int i = 0; i < theIndex - 1; i++)
	//	{
	//		p = p->next;
	//	}
	//	deleteNode = p->next;
	//	p->next = p->next->next;
	//}
	//listSize--;
	//delete deleteNode;
	//cout << "delete successfully!\n";
}


//已借车的类
template<class T>
class rentedCar 
{
public:
	rentedCar(int initialCapacity = 1);

	void newRentCar(int license, int time, int mile);
	void test(int license, int time);
	void outputRentCar();

protected:
	int listSize;
	rentedNode<T>* firstNode;
};

//已借车构造函数
template<class T>
rentedCar <T>::rentedCar(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		cout << "Illegalparametervalues.\n";
	}
	firstNode = NULL;
	listSize = 0;
};


//已借车 引入新车
template<class T>
void rentedCar <T> ::newRentCar(int license, int time, int mile)
{
	firstNode = new rentedNode <T>( license,  time, mile, firstNode);
	listSize++;
}

template<class T>
void rentedCar <T>::test(int license, int time)
{
	firstNode
}

//已借车 输出列表
template <class T>
void rentedCar <T>::outputRentCar()
{
	for (rentedNode<T>*p = firstNode; p != NULL; p = p->next)
		cout << "ID license : " << p->license << "; rentedtime : " << p->rentedtime << "; rentedmiles : " << p->rentedmiles << endl;
}


//int main()
//{
//
//	availableCar<int> x(11);
//
//	x.newAvaCar(001, 24);
////	x.erase(0);
//	x.outputAvaCar();
//
//	//rentedCar<int> x(11);
//	//x.newRentCar(001, 14, 400);
//	//x.newRentCar(002, 10, 300);
//	//x.newRentCar(004, 40, 800);
//	//x.erase(0);
//
//	//x.outputRentCar();
//	//
//
//	system("PAUSE");
//	
//	return 0;
//}