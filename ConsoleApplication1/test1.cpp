#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;

struct allCarsNode
{
	allCarsNode* next;
	int license;
	int ranMiles;
	int status;		//0:可用 1:已借  2:在修
	int returnTime;
	int repairedTime;
	double income;

	allCarsNode(const int& license, int& ranMiles, int& status, int& returnTime, int& repairedTime, double& income, allCarsNode *next)
	{
		this->license = license;
		this->ranMiles = ranMiles;
		this->status = status;
		this->returnTime = returnTime;
		this->repairedTime = repairedTime;
		this->next = next;
		this->income = income;
	}
};





class allcars
{
public:
	allcars(int initialCapacity = 10);
	void addNewCar(int license = 0, int ranMiles = 0, int status = 0, int returnTime = 0, int repairedTime = 0, double income = 0);
	void changeCarstatus(int license, int ranMiles, int status, int returnTime,int repairedTime, double income);
	void erase(int license);
	void prin();

	int listSize;
	allCarsNode* firstNode;

};


allcars::allcars(int initialCapacity)
{
	if (initialCapacity < 1)
		cout << "Illegalparametervalues.\n";
	firstNode = NULL;
	listSize = 0;
}

//状态改为已借
void allcars::changeCarstatus(int license, int ranMiles, int status, int returnTime,int repairedTime, double income)
{
	allCarsNode  *findNode = firstNode;
	for (int i = 0; i < listSize && findNode->license != license; i++)
		findNode = findNode->next;
	findNode->status = status;
	findNode->ranMiles = ranMiles;
	findNode->income = income;
	findNode->returnTime = returnTime;
}

//所有车 加新车
void allcars::addNewCar(int license, int ranMiles, int status, int returnTime, int repairedTime, double income)
{
	firstNode = new allCarsNode(license, ranMiles, status, returnTime, repairedTime, income, firstNode);
	listSize++;
}


//删除
void allcars::erase(int license)
{

	allCarsNode *deleteNode;
	if (firstNode->license == license)
	{
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}

	else
	{
		allCarsNode* p = firstNode;
		for (int i = 0; i < listSize && p->next->license != license; i++)
		{
			p = p->next;
		}
		deleteNode = p->next;
		p->next = p->next->next;
	}
	listSize--;
	delete deleteNode;



}

//所有车 输出
void allcars::prin()
{

	cout << "" << setw(10) << "汽车编号" << setw(10) << "现在状态" << setw(10) << "驶过距离" << setw(10) << "归还时间" << setw(10) << "修理次数" << setw(10) << "带来收入" << endl;
	for (allCarsNode *p = firstNode; p != NULL; p = p->next)
	{
		cout << "" << setw(10) << p->license << setw(10) << p->status << setw(10) << p->ranMiles << setw(10) << p->returnTime << setw(10) << p->repairedTime << setw(10) << p->income << endl;
	}
	
}

//可借车的类
class avacars :public allcars
{
public:
	avacars(int initialCapacity = 10);
};

//可借车初始化
avacars::avacars(int initialCapacity)
{
	if (initialCapacity < 1)
		cout << "Illegalparametervalues.\n";
	firstNode = NULL;
	listSize = 0;
}

//已借车的类
class rentedcars : public allcars
{
public:
	rentedcars(int initialCapacity = 10);
};


//已借车初始化
rentedcars::rentedcars(int initialCapacity)
{
	if (initialCapacity < 1)
		cout << "Illegalparametervalues.\n";
	firstNode = NULL;
	listSize = 0;
}

class repaircars : public allcars
{
public:
	repaircars(int initialCapacity = 10);
};

repaircars::repaircars(int initialCapacity)
{
	if (initialCapacity < 1)
		cout << "Illegalparametervalues.\n";
	firstNode = NULL;
	listSize = 0;
}

void sortrent(rentedcars *re);
void writedata(allcars *a);
void sortava(avacars *ava);

//保证正确输入格式
template<class T>
T inputcheck()
{
	T i;
	while (1)
	{
		cin >> i;
		if (cin.fail())
		{
			cout << "输入错误，请重新输入：";
			cin.clear();
			cin.sync();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else
			break;
	}
	return i;
}


//引入新车
void addnewcar(allcars *all, avacars *ava, rentedcars *ren, repaircars *rep,int license)
{
	all->addNewCar(license);
	ava->addNewCar(license);
}

//租车, 在allcars中改变状态为1, 从avacars列表删除, 加到rentedcars
void rentcar(allcars *a, avacars *ava, rentedcars *ren)
{
	
	int license;
	cout << "请输入序号 :";
	license = inputcheck<int>();
	

	allCarsNode *p = a->firstNode;
	while (p != 0 && p->license != license)
		p = p->next;
	if (p != NULL)
	{
		int renttime;
		cout << "输入借车时间 :";
		renttime = inputcheck<int>();

		a->changeCarstatus(license, p->ranMiles, 1, renttime, p->repairedTime, p->income);
		writedata(a);
		ava->erase(license);
		ren->addNewCar(p->license, p->ranMiles, 1, renttime, p->repairedTime, p->income);
		sortrent(ren);
		cout << "已租！\n";
	}
	else
		cout << "序号不存在" << endl;

}

//还车收费
double charge(int miles)
{
	double c = 0;
	if (miles <= 100)
		c = 20;
	else
		c = 20 + 0.15*(c - 100);
	return c;
}

//还车， 在allcars中改状态为0,改行驶历程 收入, 从rentedcars中删除，加到avacars列表
void returncar(allcars *a, avacars *ava, rentedcars *ren)
{
	int license;
	cout << "输入序号 :";
	license = inputcheck<int>();
	
	allCarsNode *p = a->firstNode;
	while (p != 0 && p->license != license)
		p = p->next;
	if (p != NULL)
	{
		if (p->status == 1)
		{
			int ranmiles;
			cout << "输入行驶路程 :";
			ranmiles = inputcheck<int>();

			double ch;
			ch = charge(ranmiles);
			cout << "行驶" << ranmiles << "km , 收费" << ch << "元。" << endl;

			a->changeCarstatus(p->license, ranmiles + p->ranMiles, 0, 0, p->repairedTime, ch + p->income);
			writedata(a);
			ren->erase(p->license);
			ava->addNewCar(license, p->ranMiles, 0, 0, p->repairedTime, p->income);
			sortava(ava);
			cout << "已还！\n";
		}
		else
			cout << "此车并不在已借列表！\n";
	}
	else
		cout << "序号不存在！\n";

}

//送修理， 在allcars改状态为2，加入repaircas列表
void repairecars(allcars *all, avacars *ava, repaircars *rep)
{
	int license;
	cout << "输入序号 :";
	license = inputcheck<int>();

	allCarsNode *p = all->firstNode;
	while (p != 0 && p->license != license)
		p = p->next;

	if (p != NULL)
	{
		all->changeCarstatus(license, p->ranMiles, 2, 0, p->repairedTime, p->income);
		ava->erase(license);
		writedata(all);
		rep->addNewCar(license, p->ranMiles, 2, p->returnTime, p->repairedTime, p->income);
		cout << "已送修理！\n";
	}
	else
		cout << "序号不存在！\n";

}

//修理结束，在allcars改状态为0，从repaircars删除，加入avacars,改repairtime++
void finishrepaired(allcars *a, avacars *ava, repaircars *re)
{
	int license;
	cout << "输入序号 :";
	license = inputcheck<int>();

	allCarsNode *p = a->firstNode;
	while (p != 0 && p->license != license)
		p = p->next;

	if (p != NULL)
	{
		a->changeCarstatus(license, p->ranMiles, 0, 0, p->repairedTime++, p->income);
		writedata(a);
		re->erase(license);
		ava->addNewCar(license, p->ranMiles, 0, p->returnTime, p->repairedTime, p->income);
		sortava(ava);
		cout << "已还！\n";
	}
	else 
		cout << "序号不存在！\n";
}


//可用车按行驶路程升序排列
void sortava(avacars *ava)
{
	allCarsNode *pre, *p, *tail, *temp;
	allCarsNode *firstNode;
	ava->addNewCar(NULL);
	firstNode = ava->firstNode;
	tail = NULL;
	pre = ava->firstNode;

	while ((ava->firstNode->next->next) != tail)
	{
		p = ava->firstNode->next;
		pre = ava->firstNode;
		while (p->next != tail)
		{
			if ((p->ranMiles)>(p->next->ranMiles))
			{
				pre->next = p->next;
				p->next = p->next->next;
				pre->next->next = p;
				p = pre->next;  //p回退一个节点   

			}
			p = p->next;  //p再前进一个节点   
			pre = pre->next;
		}
		tail = p;
	}
	ava->erase(NULL);
}

//已借车按预期返回时间升序排列
void sortrent(rentedcars *re)
{
	allCarsNode *pre, *p, *tail, *temp;
	allCarsNode *firstNode;
	re->addNewCar(NULL);
	firstNode = re->firstNode;
	tail = NULL;

	pre = re->firstNode;

	while ((re->firstNode->next->next) != tail)
	{
		p = re->firstNode->next;
		pre = re->firstNode;
		while (p->next != tail)
		{
			if ((p->returnTime)>(p->next->returnTime))
			{
				pre->next = p->next;
				p->next = p->next->next;
				pre->next->next = p;
				p = pre->next;  //p回退一个节点   

			}
			p = p->next;  //p再前进一个节点   
			pre = pre->next;
		}
		tail = p;
	}
	re->erase(NULL);
}


//保存allcars数据到本地
void writedata(allcars *a)
{

	ofstream in;
	in.open("carData.txt", ios_base::out | ios_base::trunc);

	allCarsNode * p = a->firstNode;
	while (p != NULL)
	{
		in << p->license << "\t" << p->status << "\t" << p->ranMiles << "\t" << p->returnTime << "\t" << p->repairedTime << "\t" << p->income << endl;
		p = p->next;
	}
	in.close();
}


//读取本地已存的allcars数据
void readdata(allcars *a, avacars*ava, rentedcars*ret, repaircars*rep)
{
	ifstream fread("carData.txt", ios::in);
	if (!fread)
	{
		cerr << "open error!" << endl;
		abort();
	}
	while (!fread.eof())
	{
		allCarsNode* next;
		int license;
		int ranMiles;
		int status;		//0:可用 1:已借  2:在修
		int returnTime;
		int repairedTime;
		double income;

		fread >> license >> status >> ranMiles >> returnTime >> repairedTime >> income;

		a->addNewCar(license, ranMiles, status, returnTime, repairedTime, income);

		if (fread.eof())
		{
			a->erase(license);
			break;
		}

		if (status == 0)
			ava->addNewCar(license, ranMiles, status, returnTime, repairedTime, income);
		if (status == 1)
			ret->addNewCar(license, ranMiles, status, returnTime, repairedTime, income);
		if (status == 2)
			rep->addNewCar(license, ranMiles, status, returnTime, repairedTime, income);

	}
}




//2.引入新车
void addcar(allcars *all, avacars *ava, rentedcars *ren, repaircars *rep)
{
	int license;
	int ranMiles;
	int status;		//0:可用 1:已借  2:在修
	int returnTime;
	int repairedTime;
	double income;

	cout << "请输入车编号：";
	license = inputcheck<int>();
	cout << "请输入车行驶过的距离（km），不足1km按1km计算：";
	ranMiles = inputcheck<int>();
	cout << "请输入车的状态（0：可借，1：已借，2：在修理）：";
	status = inputcheck<int>();
	cout << "请输入车归还时间：";
	returnTime = inputcheck<int>();
	cout << "请输入车维修过的次数：";
	repairedTime = inputcheck<int>();
	cout << "请输入车已带来的收入：";
	income = inputcheck<double>();

	all->addNewCar(license, ranMiles, status, returnTime, repairedTime, income);
	if (status == 0)
	{
		ava->addNewCar(license, ranMiles, status, returnTime, repairedTime, income);
		sortava(ava);
	}
	if (status == 1)
	{
		ren->addNewCar(license, ranMiles, status, returnTime, repairedTime, income);
		sortrent(ren);
	}
	if (status == 2)
		rep->addNewCar(license, ranMiles, status, returnTime, repairedTime, income);
	writedata(all);
	cout << "已加入！" << endl;
}

void findcar(allcars *all)
{
	int license;
	cout << "输入序号 :";
	license = inputcheck<int>();

	allCarsNode *p = all->firstNode;
	while (p != 0 && p->license != license)
		p = p->next;

	if (p != NULL)
	{
		cout << "" << setw(10) << "汽车编号" << setw(10) << "现在状态" << setw(10) << "驶过距离" << setw(10) << "归还时间" << setw(10) << "修理次数" << setw(10) << "带来收入" << endl;
		cout << "" << setw(10) << p->license << setw(10) << p->status << setw(10) << p->ranMiles << setw(10) << p->returnTime << setw(10) << p->repairedTime << setw(10) << p->income << endl;
		
	}
	else
		cout << "序号不存在！\n";
}



void allincome(allcars *a)
{
	double income = 0;
	allCarsNode *p = a->firstNode;
	while (p != NULL)
	{
		income += p->income;
		p = p->next;
	}
	cout << "总共收益为 :" << income << "元" << endl;
}



int main()
{

	allcars a(1);
	avacars x(1);
	rentedcars r(1);
	repaircars re(1);

	readdata(&a, &x, &r, &re);

	

	while (1)
	{
		cout << "---------------------汽车租借公司管理系统---------------------" << endl;
		cout << "*" << setw(35) << "1. 查看所有  " << setw(26) << "*" << endl;   
		cout << "*" << setw(35) << "2. 引入新车  " << setw(26) << "*" << endl;	
		cout << "*" << setw(35) << "3. 租借汽车  " << setw(26) << "*" << endl;	
		cout << "*" << setw(35) << "4. 归还汽车  " << setw(26) << "*" << endl;	
		cout << "*" << setw(35) << "5. 修理汽车  " << setw(26) << "*" << endl;
		cout << "*" << setw(35) << "6. 结束修理  " << setw(26) << "*" << endl;
		cout << "*" << setw(35) << "7. 查询      " << setw(26) << "*" << endl;
		cout << "*" << setw(35) << "8. 打印可借  " << setw(26) << "*" << endl;
		cout << "*" << setw(35) << "9. 打印已借  " << setw(26) << "*" << endl;
		cout << "*" << setw(35) << "10. 打印修理  " << setw(26) << "*" << endl;
		cout << "*" << setw(35) << "11. 计算收益  " << setw(26) << "*" << endl;
		cout << "*" << setw(35) << "其他. 退出      " << setw(26) << "*" << endl;
		cout << "--------------------------------------------------------------" << endl;
		cout << "请输入选择：";

		int i;
		i = inputcheck<int>();
		
		switch (i)
			{
		case 1: a.prin(); 
			break;
		case 2: addcar(&a, &x, &r, &re);
			break;
		case 3: rentcar(&a, &x, &r);
			break;
		case 4: returncar(&a, &x, &r);
			break;
		case 5: repairecars(&a, &x, &re);
			break;
		case 6: finishrepaired(&a, &x, &re);
			break;
		case 7: findcar(&a);
			break;
		case 8:
			sortava(&x);
			x.prin();
			break;
		case 9: 
			sortrent(&r);
			r.prin();
			break;
		case 10: re.prin();
			break;
		case 11: allincome(&a);
			break;



		default:
			exit(0);
			break;
			}

	}



	system("PAUSE");
}