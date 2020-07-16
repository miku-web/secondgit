#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h> 
#define error 0
#define ok 1

typedef double Status; 
typedef struct Employee {
	char id[10];//1.职工工号	 
	char name[10];//2.职工姓名 
	double salary;//3.岗位工资 
	double wages;//4.薪级工资 
	double allowance;//5.职务津贴 
	double meritpay;//6.绩效工资 
	double shouldpay;//7.应发工资
	double tax;//8.个人所得税
	double realpay;//9.实发工资 

}EMPLOYEE; //职工结构体类型


typedef struct DuLNode
{
	EMPLOYEE data;//数据域
	struct DuLNode *prior,*next;//结点的前指针   // 结点的尾指针 
}DuLNode,*DuLinkList;
int number=0;


//初始链表 
void CreateList(DuLinkList &L)
{
	L = (DuLNode*)malloc(sizeof(DuLNode));
	L->next = NULL;
	L->prior = L->next;
}
 
//1.读取文件 
int read(DuLinkList &L)
{
	FILE *fp;
	int i;
	DuLinkList p, ptemp;
	char tag;

	p = L;
	fp = fopen("zgzggz.dat", "rb");
	tag = fgetc(fp);
	rewind(fp);
	if (tag != EOF)
	{
		
			for (i = 0; !feof(fp); i++)
			{
				ptemp = (DuLNode*)malloc(sizeof(DuLNode));
				fread(&ptemp->data, sizeof(EMPLOYEE), 1, fp);
				
				ptemp->next = p->next;
				p->next = ptemp;
				ptemp->prior = p;
				p = ptemp;	
		    }
		    p->prior->next=NULL;
            free(ptemp);
            
	}
		number = i;
		fclose(fp);
	return ok;
}

//2.保存 
void write(DuLinkList &L)
{
	DuLinkList ptemp;
	FILE *fp;

	ptemp = L->next;
	if (number == 0) printf("\t\t\t目前员工的数量为0!请添加数据");

	if ((fp = fopen("zgzggz.dat", "wb+")) == NULL)
	{
		printf("\t\t\t不能打开文件");
		exit(1);
	}

	for(int i=0;ptemp;i++)
	{
		fwrite(&ptemp->data, sizeof(EMPLOYEE), 1, fp);
		ptemp = ptemp->next;
	}
	fclose(fp);
	printf("\t\t\t保存成功!\n");
}

//8.个人所得sui
double grsds(double sum)		//个人所得税
{
	double t;
	if (sum > 100000)
		t = 29625.0 + (sum - 100000) * 0.45;
	else if (sum > 80000)
		t = 21700.0 + (sum - 80000) * 0.4;
	else if (sum > 60000)  
		t = 14625.0 + (sum - 60000) * 0.35;
	else if (sum > 40000)
		t = 8625.0 + (sum - 40000) * 0.3;
	else if (sum > 20000)
		t = 3625.0 + (sum - 20000) * 0.25;
	else if (sum > 5000)
		t = 625.0 + (sum - 5000) * 0.2;
	else if (sum > 2000)
		t = 175.0 + (sum - 2000) * 0.15;
	else if (sum > 500)
		t = 25.0 + (sum - 500) * 0.1;
	else
		t = sum * 0.05;
	return t;
} 



//输入
void modify_add_scanf(EMPLOYEE &ptemp)
{
	printf("\t\t\t工号\t姓名\t岗位工资\t薪级工资\t职务津贴\t绩效工资\n");
    printf("\t\t\t");scanf("\t\t\t%s\t%s\t%lf\t%lf\t%lf\t%lf", ptemp.id, ptemp.name, &ptemp.salary, &ptemp.wages,&ptemp.allowance, &ptemp.meritpay);
	while (strlen(ptemp.id)>10)
	{
		//printf("\t工号\t姓名\t岗位工资\t薪级工资\t职务津贴\t绩效工资\n");
		printf("\t\t\t工号\t姓名\t岗位工资\t薪级工资\t职务津贴\t绩效工资\n");
		printf("\t\t\t");scanf("\t\t\t%s\t%s\t%lf\t%lf\t%lf\t%lf", ptemp.id, ptemp.name, &ptemp.salary, &ptemp.wages,&ptemp.allowance, &ptemp.meritpay);
	}//工号大于要求 

	while (strlen(ptemp.name)>10)
	{
		//printf("\t工号\t姓名\t岗位工资\t薪级工资\t职务津贴\t绩效工资\n");
		printf("\t\t\t工号\t姓名\t岗位工资\t薪级工资\t职务津贴\t绩效工资\n");
		printf("\t\t\t");scanf("\t\t\t%s\t%s\t%lf\t%lf\t%lf\t%lf", ptemp.id, ptemp.name, &ptemp.salary, &ptemp.wages,&ptemp.allowance, &ptemp.meritpay);
	}//姓名不符合
	ptemp.shouldpay = ptemp.salary + ptemp.wages + ptemp.allowance + ptemp.meritpay;
	ptemp.tax = grsds(ptemp.shouldpay);
	ptemp.realpay = ptemp.shouldpay - ptemp.tax;
	printf("\t\t\t添加成功\n");


}

//第一个功能->查找 
void find(DuLinkList &L)
{
	DuLinkList ptemp;
	char gonghao[20]; 
	char ch;//标记是否重新输入 
    ptemp = L;
    int i;


	printf("\t\t\t请输入职工的工号：");
	scanf("\t\t\t%s", gonghao);

	while (strlen(gonghao) > 10)
	{
		printf("\t\t\t输入的工号有误，请重新输入\n");
		scanf("%s", gonghao);
	}
    //if (ptemp =)printf("该职工信息不存在\n");
	for( i=0;i<number;i++)
	{
		if (strcmp(ptemp->data.id, gonghao) == 0)
		{
			printf("\t\t工号 姓名 岗位工资 薪级工资 职务津贴 绩效工资 应发工资 个人所得税 实发工资\n");
		    printf("\t\t%s    %s\t   %.2lf\t   %.2lf\t    %.2lf     %.2lf\t %.2lf\t %.2lf \t   %.2lf\n", ptemp->data.id, ptemp->data.name, ptemp->data.salary, ptemp->data.wages,ptemp->data.allowance, ptemp->data.meritpay, ptemp->data.shouldpay, ptemp->data.tax, ptemp->data.realpay);
		        //   工号    姓名    岗位      职务      绩效      实发      应发     所得     实发  break;
		}
		ptemp = ptemp->next;
		
	}
	if (i==number)printf("该职工信息不存在\n");
	//free(ptemp);

}

//5.修改 
void modify(DuLinkList &L)
{
	char gonghao[20];
	DuLinkList ptemp;
	ptemp = L;
	bool flag =0;

	printf("\t\t\t请输入你需要修改的职工号：");
	scanf("%s", gonghao);

	while (strlen(gonghao) > 10)
	{
		printf("\t\t\t你输入的工号所对应的职工不存在，请检查过后重新输入!\n");
		printf("\t\t\t请输入所需修改的职工号:\n");
		scanf("%s", gonghao);
	}//while

	while (ptemp)
	{
		if (strcmp(gonghao, ptemp->data.id) == 0)
		{
			flag=1;
			modify_add_scanf(ptemp->data);
		}
		
		ptemp = ptemp->next;
	}
	if(flag==0)
			printf("\t\t\t你输入的工号没有对应的职工数据，请检查是否有错误!\n");
} 

//7.添加
/**************7.添加职工工资数据***********************/
void add(DuLinkList &L)
{
	DuLinkList ptemp;
	
	int count;//添加的总个数 
	

    printf("\t\t\t请输入你想添加的职工数：");
    scanf("%d",&count);
    while(count!=0)
    {
    	if (L->next == NULL)
	  {
	  	ptemp = (DuLNode*)malloc(sizeof(DuLNode));
		ptemp->next = L->next;
		L->next = ptemp;
		ptemp->prior=L;
		printf("\t\t\t请添加职工信息\n");
		modify_add_scanf(ptemp->data);
	  }
 	   else
	  {
	  	ptemp = (DuLNode*)malloc(sizeof(DuLNode));
		ptemp->prior = L;
		ptemp->next = L->next;	
		L->next->prior = ptemp;
		L->next = ptemp;
		printf("\t\t\t请添加职工信息:\n");
		modify_add_scanf(ptemp->data);
	  }
	  count--;
    }
	
}

//6.删除
 /***************删除*******************/
void del(DuLinkList &L)
{
	char gonghao[20];
	DuLinkList ptemp;
	ptemp = L;
	int i;
	char ch;

	printf("\t\t\t请输入你想删除的工号：");
		scanf("%s", gonghao);
	for (i = 0; ptemp; i++)
	{
		if (strcmp(gonghao, ptemp->data.id) == 0)
		{
			printf("\t\t\t是否确认删除该员工的所有信息（y/n)\n");
			printf("\t\t\t");scanf(" %c", &ch);
			if (ch == 'y' || ch == 'Y')
			{
				printf("\t\t\t已删除：职工%s的全部信息\n",ptemp->data.id);
				break;
			}
		}
		ptemp = ptemp->next;
	}
	//没找到
	if (ptemp == NULL || i == number)
	{
		printf("\t\t\t未找到该职工信息！\n");
			
	}
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
}

void list(DuLinkList &L)
{
	DuLinkList ptemp;
	ptemp = L->next;

	
	if(ptemp==NULL)printf("\t\t\t没有数据可浏览\n");
	while(ptemp!=NULL)
	{
		printf("\t\t工号 姓名 岗位工资 薪级工资 职务津贴 绩效工资 应发工资 个人所得税 实发工资\n");
		printf("\t\t%s    %s\t   %.2lf\t   %.2lf\t    %.2lf     %.2lf\t %.2lf\t %.2lf \t   %.2lf\n", ptemp->data.id, ptemp->data.name, ptemp->data.salary, ptemp->data.wages,ptemp->data.allowance, ptemp->data.meritpay, ptemp->data.shouldpay, ptemp->data.tax, ptemp->data.realpay);
		        //   工号    姓名    岗位      职务      绩效      实发      应发     所得     实发    
		ptemp = ptemp->next;
	}

	free(ptemp);

}

//菜单页面
void menu()
{
	system("cls");
	printf("\t\t\t*********************************************************\n");
	printf("\t\t\t************* 职工工资管理系统 **************************\n");
	printf("\t\t\t*            1-----查询职工信息                     *****\n");
	printf("\t\t\t*            2-----修改职工信息                   *******\n");
	printf("\t\t\t*            3-----添加职工信息                  ********\n");
	printf("\t\t\t*            4-----根据职工ID号删除             *********\n");
	printf("\t\t\t*            5-----保存员工信息               ***********\n");
	printf("\t\t\t*            6-----浏览全部职工信息          ************\n");
	printf("\t\t\t*            7-----退出程序                **************\n");
	printf("\t\t\t*********************************************************\n");
	printf("    \t \t\t\t  请输入您的选择:");

}

/*void PrintfAll(DuLinkList &L)
{
	DuLinkList ptemp=L;
	
	while(ptemp)
	{
		printf("%s %s %lf %lf %lf %lf\n", ptemp->data.id, ptemp->data.name, ptemp->data.salary, ptemp->data.allowance, ptemp->data.meritpay, ptemp->data.shouldpay, ptemp->data.tax, ptemp->data.realpay);
	
	}
		
}*/

//9.main
 int main()
{
	int sele;
	DuLinkList L;
	
	menu();
	CreateList(L);
	read(L);
    /*PrintfAll(L);*/ 
	
	scanf("\t\t\t%d", &sele);
	while (sele<1 || sele>7)
	{
		printf("\t\t\t你输入的选项必须在1-7之间，请检查之后重新输入\n");
		scanf("\t\t\t%d", &sele);
	}
	while(sele!=7)
	{
		switch (sele)
	    {
	      case 1:  find(L); break;
	          case 2 : modify(L); break;
	              case 3 : add(L); break;
	                case 4 : del(L); break;
	                     case 5 : write(L); break;
	                         case 6 : list(L); break;
	                             case 7 : exit(0); break;	
	    }
	    printf("\t\t\t请输入你想要进行的操作：");
	    scanf("\t\t\t%d",&sele);
	}
	
}
