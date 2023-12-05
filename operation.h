#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//정수는 역방향, 소수는 순방향으로 되어있음.
char integer1[10000];//역방향 
char integer2[10000];
char decimal1[10000];//순방향 
char decimal2[10000];

int integer_result[10000];//정수부 연산 결과 값 저장(역방향)
int decimal_result[10000];//소수부 연산 결과 값 저장(순방향)

char result[10000];//순방향 

int dot1,dot2;//각 수의 소수점
int result_dot;//multiply시 최종 소수점 위치 
int first_int_win,second_int_win;//minus연산시 정수부에서 더 큰 수 비교
int first_dec_win,second_dec_win;//minus연산시 소수부에서 더 큰 수 비교
int int_length,dec_length;//정수부, 소수부 길이

void plus_operation(char* first, char* second);//plus연산 후 result 값 저장
void minus_operation(char* first, char* second);//minus연산 후 result 값 저장
void multiply_operation(char* first, char* second);//multiply연산 후 result 값 저장

void cal_prepare(char* first, char* second);
void change(char *list);//연산을 위해 정방향을 역방향으로 변경 ex> 234 -> 432
void zero_add(char *first,char *second);//소수부 자리 맞추기
void convert_num(char *first,char *second);//문자형의 숫자를 숫자로 변경 ex> '2' - 48 = 2 
int integer_plus(char *first,char *second);//정수부 덧셈연산
int decimal_plus(char *first,char *second);//소수부 덧셈연산
int integer_minus(char *first,char *second);//정수부 뺄셈연산
int decimal_minus(char *first,char *second);//소수부 뺄셈연산
void minus_check();//minus연산시 정수부의 결과값과 소수부의 결과값 연산 
int multiply(char* first,char* second);//곱셈 연산
void multiply_prepare(char *first,char *second);//multiply시 소수점 제거
void initialization_char(char *list);//char형 리스트 초기화
void initialization_int(int *list);//int형 리스트 초기화