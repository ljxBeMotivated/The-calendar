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
			printf("Please enter month��");    //�������·�
			scanf("%d", &month);
			printf("\n");
			month = showMonth(month);
			break;
		case 2:
			printf("Please enter month��");
			scanf("%d", &month);
			strcpy(filename, ensureMonth(month));
			printf("\n");
			month = showMonth(month);
			do {
				printf("Please enter date��");  //����������
				scanf("%d", &day);
				getchar();
				printf("\n");
				day = isDay(month, day);
				flag=readFile(filename, month, day);
				addEvent(filename, month, day);
				printf("Add success��\n");  //��ӳɹ�
				if(flag!=1){
					addSign(filename, day);
				}
				readFile(filename, month, day);
				printf("Whether you need to operate on another date��<Y/N>");  //�Ƿ���Ҫ�����������
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
					printf("The day was event-free ��\n");
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
				printf("Please enter the date you want to query: (for example: January 1 enter 1 1)");  //��������Ҫ��ѯ�����ڣ�(��:һ��һ������1 1���м��ÿո����)
				scanf("%d%d",&month,&day);
				day = isDay(month, day);
				getchar();
				strcpy(filename, ensureMonth(month));
				findEvent(filename, month, day);
				printf("Whether you need to operate on another date��<Y/N>");
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
			printf("Press any key to return to the main menu��\n");  //��������ص����˵�
			getchar();
			getchar();
	}
	printf("End of the program��\n");  //�������
	return 0;
}


/*
��ʼ���ṹ��
Ϊ�˱Ƚϣ��û���������ں��ļ��д��ڵ����ڱȽ�
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
���ļ�
*/
int readFile(char filename[], int month, int day) {
	int len = 0, i = 0, flag=0;
	char str[5];
	char line[512];
	FILE* fp;
	fp = fopen(filename, "r");
	if (!fp) {
		printf("File opening error��");  //�ļ��򿪴���
		exit(0);
	}
	strcpy(str, intToChar(month, day));  //�õ��û����������
	while (fgets(line, sizeof(line), fp)) {
		char* pLast = strstr(line, str);   //�ж��û�����������Ƿ����ļ���
		if (pLast != NULL) {
			flag = 1;
			pLast = pLast + 5;   //�̶�+5����Ϊ���ļ�ʱ������+�¼�����0101�¼���
			do {
				while (*pLast != '*' && *pLast != '\n') {
					len++;
					pLast++;
				}
				memset(Cal[countDay(month, day)].event[i],0,256);
				memcpy(Cal[countDay(month, day)].event[i], pLast - len, len);  //���¼��浽��Ӧ�Ľṹ����
				printf("%d.%s\n", i + 1, Cal[countDay(month, day)].event[i]);  //����¼�
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
	if (flag == 1)  //�ж��ļ����Ƿ�����û����������
		return 1;
	return 0;
	fclose(fp);
}

/*
����¼�
*/
void addEvent(char filename[],int month,int day) {
	char str[5];
	char events[128] = {'*'};
	FILE* fp;
	fp = fopen(filename, "a");
	if (!fp) {
			printf("File opening error��");
			exit(0);
	}
	strcpy(str, intToChar(month, day));
	printf("Please enter the event to add :  (press 0 to end)\n");  //������Ҫ��ӵ��¼�������0�س�������
	gets(Cal[countDay(month, day)].event[0]);
	if(Cal[countDay(month, day)].event[0][0] != '0'){
		fputs(str, fp);
		fputs(strcat(events, Cal[countDay(month, day)].event[0]), fp);
		strcpy(events, "*");
		for (int i = 1; i < 5; i++) {												//�û������¼������5��
			gets(Cal[countDay(month, day)].event[i]);
			if (Cal[countDay(month, day)].event[i][0] == '0')			//�ж�������Ƿ���0����0����ѭ����������
				break;
			//Cal[countDay(month, day)].event[i][99] = '\0';
			fputs(strcat(events, Cal[countDay(month, day)].event[i]), fp);  //д���ļ�
			strcpy(events, "*");
		}
		fputs("\n", fp);
	}
	fclose(fp);
}

/*
ɾ���¼�
*/
void deleteEvent(char filename[], int month, int day,int index) {
	//���ö�ά���齫�¼������������ҵ���Ҫ�޸ĵĵط����ڽ����޸ģ����һ��һ�е���ؽ�ȥ
	FILE* fp;
	char str[50][300] = { 0 };   //�������ļ���Ķ���
	char str1[5];		//���û����������
	char line[300];	//���ļ�һ������
	int i = 0,event = 0;	//i��ʾ��ȡ���ļ��ж��������ݣ�eventΪ�¼���ʶ�������ڼ����¼���
	int place[10];   //�������n���¼����ֵ�λ��
	int flag = 0;
	int bian=0;
	fp = fopen(filename, "r");
	if (!fp) {
		printf("File opening error��");
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
				if (event - 1 == index) {//��Ϊeventһֱ�����ˣ�������Ҫ���ж�
					int o1 = place[event - 1];
					int o2 = place[event - 2]; //o2�ǵ�index���¼��� '*'
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
	}//�Ѻ�����*�ŵ����������
	if(str[bian][1]!= ' ')
	{
		if(month>10)
			str[bian+1][0]='1';
		else
			str[bian+1][0]='0';
	}

	for (int u = 0; u < i; u++) {		//�Ѷ�ά�������ļ�
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
��ѯ�¼�
*/
void findEvent(char filename[], int month, int day) {
	int len = 0, i = 0,flag=0;
	char str[5];
	char line[512];
	FILE* fp;
	fp = fopen(filename, "r");
	if (!fp) {
		printf("File opening error ��");
		exit(0);
	}
	strcpy(str, intToChar(month, day));
	printf("The events of the day are ��\n");  //��һ����¼���
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
		printf("The day was event-free ��\n");
	fclose(fp);
}




