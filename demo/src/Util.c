#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Calendar.h"
/*
�˵�
*/
void menu()
{
	//system("cls");//�����Ļ
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("\n");
	printf("\t\t-------------------------------Event recording system--------------------------------\n");   //�¼���¼ϵͳ
	printf("\n");
	printf("\n");
	printf("\t\t\t\t\t       1  Display month calender\n");
	printf("\n");
	printf("\t\t\t\t\t       2  Add events\n");
	printf("\n");
	printf("\t\t\t\t\t       3  Delete events\n");
	printf("\n");
	printf("\t\t\t\t\t       4  Inquire events\n");
	printf("\n");
	printf("\t\t\t\t\t       5  Quit\n");
	printf("\n");
	printf("\t\t----------------------------------------------------------------------------\n");
	printf("Please enter a selection number to select an operation��");  //ѡ��һ��
}

/*
��ʾ����
�������ò�����Ϊ�˺���������monthֵ����һ��
*/
int showMonth(int month)
{
	int count;
	char ch[128];
	char filename[100]={0};
	FILE* outfile;
	while (month < 1 || month>12)
	{
		printf("Incorrect month, please re-enter\n");   //�����·ݴ�������������
		scanf("%d", &month);
		getchar();
	}
	strcpy(filename, ensureMonth(month));
	outfile = fopen(filename, "r");   //��ֻ����ʽ���ļ�
	if (outfile == NULL)
	{
		cun_last(filename,2022,month,1);
		FILE* fp;
		fp = fopen(filename, "r");
		while (!feof(fp))                        //ѭ�����
		{
			for (count = 0; count < 8; count++)  //count<8��ʾ������8�У���8�в��ܸģ�ǰ8����������
			{
				fgets(ch, 128, fp);  //��ȡһ��
				if (count >= 0)
					printf("%s", ch); //���
			}
			break;
		}
		fclose(fp);
	}
	else {
		while (!feof(outfile))                        //ѭ�����
			{
				for (count = 0; count < 8; count++)  //count<8��ʾ������8�У���8�в��ܸģ�ǰ8����������
				{
					fgets(ch, 128, outfile);  //��ȡһ��
					if (count >= 0)
						printf("%s", ch); //���
				}
				break;
			}
		fclose(outfile);
	}
	printf("\n");
	return month;
}

/*
�ж���������ĸ�txt�ļ�
�����ļ���·��һ��Ҫ�ԣ�������������Ȼ���ܴ��ļ�
*/
char *ensureMonth(int month) {
	static char filename[100];
	switch (month)
	{
	case 1:
		strcpy(filename, "January.txt");
		return filename;
		break;
	case 2:
		strcpy(filename, "February.txt");
		return filename;
		break;
	case 3:
		strcpy(filename, "March.txt");
		return filename;
		break;
	case 4:
		strcpy(filename, "April.txt");
		return filename;
		break;
	case 5:
		strcpy(filename, "May.txt");
		return filename;
		break;
	case 6:
		strcpy(filename, "June.txt");
		return filename;
		break;
	case 7:
		strcpy(filename, "July.txt");
		return filename;
		break;
	case 8:
		strcpy(filename, "August.txt");
		return filename;
		break;
	case 9:
		strcpy(filename, "September.txt");
		return filename;
		break;
	case 10:
		strcpy(filename, "October.txt");
		return filename;
		break;
	case 11:
		strcpy(filename, "November.txt");
		return filename;
		break;
	case 12:
		strcpy(filename, "December.txt");
		return filename;
		break;
	}
}

/*
�ж������Ƿ��ǺϷ���
�������ò�����Ϊ�˺���������dayһ��
*/
int isDay(int month,int day) {
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 9 || month == 11)
	{
		while (day < 1 || day>31)
		{
			printf("The date entered is incorrect. Please re-enter it ��");   //�������ڴ�������������
			scanf_s("%d", &day);
			getchar();
		}
	}
	else if (month == 4 || month == 6 || month == 8 || month == 10 || month == 12)
	{
		while (day < 1 || day >30)
		{
			printf("The date entered is incorrect. Please re-enter it ��");
			scanf_s("%d", &day);
			getchar();
		}
	}
	else
	{
		while (day < 1 || day> 28)
		{
			printf("The date entered is incorrect. Please re-enter it ��");
			scanf_s("%d", &day);
			getchar();
		}
	}
	return day;
}

/*
�ж���һ����һ������һ�����һ��
Ϊ��ͳһ�ṹ����±�
*/
int countDay(int month, int day)
{
	int a = 0;
	switch (month - 1)
	{
	case 11:a += 30;
	case 10:a += 31;
	case 9:a += 30;
	case 8:a += 31;
	case 7:a += 31;
	case 6:a += 30;
	case 5:a += 31;
	case 4:a += 30;
	case 3:a += 31;
	case 2:a += 28;
	case 1:a += 31; break;
	}
	a += day;
	return a;
}

/*
����ת�ַ���
��month����dayֻ��һλʱ��ǰ�油0 ��0%d
*/
char* intToChar(int month, int day)
{
	static char str1[5];
	char str2[3];
	if (month < 10) {
		sprintf(str1, "0%d", month);
	}
	else {
		sprintf(str1, "%d", month);
	}
	if (day < 10) {
		sprintf(str2, "0%d", day);
		strcat(str1, str2);
	}
	else {
		sprintf(str2, "%d", day);
		strcat(str1, str2);
	}
	return str1;
}

/*
�������ӡ�+����
��װ�˵ģ����������ж������¼�����������������
*/
void addSign(char filename[],int day) {
	FILE* outfile;
	char num1, num2='0';
	outfile = fopen(filename, "rt+");
	if (outfile == NULL)
	{
		printf("File opening error ��\n");
		exit(0);
	}
	while (fscanf(outfile, "%c", &num1) != EOF)                        //���ļ�
	{
		if (day > 10)
		{
			if (num1 - '0' == day % 10 && num2 - '0' == day / 10)			//�õ����ڵ�ʮλ��λ���ļ��е��ж�
			{
				fseek(outfile, 0, SEEK_CUR);									//�ļ�ָ��ƫ��
				fprintf(outfile, "%c", '+');
				break;
			}
		}
		else
		{
			if (num1 - '0' == day)
			{
				fseek(outfile, 0, SEEK_CUR);
				fprintf(outfile, "%c", '+');
				break;
			}
		}
		num2 = num1;
	}
	fclose(outfile);
}

/*
ɾ����+����
ͬ�ϣ��������ж����¼�������������
*/
void deleteSign(char filename[], int day) {
	FILE* outfile;
	char num1, num2 = '0';
	outfile = fopen(filename, "rt+");
	if (outfile == NULL)
	{
		printf("File opening error ��\n");
		exit(0);
	}
	while (fscanf(outfile, "%c", &num1) != EOF)                        //���ļ�
	{
		if (day > 10)
		{
			if (num1 - '0' == day % 10 && num2 - '0' == day / 10)
			{
				fseek(outfile, 0, SEEK_CUR);
				fprintf(outfile, "%c", ' ');
				break;
			}
		}
		else
		{
			if (num1 - '0' == day)
			{
				fseek(outfile, 0, SEEK_CUR);
				fprintf(outfile, "%c", ' ');
				break;
			}
		}
		num2 = num1;
	}
	fclose(outfile);
}

int runnian_day(int a, int b, int c) {
	int sum = 0;
	int i;
	for (i = 1; i <= a - 1; i++) {
		if (is_runnian(i)) {
			sum++;
		}
	}
	return sum;
}

int is_runnian(int a) {
	if ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) {
		return 1;
	}
	else {
		return 0;
	}
}

//������һ��ӹ�ԪԪ�������ǵڼ���,�㷨��1.��������Ĳ��֣�����2018�꣬�����Ѿ����˵������2017������ƽ������ 2017 * 365 �죬��������������366�죬ÿ������������һ�졣1��2017�м���������
int get_days(int year, int month, int day)
{
	int days = days_of_year(year, month, day);
	int temp = year - 1;
	return temp * 365 + runnian_day(year, month, day) + days;
}


//������һ���ڵ����ǵڼ���
int days_of_year(int year, int month, int day)
{
	int i;
	int days = 0;
	for (i = 1; i < month; i++)
	{
		days += days_of_month(year, i);

	}
	return days + day;
}

//���������һ���ж�����
int days_of_month(int year, int month)
{
	//�洢ƽ��ÿ�µ�����
	const int  month_days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month == 2 && is_runnian(year))
		return 29; // ���������2�£�����29��
	else
		return month_days[month - 1];  //��������
}


void cun_last(char filename[], int a, int b, int c) { //a���꣬b���·ݣ�c������
	int firstday_of_tmonth = get_days(a, b, 1) % 7;
	int tmonth_days = days_of_month(a, b);  //�����һ��������
	int i, j;

	FILE* fp;
	fp = fopen(filename, "w");
	if (!fp) {
		printf("�ļ��򿪴���");
		exit(0);
	}

	fputs("               ", fp);
	switch (b)
	{
	case 1: fputs("January\n", fp);    break;
	case 2: fputs("February\n", fp);    break;
	case 3: fputs("March\n", fp);    break;
	case 4: fputs("April\n", fp);    break;
	case 5: fputs("May\n", fp);    break;
	case 6: fputs("June\n", fp);    break;
	case 7: fputs("July\n", fp);    break;
	case 8: fputs("August\n", fp);    break;
	case 9: fputs("September\n", fp);    break;
	case 10: fputs("October\n", fp);    break;
	case 11: fputs("November\n", fp);    break;
	case 12: fputs("December\n", fp);    break;
	default: printf("Bad input of month, please enter a right month.\n"); return;
	}
	fputs("    Mon    Tue    Wed    Thu    Fri    Sat    Sun", fp);
	fputs("\n", fp);
	for (i = 1; i <= tmonth_days; i++) {
		if (i == 1) {
			//�ȴ�ӡ��һ���λ��
			for (j = 1; j < firstday_of_tmonth; j++) {
				fputs("       ", fp);

			}
			fputs("      1", fp);
			//��������������գ�����
			if (firstday_of_tmonth == 7)
				fputs("\n", fp);
			continue;
		}
		if (i >= 10) {
			int di = i % 10;
			int gao = i / 10;
			char a[10] = { '\0 ','\0 ','\0 ','\0 ','\0 ',gao + '0' ,di + '0' };
			fputs(a, fp);
		}
		else
		{
			char a[10] = { '\0 ','\0 ','\0 ','\0 ','\0 ','\0 ',i + '0' };
			fputs(a, fp);
		}
		if (((firstday_of_tmonth + i - 1) % 7 == 0) || (i == tmonth_days)) {
			fputs("\n", fp);
		}
	}
	fputs("\n", fp);
	fputs("\n", fp);
	fclose(fp);
}
