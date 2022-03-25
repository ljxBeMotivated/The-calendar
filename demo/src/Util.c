#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Calendar.h"
/*
菜单
*/
void menu()
{
	//system("cls");//清空屏幕
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("\n");
	printf("\t\t-------------------------------Event recording system--------------------------------\n");   //事件记录系统
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
	printf("Please enter a selection number to select an operation：");  //选择一个
}

/*
显示月历
用了引用参数，为了和主函数的month值保持一致
*/
int showMonth(int month)
{
	int count;
	char ch[128];
	char filename[100]={0};
	FILE* outfile;
	while (month < 1 || month>12)
	{
		printf("Incorrect month, please re-enter\n");   //输入月份错误，请重新输入
		scanf("%d", &month);
		getchar();
	}
	strcpy(filename, ensureMonth(month));
	outfile = fopen(filename, "r");   //以只读方式打开文件
	if (outfile == NULL)
	{
		cun_last(filename,2022,month,1);
		FILE* fp;
		fp = fopen(filename, "r");
		while (!feof(fp))                        //循环输出
		{
			for (count = 0; count < 8; count++)  //count<8表示读到第8行；第8行不能改（前8行是日历）
			{
				fgets(ch, 128, fp);  //读取一行
				if (count >= 0)
					printf("%s", ch); //输出
			}
			break;
		}
		fclose(fp);
	}
	else {
		while (!feof(outfile))                        //循环输出
			{
				for (count = 0; count < 8; count++)  //count<8表示读到第8行；第8行不能改（前8行是日历）
				{
					fgets(ch, 128, outfile);  //读取一行
					if (count >= 0)
						printf("%s", ch); //输出
				}
				break;
			}
		fclose(outfile);
	}
	printf("\n");
	return month;
}

/*
判断这个月用哪个txt文件
日历文件的路径一定要对！！！！！！不然不能打开文件
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
判断日期是否是合法的
用了引用参数。为了和主函数的day一致
*/
int isDay(int month,int day) {
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 9 || month == 11)
	{
		while (day < 1 || day>31)
		{
			printf("The date entered is incorrect. Please re-enter it ：");   //输入日期错误，请重新输入
			scanf_s("%d", &day);
			getchar();
		}
	}
	else if (month == 4 || month == 6 || month == 8 || month == 10 || month == 12)
	{
		while (day < 1 || day >30)
		{
			printf("The date entered is incorrect. Please re-enter it ：");
			scanf_s("%d", &day);
			getchar();
		}
	}
	else
	{
		while (day < 1 || day> 28)
		{
			printf("The date entered is incorrect. Please re-enter it ：");
			scanf_s("%d", &day);
			getchar();
		}
	}
	return day;
}

/*
判断这一月这一天是这一年的哪一天
为了统一结构体的下标
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
整型转字符型
当month或者day只有一位时，前面补0 即0%d
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
给日历加“+”号
封装了的，在主函数判断有无事件，有则调用这个函数
*/
void addSign(char filename[],int day) {
	FILE* outfile;
	char num1, num2='0';
	outfile = fopen(filename, "rt+");
	if (outfile == NULL)
	{
		printf("File opening error ！\n");
		exit(0);
	}
	while (fscanf(outfile, "%c", &num1) != EOF)                        //读文件
	{
		if (day > 10)
		{
			if (num1 - '0' == day % 10 && num2 - '0' == day / 10)			//拿到日期的十位个位和文件中的判断
			{
				fseek(outfile, 0, SEEK_CUR);									//文件指针偏移
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
删除“+”号
同上，主函数判断无事件则调用这个函数
*/
void deleteSign(char filename[], int day) {
	FILE* outfile;
	char num1, num2 = '0';
	outfile = fopen(filename, "rt+");
	if (outfile == NULL)
	{
		printf("File opening error ！\n");
		exit(0);
	}
	while (fscanf(outfile, "%c", &num1) != EOF)                        //读文件
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

//返回这一天从公元元年算起是第几天,算法：1.先算整年的部分：比如2018年，完整已经过了的年份有2017个，按平年算有 2017 * 365 天，但是其中闰年是366天，每个闰年少算了一天。1至2017有几个闰年呢
int get_days(int year, int month, int day)
{
	int days = days_of_year(year, month, day);
	int temp = year - 1;
	return temp * 365 + runnian_day(year, month, day) + days;
}


//返回这一天在当年是第几天
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

//返回这个月一共有多少天
int days_of_month(int year, int month)
{
	//存储平年每月的天数
	const int  month_days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month == 2 && is_runnian(year))
		return 29; // 如果是闰年2月，返回29天
	else
		return month_days[month - 1];  //正常返回
}


void cun_last(char filename[], int a, int b, int c) { //a是年，b是月份，c是天数
	int firstday_of_tmonth = get_days(a, b, 1) % 7;
	int tmonth_days = days_of_month(a, b);  //这个月一共多少天
	int i, j;

	FILE* fp;
	fp = fopen(filename, "w");
	if (!fp) {
		printf("文件打开错误！");
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
			//先打印第一天的位置
			for (j = 1; j < firstday_of_tmonth; j++) {
				fputs("       ", fp);

			}
			fputs("      1", fp);
			//如果今天是星期日，换行
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
