#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include "Calendar.h"
#include <string.h>

struct calendar {
	int month;
	int day;
	char event[5][256];
}Cal[365];

int main()
{
	char filename[50];
	int t, quit = 0, flag = 0,index;
	char YN='N';
	int month,day;
	initStruct();
	while (1)
	{
		menu();
		scanf("%d", &t);
		switch (t)
		{
		case 1:
			printf("Please enter month：");    //请输入月份
			scanf("%d", &month);
			printf("\n");
			month = showMonth(month);
			break;
		case 2:
			printf("Please enter month：");
			scanf("%d", &month);
			strcpy(filename, ensureMonth(month));
			printf("\n");
			month = showMonth(month);
			do {
				printf("Please enter date：");  //请输入日期
				scanf("%d", &day);
				getchar();
				printf("\n");
				day = isDay(month, day);
				flag=readFile(filename, month, day);
				addEvent(filename, month, day);
				printf("Add success！\n");  //添加成功
				if(flag!=1){
					addSign(filename, day);
				}
				readFile(filename, month, day);
				printf("Whether you need to operate on another date？<Y/N>");  //是否需要操作别的日期
				scanf("%c", &YN);
				getchar();
				if(YN!= 'Y' && YN!= 'N'){
					printf("Input error please re-enter!");
					scanf("%c", &YN);
					getchar();
				}
			} while (YN == 'Y');
			break;
		case 3:
			flag=0;
			printf("Please enter month:");
			scanf("%d", &month);
			strcpy(filename, ensureMonth(month));
			printf("\n");
			showMonth(month);
			do {
				printf("Please enter date:");
				scanf("%d", &day);
				getchar();
				printf("\n");
				isDay(month, day);
				flag=readFile(filename, month, day);
				if(flag==0){
					printf("The day was event-free ！\n");
					break;
				}
				do {
					printf("Please enter the events you want to delete :(that is, 1, 2, 3)");
					scanf("%d", &index);
					getchar();
					deleteEvent(filename, month, day, index);
					printf("Deleted successfully!\n");
					flag = readFile(filename, month, day);
					if (flag == 0)
						deleteSign(filename, day);
					printf("Do you want to continue to delete it? <Y/N>");
					scanf("%c", &YN);
					getchar();
					if(YN!= 'Y' && YN!= 'N'){
						printf("Input error please re-enter!");
						scanf("%c", &YN);
						getchar();
					}
				} while (YN == 'Y');
				printf("Do you need to manipulate other dates?<Y/N>");
				scanf("%c", &YN);
				if(YN!= 'Y' && YN!= 'N'){
					printf("Input error please re-enter!");
					scanf("%c", &YN);
					getchar();
				}
			} while (YN == 'Y');
			break;
		case 4:
			do {
				printf("Please enter the date you want to query: (for example: January 1 enter 1 1)");  //请输入需要查询的日期：(如:一月一号输入1 1；中间用空格隔开)
				scanf("%d%d",&month,&day);
				day = isDay(month, day);
				getchar();
				strcpy(filename, ensureMonth(month));
				findEvent(filename, month, day);
				printf("Whether you need to operate on another date？<Y/N>");
				scanf("%c", &YN);
				if(YN!= 'Y' && YN!= 'N'){
					printf("Input error please re-enter!");
					scanf("%c", &YN);
					getchar();
				}
			} while (YN == 'Y');
			break;
		case 5:
			quit = 1;
			break;
		}
		if (quit == 1)
				break;
			printf("Press any key to return to the main menu！\n");  //按任意键回到主菜单
			getchar();
			getchar();
	}
	printf("End of the program！\n");  //程序结束
	return 0;
}


/*
初始化结构体
为了比较，用户输入的日期和文件中存在的日期比较
*/
void initStruct()
{
	for (int i = 1; i < 13; i++)
	{
		if (i == 1 || i == 3 || i == 5 || i == 7 || i == 9 || i == 11)
		{
			for (int j = 1; j < 32; j++) {
				Cal[countDay(i, j)].month = i;
				Cal[countDay(i, j)].day = j;
			}
		}
		else if (i == 4 || i == 6 || i == 8 || i == 10 || i == 12) {
			for (int j = 1; j < 31; j++) {
				Cal[countDay(i, j)].month = i;
				Cal[countDay(i, j)].day = j;
			}
		}
		else {
			for (int j = 1; j < 29; j++) {
				Cal[countDay(i, j)].month = 2;
				Cal[countDay(i, j)].day = j;
			}
		}
	}
}

/*
读文件
*/
int readFile(char filename[], int month, int day) {
	int len = 0, i = 0, flag=0;
	char str[5];
	char line[512];
	FILE* fp;
	fp = fopen(filename, "r");
	if (!fp) {
		printf("File opening error！");  //文件打开错误
		exit(0);
	}
	strcpy(str, intToChar(month, day));  //得到用户输入的日期
	while (fgets(line, sizeof(line), fp)) {
		char* pLast = strstr(line, str);   //判断用户输入的日期是否在文件中
		if (pLast != NULL) {
			flag = 1;
			pLast = pLast + 5;   //固定+5；因为存文件时是日期+事件（即0101事件）
			do {
				while (*pLast != '*' && *pLast != '\n') {
					len++;
					pLast++;
				}
				memset(Cal[countDay(month, day)].event[i],0,256);
				memcpy(Cal[countDay(month, day)].event[i], pLast - len, len);  //把事件存到对应的结构体中
				printf("%d.%s\n", i + 1, Cal[countDay(month, day)].event[i]);  //输出事件
				i++;
				if (*pLast == '*')
				{
					len = 0;
					pLast++;
				}
			} while (*pLast != '\n');
			len = 0;
		}
		memset(line,0,512);
	}
	if (flag == 1)  //判断文件中是否存在用户输入的日期
		return 1;
	return 0;
	fclose(fp);
}

/*
添加事件
*/
void addEvent(char filename[],int month,int day) {
	char str[5];
	char events[128] = {'*'};
	FILE* fp;
	fp = fopen(filename, "a");
	if (!fp) {
			printf("File opening error！");
			exit(0);
	}
	strcpy(str, intToChar(month, day));
	printf("Please enter the event to add :  (press 0 to end)\n");  //请输入要添加的事件：（按0回车结束）
	gets(Cal[countDay(month, day)].event[0]);
	if(Cal[countDay(month, day)].event[0][0] != '0'){
		fputs(str, fp);
		fputs(strcat(events, Cal[countDay(month, day)].event[0]), fp);
		strcpy(events, "*");
		for (int i = 1; i < 5; i++) {												//用户输入事件，最多5条
			gets(Cal[countDay(month, day)].event[i]);
			if (Cal[countDay(month, day)].event[i][0] == '0')			//判断输入的是否是0，是0跳出循环。即结束
				break;
			//Cal[countDay(month, day)].event[i][99] = '\0';
			fputs(strcat(events, Cal[countDay(month, day)].event[i]), fp);  //写入文件
			strcpy(events, "*");
		}
		fputs("\n", fp);
	}
	fclose(fp);
}

/*
删除事件
*/
void deleteEvent(char filename[], int month, int day,int index) {
	//先用二维数组将事件读出来，在找到需要修改的地方，在进行修改，最后一行一行的输回进去
	FILE* fp;
	char str[50][300] = { 0 };   //用来存文件里的东西
	char str1[5];		//存用户输入的日期
	char line[300];	//存文件一行数据
	int i = 0,event = 0;	//i表示读取了文件中多少行数据，event为事件标识符（即第几个事件）
	int place[10];   //用来存第n个事件出现的位置
	int flag = 0;
	int bian=0;
	fp = fopen(filename, "r");
	if (!fp) {
		printf("File opening error！");
		exit(0);
	}
	while (fgets(line, sizeof(line), fp)) {
		for (int k = 0; k < 300; k++) {
			if (line[k] == '\n')
				break;
			str[i][k] = line[k];
		}
		i++;
	}
	strcpy(str1, intToChar(month, day));
	for (int k = 0; k < i; k++) {
		if (str[k][0] == str1[0] && str[k][1] == str1[1] && str[k][2] == str1[2] && str[k][3] == str1[3]) {

			for (int j = 4; j < 300; j++) {
				if (str[k][j] == '*') {
					place[event] = j;
					event++;
				}

				if (str[k][j] == '\0' && str[k][j+1] == '\0' ) {
					flag++;
					if (flag == 2) {
						event--;
						break;
					}
					place[event] = j;
					event++;
				}
				if (event - 1 == index) {//因为event一直不变了，所以需要后判断
					int o1 = place[event - 1];
					int o2 = place[event - 2]; //o2是第index个事件的 '*'
					for (j = j - 1; j < 300; j++) {
						str[k][o2++] = str[k][o1];
						str[k][o1++] = NULL;
					}
					bian=k;
					break;
				}

			}
			//printf("\n");
			flag = 0;
		}
	}
	fclose(fp);
	fp = fopen(filename, "w");
	for (int k = 0; k < i; k++) {
		if (str[k][0] == str1[0] && str[k][1] == str1[1] && str[k][2] == str1[2] && str[k][3] == str1[3] && str[k][4] != '*') {
			for (int j = 0; j < 300; j++) {
				str[k][j] = NULL;
			}
		}
	}//把后面无*号的整行清除掉
	if(str[bian][1]!= ' ')
	{
		if(month>10)
			str[bian+1][0]='1';
		else
			str[bian+1][0]='0';
	}

	for (int u = 0; u < i; u++) {		//把二维数组存回文件
		for (int j = 0; j < 300; j++) {
			if (str[u][j] == '\0' && str[u][j+1] == '\0')
				break;

			fputc(str[u][j], fp);
		}
		fputc('\n', fp);
	}
	fclose(fp);
}

/*
查询事件
*/
void findEvent(char filename[], int month, int day) {
	int len = 0, i = 0,flag=0;
	char str[5];
	char line[512];
	FILE* fp;
	fp = fopen(filename, "r");
	if (!fp) {
		printf("File opening error ！");
		exit(0);
	}
	strcpy(str, intToChar(month, day));
	printf("The events of the day are ：\n");  //这一天的事件有
	while (fgets(line, sizeof(line), fp)) {
		char* pLast = strstr(line, str);
		if (pLast != NULL) {
			flag = 1;
			pLast = pLast + 5;
			do {
				while (*pLast != '*' && *pLast != '\n') {
					len++;
					pLast++;
				}
				memcpy(Cal[countDay(month, day)].event[i], pLast - len, len);
				printf("%d.%s\n", i + 1, Cal[countDay(month, day)].event[i]);
				i++;
				if (*pLast == '*')
				{
					len = 0;
					pLast++;
				}
			} while (*pLast != '\n');
			len = 0;
		}
	}if (flag == 0)
		printf("The day was event-free ！\n");
	fclose(fp);
}




