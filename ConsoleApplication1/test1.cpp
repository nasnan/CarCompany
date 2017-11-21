#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;

struct allCarsNode
{
	allCarsNode* next;
	int license;
	int ranMiles;
	int status;		//0:���� 1:�ѽ�  2:����
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

//״̬��Ϊ�ѽ�
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

//���г� ���³�
void allcars::addNewCar(int license, int ranMiles, int status, int returnTime, int repairedTime, double income)
{
	firstNode = new allCarsNode(license, ranMiles, status, returnTime, repairedTime, income, firstNode);
	listSize++;
}


//ɾ��
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

//���г� ���
void allcars::prin()
{

	cout << "" << setw(10) << "�������" << setw(10) << "����״̬" << setw(10) << "ʻ������" << setw(10) << "�黹ʱ��" << setw(10) << "�������" << setw(10) << "��������" << endl;
	for (allCarsNode *p = firstNode; p != NULL; p = p->next)
	{
		cout << "" << setw(10) << p->license << setw(10) << p->status << setw(10) << p->ranMiles << setw(10) << p->returnTime << setw(10) << p->repairedTime << setw(10) << p->income << endl;
	}
	
}

//�ɽ賵����
class avacars :public allcars
{
public:
	avacars(int initialCapacity = 10);
};

//�ɽ賵��ʼ��
avacars::avacars(int initialCapacity)
{
	if (initialCapacity < 1)
		cout << "Illegalparametervalues.\n";
	firstNode = NULL;
	listSize = 0;
}

//�ѽ賵����
class rentedcars : public allcars
{
public:
	rentedcars(int initialCapacity = 10);
};


//�ѽ賵��ʼ��
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

//��֤��ȷ�����ʽ
template<class T>
T inputcheck()
{
	T i;
	while (1)
	{
		cin >> i;
		if (cin.fail())
		{
			cout << "����������������룺";
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


//�����³�
void addnewcar(allcars *all, avacars *ava, rentedcars *ren, repaircars *rep,int license)
{
	all->addNewCar(license);
	ava->addNewCar(license);
}

//�⳵, ��allcars�иı�״̬Ϊ1, ��avacars�б�ɾ��, �ӵ�rentedcars
void rentcar(allcars *a, avacars *ava, rentedcars *ren)
{
	
	int license;
	cout << "��������� :";
	license = inputcheck<int>();
	

	allCarsNode *p = a->firstNode;
	while (p != 0 && p->license != license)
		p = p->next;
	if (p != NULL)
	{
		int renttime;
		cout << "����賵ʱ�� :";
		renttime = inputcheck<int>();

		a->changeCarstatus(license, p->ranMiles, 1, renttime, p->repairedTime, p->income);
		writedata(a);
		ava->erase(license);
		ren->addNewCar(p->license, p->ranMiles, 1, renttime, p->repairedTime, p->income);
		sortrent(ren);
		cout << "���⣡\n";
	}
	else
		cout << "��Ų�����" << endl;

}

//�����շ�
double charge(int miles)
{
	double c = 0;
	if (miles <= 100)
		c = 20;
	else
		c = 20 + 0.15*(c - 100);
	return c;
}

//������ ��allcars�и�״̬Ϊ0,����ʻ���� ����, ��rentedcars��ɾ�����ӵ�avacars�б�
void returncar(allcars *a, avacars *ava, rentedcars *ren)
{
	int license;
	cout << "������� :";
	license = inputcheck<int>();
	
	allCarsNode *p = a->firstNode;
	while (p != 0 && p->license != license)
		p = p->next;
	if (p != NULL)
	{
		if (p->status == 1)
		{
			int ranmiles;
			cout << "������ʻ·�� :";
			ranmiles = inputcheck<int>();

			double ch;
			ch = charge(ranmiles);
			cout << "��ʻ" << ranmiles << "km , �շ�" << ch << "Ԫ��" << endl;

			a->changeCarstatus(p->license, ranmiles + p->ranMiles, 0, 0, p->repairedTime, ch + p->income);
			writedata(a);
			ren->erase(p->license);
			ava->addNewCar(license, p->ranMiles, 0, 0, p->repairedTime, p->income);
			sortava(ava);
			cout << "�ѻ���\n";
		}
		else
			cout << "�˳��������ѽ��б�\n";
	}
	else
		cout << "��Ų����ڣ�\n";

}

//������ ��allcars��״̬Ϊ2������repaircas�б�
void repairecars(allcars *all, avacars *ava, repaircars *rep)
{
	int license;
	cout << "������� :";
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
		cout << "��������\n";
	}
	else
		cout << "��Ų����ڣ�\n";

}

//�����������allcars��״̬Ϊ0����repaircarsɾ��������avacars,��repairtime++
void finishrepaired(allcars *a, avacars *ava, repaircars *re)
{
	int license;
	cout << "������� :";
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
		cout << "�ѻ���\n";
	}
	else 
		cout << "��Ų����ڣ�\n";
}


//���ó�����ʻ·����������
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
				p = pre->next;  //p����һ���ڵ�   

			}
			p = p->next;  //p��ǰ��һ���ڵ�   
			pre = pre->next;
		}
		tail = p;
	}
	ava->erase(NULL);
}

//�ѽ賵��Ԥ�ڷ���ʱ����������
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
				p = pre->next;  //p����һ���ڵ�   

			}
			p = p->next;  //p��ǰ��һ���ڵ�   
			pre = pre->next;
		}
		tail = p;
	}
	re->erase(NULL);
}


//����allcars���ݵ�����
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


//��ȡ�����Ѵ��allcars����
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
		int status;		//0:���� 1:�ѽ�  2:����
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




//2.�����³�
void addcar(allcars *all, avacars *ava, rentedcars *ren, repaircars *rep)
{
	int license;
	int ranMiles;
	int status;		//0:���� 1:�ѽ�  2:����
	int returnTime;
	int repairedTime;
	double income;

	cout << "�����복��ţ�";
	license = inputcheck<int>();
	cout << "�����복��ʻ���ľ��루km��������1km��1km���㣺";
	ranMiles = inputcheck<int>();
	cout << "�����복��״̬��0���ɽ裬1���ѽ裬2����������";
	status = inputcheck<int>();
	cout << "�����복�黹ʱ�䣺";
	returnTime = inputcheck<int>();
	cout << "�����복ά�޹��Ĵ�����";
	repairedTime = inputcheck<int>();
	cout << "�����복�Ѵ��������룺";
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
	cout << "�Ѽ��룡" << endl;
}

void findcar(allcars *all)
{
	int license;
	cout << "������� :";
	license = inputcheck<int>();

	allCarsNode *p = all->firstNode;
	while (p != 0 && p->license != license)
		p = p->next;

	if (p != NULL)
	{
		cout << "" << setw(10) << "�������" << setw(10) << "����״̬" << setw(10) << "ʻ������" << setw(10) << "�黹ʱ��" << setw(10) << "�������" << setw(10) << "��������" << endl;
		cout << "" << setw(10) << p->license << setw(10) << p->status << setw(10) << p->ranMiles << setw(10) << p->returnTime << setw(10) << p->repairedTime << setw(10) << p->income << endl;
		
	}
	else
		cout << "��Ų����ڣ�\n";
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
	cout << "�ܹ�����Ϊ :" << income << "Ԫ" << endl;
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
		cout << "---------------------������蹫˾����ϵͳ---------------------" << endl;
		cout << "*" << setw(35) << "1. �鿴����  " << setw(26) << "*" << endl;   
		cout << "*" << setw(35) << "2. �����³�  " << setw(26) << "*" << endl;	
		cout << "*" << setw(35) << "3. �������  " << setw(26) << "*" << endl;	
		cout << "*" << setw(35) << "4. �黹����  " << setw(26) << "*" << endl;	
		cout << "*" << setw(35) << "5. ��������  " << setw(26) << "*" << endl;
		cout << "*" << setw(35) << "6. ��������  " << setw(26) << "*" << endl;
		cout << "*" << setw(35) << "7. ��ѯ      " << setw(26) << "*" << endl;
		cout << "*" << setw(35) << "8. ��ӡ�ɽ�  " << setw(26) << "*" << endl;
		cout << "*" << setw(35) << "9. ��ӡ�ѽ�  " << setw(26) << "*" << endl;
		cout << "*" << setw(35) << "10. ��ӡ����  " << setw(26) << "*" << endl;
		cout << "*" << setw(35) << "11. ��������  " << setw(26) << "*" << endl;
		cout << "*" << setw(35) << "����. �˳�      " << setw(26) << "*" << endl;
		cout << "--------------------------------------------------------------" << endl;
		cout << "������ѡ��";

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