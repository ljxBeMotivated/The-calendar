#ifndef Calendar_H_ //防止重复编译，不用也可以运行
#define Calendar_H_

void menu();
void initStruct();
int showMonth(int month);
int isDay(int month, int day);
int readFile(char filename[], int month , int day );
void addEvent(char filename[], int month, int day);
void findEvent(char filename[], int month, int day);
void deleteEvent(char filename[], int month, int day, int index);
int countDay(int month, int day);
char* intToChar(int month, int day);
void addSign(char filename[], int day);
void deleteSign(char filename[], int day);
char * ensureMonth(int month);

int runnian_day(int a, int b, int c);
int is_runnian(int a);
int get_days(int year, int month, int day);
int days_of_year(int year, int month, int day);
int days_of_month(int year, int month);
void cun_last(char filename[], int a, int b, int c);

#endif
