#include<iostream>
#include<cstring>
#define error 0
#define ok 1
#define Max_Size 100
using namespace std;

typedef int Status;
typedef struct Warehourse{
	char number[Max_Size];//������
	char name[Max_Size];//��������
	char counter[Max_Size];//��������
}WAREHOUSE;

typedef struct DuLNode
{
	WAREHOUSE data;
	struct DuLNode *prior, *next;
}DuLNode,*DuLinkList;
int number = 0;

//��ʼ������
void InitLinkList(DuLinkList &L)
{
	L = new DuLNode;
	L->next = NULL;
	L->prior = L->next;
}
//��ȡ�ֿ��ļ�
int read(DuLinkList &L)
{
	FILE *fp;
	int i;
	DuLinkList p, ptemp;//WAREHOUSE
	char tag;

	p = L;
	fp = fopen("warehouse.dat", "rb");//���ļ�
	tag = fgetc(fp);
	rewind(fp);
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
		free(ptemp);
	}
	number = i;
	fclose(fp);
	return ok;
}

//�����µĲֿ��ļ�
void save(DuLinkList &L)
{
	DuLinkList ptemp;
	FILE *fp;

	ptemp = L->next;
	if (number == 0)cout << "Ŀǰ�ֿ������ݣ�������������ݣ�";

	if ((fp = fopen("warehouse.dat", "wb+")) == NULL)
	{
		cout << "�޷��򿪴��ļ�";
		exit(0);
	}

	for (int i = 0; ptemp; i++)
	{
		fwrite(&ptemp->data, sizeof(WAREHOUSE), 1, fp);
		ptemp = ptemp->next;
	}
	fclose(fp);
	cout << "���ر���ɹ�" << endl;
}

//��ѯ�ֿⴢ�����
void find(DuLinkList &L)
{
	DuLinkList ptemp;
	char Gnumber[20];
	char Gname[20];
	char tag;//����Ƿ�Ҫ����
	int flag;
	int i;
	int record;

	ptemp = L->next;
	cout << "����������ʲô��ʽ���ң���1�ǰ��ջ����Ų��ң�2�ǰ������Ʋ��ң�";
	cin >> flag;
	if (flag == 1)
	{
		cout << "������������Ҫ�ҵĻ�����(��10λ��������)��";
		cin >> Gnumber;
		while (strlen(Gnumber) > 10)
		{
			cout << "������Ļ�������������������";
			cin >> Gnumber;
		}
		while (ptemp != NULL)
		{
			record = 1;
			if (strcmp(ptemp->data.number, Gnumber) == 0)
			{
				cout << "λ��" << record << "  " << "�����ţ�" << ptemp->data.number << "  " << "�������ƣ�" << ptemp->data.name << "����������" << ptemp->data.counter << endl;
				break;
			}
			ptemp = ptemp->next;
			record++;
		}
	}//flag==1

	else if (flag == 2)
	{
		cout << "������������Ҫ�ҵĻ�������(��10λ��ĸ����)��";
		cin >> Gname;
		while (strlen(Gname) > 10)
		{
			cout << "������Ļ���������������������";
			cin >> Gname;
		}
		while (ptemp != NULL)
		{
			record = 1;
			if (strcmp(ptemp->data.name, Gname) == 0)
			{
				cout << "λ��" << record << "  " << "�����ţ�" << ptemp->data.number << "  " << "�������ƣ�" << ptemp->data.name << "����������" << ptemp->data.counter << endl;
				break;
			}
			ptemp = ptemp->next;
			record++;
		}
		if (ptemp == NULL)cout << "�òֿ�û�и�����" << endl;
	}
}

//�޸ı��
void modify_number(WAREHOUSE &ptemp)
{
	cout << "�������µĻ����ţ�";
	cin >> ptemp.number;
	while (strlen(ptemp.number) > 10)
	{
		cout << "�������µĻ����ţ�";
		cin >> ptemp.number;
	}
	cout << "�޸ĳɹ�" << endl;
}

//�޸Ļ�������
void modify_name(WAREHOUSE &ptemp)
{
	cout << "�������µĻ������ƣ�";
	cin >> ptemp.name;
	while (strlen(ptemp.name)>10)
	{
		cout << "�������µĻ������ƣ�";
		cin >> ptemp.name;
	}
	cout << "�޸ĳɹ�" << endl;
}

//�޸Ļ�������
void modify_counter(WAREHOUSE &ptemp)
{
	cout << "�������µĻ������ƣ�";
	cin >> ptemp.counter;
	cout << "�޸ĳɹ�" << endl;
}

//ȫ���޸�
void modify_all(WAREHOUSE &ptemp)
{
	cout << "�������µĻ����ţ����ƣ�������";
	cin >>ptemp.number>> ptemp.name>>ptemp.counter;
	while (strlen(ptemp.number) > 10)
	{
		cout << "�������µĻ����ţ�";
		cin >> ptemp.number;
	}

	while (strlen(ptemp.name)>10)
	{
		cout << "�������µĻ������ƣ�";
		cin >> ptemp.name;
	}
	cout << "�޸ĳɹ�" << endl;
}

//�޸�����2
void modify_add_cin(WAREHOUSE &ptemp)
{
	int tag;

	cout << "���������޸��ĸ����ݣ�����ȫ���޸ģ����޸Ļ���������0���޸Ļ�����������1���޸Ļ�����������2��ȫ���޸�����4��";
	cin >> tag;
	switch (tag)
	{
	case 0:modify_number(ptemp); break;
	case 1:modify_name(ptemp); break;
	case 2:modify_counter(ptemp); break;
	case 3:modify_all(ptemp); break;
	}
}
//�޸�����
void modify(DuLinkList &L)
{
	char Gnumber[20];
	char Gname[20];
	char Gcounter[20];
	DuLinkList ptemp;
	bool flag = 0;

	ptemp = L;
	cout << "�����������޸ĵĻ����ţ�";
	cin >> Gnumber;
	while (strlen(Gnumber) > 10)
	{
		cout << "������ı���������������룡" << endl;
		cout << "�����������޸ĵĻ�����: ";
		cin >> Gnumber;
	}
	while (ptemp)
	{
		if (strcmp(Gnumber, ptemp->data.number) == 0)
		{
			flag = 1;
			modify_add_cin(ptemp->data);
		}
		ptemp = ptemp->next;
		if (flag == 0)cout << "������ı��û�и����ݣ�";
	}
}

//�������
void add_cin(WAREHOUSE &ptemp)
{
	cout << "����������ţ��������ƣ���������" << endl;
	cin >> ptemp.number >> ptemp.name >> ptemp.counter;
	while (strlen(ptemp.number) > 10)
	{
		cout << "����������ţ��������ƣ���������" << endl;
		cin >> ptemp.number >> ptemp.name >> ptemp.counter;
	}
	while (strlen(ptemp.name) > 10)
	{
		cout << "����������ţ��������ƣ���������" << endl;
		cin >> ptemp.number >> ptemp.name >> ptemp.counter;
	}
}
void add(DuLinkList &L)
{
	DuLinkList ptemp;
	int count;

	cout << "������������ӵĻ���������";
	cin >> count;
	while (count != 0)
	{
		if (L->next == NULL)
		{
			ptemp = new DuLNode;
			ptemp->next = L->next;
			L->next = ptemp;
			ptemp->prior = L;
			cout << "����ӻ�����Ϣ��" << endl;
			add_cin(ptemp->data);
		}
		else
		{
			ptemp = new DuLNode;
			ptemp->prior = L;
			ptemp->next = L->next;
			L->next->prior = ptemp;
			L->next = ptemp;
			cout << "����ӻ�����Ϣ��" << endl;
			add_cin(ptemp->data);
		}
		count--;
	}
}

//ɾ��������Ϣ
void del(DuLinkList &L)
{
	char Gnumber[20];
	char Gname[20];
	char Gcounter[20];
	DuLinkList ptemp;
	int tag;//����ʲô��ɾ��
	int i;
	char ch;//�Ƿ�ɾ��

	ptemp = L;
	cout << "��������Ҫ����ʲô��ɾ����������0�Ǹ��ݱ��ɾ��������1�Ǹ�������ɾ����" << endl;
	cout << "��ܰ��ʾ����������Ψһ�ģ����������п����ظ�Ŷ��" << endl;
	cin >> tag;

	if (tag == 0)
	{
		cout << "����������ɾ���Ļ����ţ�";
		cin >> Gnumber;
		for (i = 0; ptemp; i++)
		{
			if (strcmp(Gnumber, ptemp->data.number) == 0)
			{
				cout << "�Ƿ�ȷ��ɾ���û�����Ϣ��y/n��";
				cin >> ch;
				if (ch == 'y' || ch == 'Y')
				{
					cout << "��ɾ�� ��" << Gnumber << "��������Ϣ!";
					break;
				}
			}
			ptemp = ptemp->next;
		}
		//�Ҳ���
		if (ptemp == NULL || i == number)
		{
			cout << "δ���ҵ��û�����Ϣ��" << endl;
		}

		//��ĩβ�ҵ�
		if (ptemp->next == NULL)
		{
			ptemp->prior->next = ptemp->next;
		}
		//�м������ҵ�
		if (ptemp->next != NULL)
		{
			ptemp->prior->next = ptemp->next;
			ptemp->next->prior = ptemp->prior;
		}
		free(ptemp);

	}

}


