#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<cstring>
#include<cmath>
#include<stdlib.h>
#define error 0
#define ok 1
#define Max_Size 100
using namespace std;

typedef int Status;
typedef struct Warehourse {
	char number[Max_Size];//货物编号
	char name[Max_Size];//货物名称
	char counter[Max_Size];//货物数量
}WAREHOUSE;

typedef struct DuLNode
{
	WAREHOUSE data;
	struct DuLNode* prior, * next;
}DuLNode, * DuLinkList;
int number = 0;

//初始化链表
void InitLinkList(DuLinkList& L)
{
	L = new DuLNode;
	L->next = NULL;
	L->prior = L->next;
}
//读取仓库文件
int read(DuLinkList& L)
{
	FILE* fp;
	int i;
	DuLinkList p, ptemp;//WAREHOUSE
	char tag;

	p = L;
	ptemp = NULL;
	fp = fopen("warehouse.dat", "rb");//打开文件
	//fp = fopen("warehouse.dat", "rb");
	//	cout << "打开文件失败！"
	tag = fgetc(fp);
	rewind(fp);
	//i = 0;
	if (tag != EOF)
	{
		for (i = 0; !feof(fp); i++)
		{
			ptemp = new DuLNode;
			fread(&ptemp->data, sizeof(WAREHOUSE), 1, fp);
			
			ptemp->next = p->next;
			p->next = ptemp;
			ptemp->prior = p;
			p = ptemp;
		}
		p->prior->next = NULL;
		delete ptemp;
		
	}
	number = i;
	fclose(fp);
	return ok;
}

//保存新的仓库文件
void save(DuLinkList& L)
{
	DuLinkList ptemp;
	FILE* fp;

	ptemp = L->next;
	if (number == 0)cout << "目前仓库无数据，请重新添加数据！"<<endl;

	if ((fp = fopen("warehouse.dat", "wb+")) == NULL)
	{
		cout << "无法打开此文件" << endl;
		exit(0);
	}

	for (int i = 0; ptemp; i++)
	{
		fwrite(&ptemp->data, sizeof(WAREHOUSE), 1, fp);
		ptemp = ptemp->next;
	}
	fclose(fp);
	if(number>0)
	cout <<"\t\t\t"<< "本地保存成功" << endl;
}

//查询仓库储存情况
void find(DuLinkList& L)
{
	DuLinkList ptemp;
	char Gnumber[20];
	char Gname[20];
	char tag;//标记是否要输入
	int flag;
	int i;
	int record;

	ptemp = L->next;
	cout << "请问你想以什么形式查找？（1是按照货物编号查找，2是按照名称查找）";
	cin >> flag;
	if (flag == 1)
	{
		cout << "请输入你所需要找的货物编号(在10位数字以下)：";
		getchar();
		cin.getline(Gnumber, 20);
		while (strlen(Gnumber) > 10)
		{
			cout << "你输入的货物编号有误，请重新输入";
			getchar();
			cin.getline(Gnumber, 20);
		}
		while (ptemp != NULL)
		{
			record = 1;
			if (strcmp(ptemp->data.number, Gnumber) == 0)
			{
				cout << "位序：" << record << "  " << "货物编号：" << ptemp->data.number << "  " << "货物名称：" << ptemp->data.name << "货物数量：" << ptemp->data.counter << endl;
				break;
			}
			ptemp = ptemp->next;
			record++;
		}
	}//flag==1
	

	else if (flag == 2)
	{
		cout << "请输入你所需要找的货物名称(在10位字母以下)：";
		getchar();
		cin.getline(Gname, 20);
		while (strlen(Gname) > 10)
		{
			cout << "你输入的货物名称有误，请重新输入";
			getchar();
			cin.getline(Gname, 20);
		}
		while (ptemp != NULL)
		{
			record = 1;
			if (strcmp(ptemp->data.name, Gname) == 0)
			{
				cout << "位序：" << record << "  " << "货物编号：" << ptemp->data.number << "  " << "货物名称：" << ptemp->data.name << "货物数量：" << ptemp->data.counter << endl;
				break;
			}
			ptemp = ptemp->next;
			record++;
		}
		if (ptemp == NULL)cout << "该仓库没有该数据" << endl;
	}
}

//修改编号
void modify_number(WAREHOUSE& ptemp)
{
	cout << "请输入新的货物编号：";
	getchar();
	cin.getline(ptemp.number, 20);
	while (strlen(ptemp.number) > 10)
	{
		cout << "请输入新的货物编号：";
		getchar();
		cin.getline(ptemp.number, 20);
	}
	cout << "修改成功" << endl;
}

//修改货物名称
void modify_name(WAREHOUSE& ptemp)
{
	cout << "请输入新的货物名称：";
	getchar();
	cin.getline(ptemp.name, 20);
	while (strlen(ptemp.name) > 10)
	{
		cout << "请输入新的货物名称：";
		getchar();
		cin.getline(ptemp.number, 20);
	}
	cout << "修改成功" << endl;
}

//修改货物数量
void modify_counter(WAREHOUSE& ptemp)
{
	cout << "请输入新的货物数量：";
	getchar();
	cin.getline(ptemp.counter, 20);
	cout << "修改成功" << endl;
}

//全部修改
void modify_all(WAREHOUSE& ptemp)
{
	cout << "请输入新的货物编号:" << endl;
	getchar();
	cin.getline(ptemp.number, 20);
	cout << "请输入新的货物名称:" << endl;
	getchar();
	cin.getline(ptemp.name, 20);
	cout << "请输入新的货物数量:" << endl;
	getchar();
	cin.getline(ptemp.counter, 20);

	while (strlen(ptemp.number) > 10)
	{
		cout << "请输入新的货物编号：";
		getchar();
		cin >> ptemp.number;
	}
	//名称 

	while (strlen(ptemp.name) > 10)
	{
		cout << "请输入新的货物名称：";
		getchar();
		cin >> ptemp.name;
	}
	cout << "修改成功" << endl;
}

//修改数据2
void modify_add_cin(WAREHOUSE& ptemp)
{
	int tag;

	cout << "请问是想修改哪个数据，还是全部修改？（修改货物编号输入0，修改货物名称输入1，修改货物数量输入2，全部修改输入3）：";
	cin >> tag;
	switch (tag)
	{
	case 0:modify_number(ptemp); break;
	case 1:modify_name(ptemp); break;
	case 2:modify_counter(ptemp); break;
	case 3:modify_all(ptemp); break;
	}
}
//修改数据
void modify(DuLinkList& L)
{
	char Gnumber[20];
	char Gname[20];
	char Gcounter[20];
	DuLinkList ptemp;
	bool flag = 0;

	ptemp = L;
	cout << "请输入你想修改的货物编号：";
	//cin >> Gnumber;
	getchar();
	cin.getline(Gnumber, 20);
	while (strlen(Gnumber) > 10)
	{
		cout << "你输入的编号有误，请重新输入！" << endl;
		cout << "请输入你想修改的货物编号: ";
		getchar();
		cin.getline(Gnumber, 20);
	}
	while (ptemp)
	{
		if (strcmp(Gnumber, ptemp->data.number) == 0)
		{
			flag = 1;
			modify_add_cin(ptemp->data);
		}
		ptemp = ptemp->next;
		
	}
	if (flag == 0)cout << "你输入的编号没有该数据！" << endl;
}

//添加数据
void add_cin(WAREHOUSE& ptemp)
{
	/*cout << "请输入货物编号，货物名称，货物数量" << endl;
	cin >> ptemp.number >> ptemp.name >> ptemp.counter;*/

	cout << "请输入新的货物编号:" << endl;
	getchar();
	cin.getline(ptemp.number, 20);
	cout << "请输入新的货物名称:" << endl;
	cin.getline(ptemp.name, 20);
	cout << "请输入新的货物数量:" << endl;
	cin.getline(ptemp.counter, 20);

	while (strlen(ptemp.number) > 10)
	{
		cout << "请输入新的货物编号:" << endl;
		getchar();
		cin.getline(ptemp.number, 20);
		cout << "请输入新的货物名称:" << endl;
		//getchar();
		cin.getline(ptemp.name, 20);
		cout << "请输入新的货物数量:" << endl;
		//getchar();
		cin.getline(ptemp.counter, 20);
	}
	while (strlen(ptemp.name) > 10)
	{
		cout << "请输入新的货物编号:" << endl;
		getchar();
		cin.getline(ptemp.number, 20);
		cout << "请输入新的货物名称:" << endl;
		//getchar();
		cin.getline(ptemp.name, 20);
		cout << "请输入新的货物数量:" << endl;
		//getchar();
		cin.getline(ptemp.counter, 20);
	}
}
void add(DuLinkList& L)
{
	DuLinkList ptemp;
	int count;
	//int record;

	cout << "请输入你想添加的货物条数：";
	cin >> count;
	number = count;
	while (count != 0)
	{
		if (L->next == NULL)
		{
			ptemp = new DuLNode;
			ptemp->next = L->next;
			L->next = ptemp;
			ptemp->prior = L;
			cout << "请添加货物信息：" << endl;
			add_cin(ptemp->data);
		}
		else
		{
			ptemp = new DuLNode;
			ptemp->prior = L;
			ptemp->next = L->next;
			L->next->prior = ptemp;
			L->next = ptemp;
			cout << "请添加货物信息：" << endl;
			add_cin(ptemp->data);
		}
		count--;
	}
	if (number > 0)
		cout << "新的货物信息已添加成功！" << endl;
	else
		cout << "当前添加的货物信息为0！" << endl;
}

//删除货物信息
void del(DuLinkList& L)
{
	char Gnumber[20];
	char Gname[20];
	char Gcounter[20];
	DuLinkList ptemp;
	int tag;//根据什么来删除
	int i;
	char ch;//是否删除

	ptemp = L;
	cout << "请问你需要根据什么来删除？（输入1是根据编号删除，输入2是根据名称删除）" << endl;
	cout << "温馨提示：货物编号是唯一的，货物名称有可能重复哦!" << endl;
	cout << "请输入你的选择:";
	cin >> tag;

	if (tag == 1)
	{
		cout << "请输入你想删除的货物编号：";
		getchar();
		cin.getline(Gnumber, 20);
		for (i = 0; ptemp; i++)
		{
			if (strcmp(Gnumber, ptemp->data.number) == 0)
			{
				cout << "是否确认删除该货物信息（y/n）";
				cin >> ch;
				if (ch == 'y' || ch == 'Y')
				{
					cout << "已删除货物编号为 " <<" "<< Gnumber << "的所有信息!" << endl;
				    	//在末尾找到
						if (ptemp->next == NULL)
						{
							ptemp->prior->next = ptemp->next;
						}
						//中间区域找到
						if (ptemp->next != NULL)
						{
							ptemp->prior->next = ptemp->next;
							ptemp->next->prior = ptemp->prior;
						}
						free(ptemp);
					break;
				}
				else
				{
				   break;
				}
			}
			ptemp = ptemp->next;
		}
	}
	else if(tag==2)
	{
		cout << "请输入你想删除的货物名称：";
		getchar();
		cin.getline(Gname, 20);
		for (i = 0; ptemp; i++)
		{
			if (strcmp(Gname, ptemp->data.name) == 0)
			{
				cout << "是否确认删除该货物信息（y/n）";
				cin >> ch;
				if (ch == 'y' || ch == 'Y')
				{
					cout << "已删除货物名称为 " <<"  "<< Gnumber << "的所有信息!" << endl;
				    	//在末尾找到
						if (ptemp->next == NULL)
						{
							ptemp->prior->next = ptemp->next;
						}
						//中间区域找到
						if (ptemp->next != NULL)
						{
							ptemp->prior->next = ptemp->next;
							ptemp->next->prior = ptemp->prior;
						}
						free(ptemp);
					break;
				}
				else
				{
				   break;
				}
			}
			ptemp = ptemp->next;
		}
	}
		//找不到
		if (ptemp == NULL || i == number)
		{
			cout << "未查找到该货物信息！" << endl;
		}

		

}

//重新建立文件
void new_file(DuLinkList& L)
{
	FILE* fp;
	if ((fp = fopen("warehouse.dat", "w")) == NULL)
	{
		cout << "新建文件失败!";
		getchar();
		exit(0);
		fclose(fp);
	}
	else
	{
		cout <<"\t\t\t"<< "新建文件成功!" << endl;
	}
}

//浏览全部仓库信息
void list(DuLinkList& L)
{
	DuLinkList ptemp;

	ptemp = L->next;
	
	if (ptemp == NULL)cout <<"\t\t\t"<< "该仓库没有数据可读" << endl;
	while (ptemp != NULL)
	{
		cout <<"\t\t\t"<< "货物编号：" << ptemp->data.number << "  " << "货物编号：" << ptemp->data.name << "  " << "货物数量：" << ptemp->data.counter << endl;
		ptemp = ptemp->next;
	}
	
}

//菜单栏 
void menu()
{
	//system("cls");
	printf("\n\t\t\t该系统版权归19软件一班 涛哥 119583010135    没问侵权违法!\n");
	printf("\t\t\t*********************************************************\n");
	printf("\t\t\t************* 仓库管理系统 ******************************\n");
	printf("\t\t\t*            1-----查询仓库信息                     *****\n");
	printf("\t\t\t*            2-----修改仓库信息                   *******\n");
	printf("\t\t\t*            3-----添加仓库信息                  ********\n");
	printf("\t\t\t*            4-----删除仓库信息                 *********\n");
	printf("\t\t\t*            5-----保存仓库信息               ***********\n");
	printf("\t\t\t*            6-----新建仓库                     ************\n");
	printf("\t\t\t*            7-----浏览仓库信息             **************\n");
	printf("\t\t\t*            8-----退出程序                  **************\n");
	printf("\t\t\t*********************************************************\n");
	printf("    \t \t\t\t  请输入你想要进行的操作所对应的选项：（1-8）:");

}

//main
int main()
{
	int sele;
	int key = 0;
	DuLinkList L;
	char ch;

	menu();
	InitLinkList(L);
	read(L);
	cin >> sele;
	while (sele < 1 || sele>8)
	{
		cout << "你输入的选项中必须在1-8之间，请检查过后重新输入!" << endl;
		cin >> sele;
	}
	while (sele != 8)
	{
		switch (sele)
		{
		

		case 1:find(L); break;
		case 2:modify(L); break;
		case 3:add(L); break;
		case 4:del(L); break;
		case 5:save(L); break;
		case 6: new_file(L); break;
		case 7:list(L); break;
		case 8: exit(0); break;
		}
		cout <<"\t\t\t"<< "是否返回主菜单(y/n):" <<endl;
		cout<<"\t\t\t输入其他字母默认继续!"<<endl;
		cout<<"\t\t\t请输入你的选择：";
		cin >> ch;
		if (ch == 'y' || ch == 'Y')
		{
		        menu();
				cin >> sele;
		}	
	}
}
