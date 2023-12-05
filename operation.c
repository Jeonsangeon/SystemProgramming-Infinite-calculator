#include "operation.h"

void plus_operation(char* first, char* second){

	initialization_char(result);
	initialization_char(integer1);
	initialization_char(integer2);
	initialization_char(decimal1);
	initialization_char(decimal2);
	initialization_int(integer_result);
	initialization_int(decimal_result);
	dot1 = 0; dot2 = 0;

    char* p = first;
    char* q = second;
    cal_prepare(p,q);

    char *ip=integer1;
	char *iq=integer2;

    //integer1, integer2의 순방향 배열을 역방향 배열로 변환
    change(ip);
	change(iq);
	zero_add(ip,iq);
    //minus연산 후 integer_result에 저장된 값의 크기 반환
	int_length=integer_plus(ip,iq);
    char *dp=decimal1;
	char *dq=decimal2;
    //decimal1, decimal2의 자리 수 맞추기
	zero_add(dp,dq);
	
	dec_length= decimal_plus(dp,dq);
	
	for (int i=0;i<int_length+dec_length+1;i++){
		if (i<int_length){
			result[i]=integer_result[int_length-1-i]+'0';
		}
		else if (i==int_length){
			result[i]='.';
		}
		else{
			result[i]=decimal_result[int_length+dec_length-i]+'0';
		}
	}

    if (result[strlen(result)-1]=='.'){
        result[strlen(result)-1]=0;
    }
}

void minus_operation(char* first, char* second){
	printf("%s %s ",first,second);
  	initialization_char(result);
	initialization_char(integer1);
	initialization_char(integer2);
	initialization_char(decimal1);
	initialization_char(decimal2);
	initialization_int(integer_result);
	initialization_int(decimal_result);
	int_length=0,dec_length=0;
    dot1=0,dot2=0;

    char* p = first;
    char* q = second;
    cal_prepare(p,q);

    char *ip=integer1;
	char *iq=integer2;
	char *dp=decimal1;
	char *dq=decimal2;
    //integer1, integer2의 순방향 배열을 역방향 배열로 변환
    change(ip);
	change(iq);

	zero_add(ip,iq);
	zero_add(dp,dq);

	dec_length=strlen(decimal1);

	multiply_prepare(ip,dp);
	multiply_prepare(iq,dq);

    //minus연산 후 integer_result에 저장된 값의 크기 반환
	int_length=integer_minus(ip,iq);//size;
	
    //minus연산 후 decimal_result에 저장된 값의 크기 반환


    //minus연산 후 정수부 결과값과 소수부 결과값을 합쳐 문자열로 result배열에 저장
	int seq=0;
	 
	int_length-=dec_length;
	//printf("%d %d %d",int_length,dec_length,seq);//1
	for (int i=0;i<int_length+dec_length+1;i++){//1 0 i<2
		if (i<int_length){//<1
			if (integer_result[i]<0){
				integer_result[i]*=-1;
				integer_result[i]+='0';
				result[i+seq]='-';
				seq++;
				result[i+seq]=integer_result[i];
			}
			else//
				result[i+seq]=integer_result[i]+'0';//0=intger_result[0]+'0';
		}
		else if (i==int_length && dec_length!=0){//1
			result[i+seq]='.';
		}
		else if (i==int_length)
			dec_length--;
		else{//1<2
			result[i+seq]=integer_result[i-1]+'0';
		}
	}
    if (result[strlen(result)-1]=='.'){
        result[strlen(result)-1]=0;
    }
}

int integer_minus(char *first,char *second){
	first_int_win=0,second_int_win=0;
	int size=strlen(first)>strlen(second)?strlen(first):strlen(second);
	for (int i=size-1;i>=0;i--){
		if (first[i]>second[i]){
			first_int_win=1;
			break;
		}
		else if (first[i]<second[i]){
			second_int_win=1;
			break;
		}
		else if (i==0)
			first_int_win=1;
	}
	if (first_int_win==1){
		for (int i=size-1;i>=0;i--){
			// if (first[i]<second[i]){
			// 	integer_result[i-1]-=1;
			// 	integer_result[i]+=10;
			// }
			integer_result[size-1-i]=first[i]-second[i];
			// printf("%c/",integer_result[size-1-i]);
		}
	}
	else if (second_int_win==1){
		for (int i=size-1;i>=0;i--){
			// if (second[i]<first[i]){
			// 	integer_result[i+1]-=1;
			// 	integer_result[i]+=10;
			// }
			integer_result[i]=second[i]-first[i];
		}
		integer_result[size-1]*=-1;
	}
	for (int i=size-1;i>=0;i--){
		if (integer_result[i]<0){
			integer_result[i-1]--;
			integer_result[i]+=10;
		}
	}

	return size;
}

void multiply_operation(char* first, char* second){

    initialization_char(result);
	initialization_char(integer1);
	initialization_char(integer2);
	initialization_char(decimal1);
	initialization_char(decimal2);
	initialization_int(integer_result);
	initialization_int(decimal_result);
	dot1 = 0; dot2 = 0;
	result_dot = 0;

    char* p = first;
    char* q = second;
    cal_prepare(p,q);

    char *ip=integer1;
	char *iq=integer2;
    char *dp=decimal1;
	char *dq=decimal2;
    
    change(ip);
	change(iq);

    multiply_prepare(ip,dp);
	multiply_prepare(iq,dq);

    //multiply연산 후 integer_result에 저장된 값의 크기 반환
	int_length = multiply(ip,iq);
    //소수점이 없는 수 연산 시 temp를 더해 결과값 자리수 맞추기

	int temp=0;
	if (strlen(first)==dot1){
		temp++;
	}
	if (strlen(second)==dot2){
		temp++;
	}
    int result_dot = strlen(first)-dot1+strlen(second)-dot2-2+temp;
    //multiply연산 후 결과값을 문자열로 result배열에 저장
    for(int i = 0; i<int_length;i++){
        if(i < int_length-result_dot){
            result[i] = integer_result[int_length-1-i]+'0';
        }
        else if(i==int_length-result_dot){
            result[i] = '.';
            result[i+1] = integer_result[int_length-1-i]+'0';
        }
        else{
            result[i+1] = integer_result[int_length-1-i]+'0';
        }
    }

	if(result[strlen(result)-1] == '.'){
		result[strlen(result)-1] = 0;
	}
    
}

void cal_prepare(char* first, char* second){
    //첫번째 수의 소수점 위치계산
    for (int i=0;i<strlen(first);i++){
		if (first[i]=='.'){
			break;
		}
		dot1++;
	}
    //두번째 수의 소수점 위치계산
	for (int i=0;i<strlen(second);i++){
		if (second[i]=='.'){
			break;
		}
		dot2++;
	}

    // 첫번째 수의 정수부 분리
	for (int i=0;i<dot1;i++){
		integer1[i]=first[i];
	}
    // 두번째 수의 정수부 분리
	for (int i=0;i<dot2;i++){
		integer2[i]=second[i];
	}

    //첫번째 숫자의 소수부 분리
	for (int i=dot1+1;i<strlen(first);i++){
		decimal1[i-dot1-1]=first[i];
	}
    //두번쨰 숫자의 소수부 분리
	for (int i=dot2+1;i<strlen(second);i++){
		decimal2[i-dot2-1]=second[i];
	}

}

void change(char *list){
	for (int i=0;i<strlen(list)/2;i++){
		char k=list[i];
		list[i]=list[strlen(list)-1-i];
		list[strlen(list)-1-i]=k;
	}
}
void zero_add(char *first,char *second){
//	printf("\nfirst : %d \nsecond : %d",strlen(first),strlen(second));
	if (strlen(first)>strlen(second)){
		for (int i=strlen(second);i<strlen(first);i++){
			second[i]='0';
		}
	}
	else if (strlen(first)<strlen(second)){
		for (int i=strlen(first);i<strlen(second);i++){
			first[i]='0';
		}
	}
}

void convert_num(char *first,char *second){
	for (int i=0;i<strlen(first);i++){
		first[i]-='0';
	}
	for (int i=0;i<strlen(second);i++){
		second[i]-='0';
	}
}
int integer_plus(char *first,char *second){
	int size=strlen(first)>strlen(second)?strlen(first):strlen(second);
	int temp;
	for (int i=0;i<size;i++){
		integer_result[i]+=first[i]+second[i]-96;
		temp=integer_result[i]/10;
		integer_result[i]%=10;
		integer_result[i+1]+=temp;
	}
	if (temp>0){
		temp=1;
	}
	
	return size+temp;
}

int decimal_plus(char *first,char *second){
	int size=strlen(first)>strlen(second)?strlen(first):strlen(second);
	int temp;
	for (int i=0;i<size;i++){
		decimal_result[i]+=first[i]+second[i]-96;
		temp=decimal_result[i]/10;
		decimal_result[i]%=10;
		decimal_result[i+1]+=temp;
	}
	if (temp>0){
		temp=1;
	}
	return size+temp;
}

int decimal_minus(char *first,char *second){
	first_dec_win=0,second_dec_win=0;
	int size=strlen(first)>strlen(second)?strlen(first):strlen(second);
	for (int i=0;i<size;i++){
		if (first[i]>second[i]){
			first_dec_win=1;
			break;
		}
		else if (first[i]<second[i]){
			second_dec_win=1;
			break;
		}
		else if (i==size-1)
			first_dec_win=1;
	}
	if (first_dec_win==1){
		for (int i=size-1;i>=0;i--){
			if (first[i]<second[i]){
				decimal_result[i-1]-=1;
				decimal_result[i]+=10;
			}
			decimal_result[i]+=first[i]-second[i];
		}
	}
	else if (second_dec_win==1){
		for (int i=size-1;i>=0;i--){
			if (second[i]<first[i]){
				decimal_result[i-1]-=1;
				decimal_result[i]+=10;
			}
			decimal_result[i]+=second[i]-first[i];
		}
//		decimal_result[0]*=-1;
	}
//	printf("\ndecimal_minus_result : ");
//	for (int i=0;i<size;i++){
//		printf("%d",decimal_result[i]);
//	}
	return size;
}

void minus_check(){
	if (first_int_win && !first_dec_win){
		integer_result[0]--;
		decimal_result[0]+=10;
		if (integer_result[0]<0){
			for (int i=0;i<int_length;i++){
				if (abs(integer_result[i])>0 && i!=0){
					for (int j=i;j>0;j--){
						integer_result[j]--;
						integer_result[j-1]+=10;
					}
					if (integer_result[0]>0)
						break;
				}	
			}
		}
		for (int i=0;i<dec_length-1;i++){
			decimal_result[i]--;
			decimal_result[i+1]=10-decimal_result[i+1];
		}
	}
	else if (!first_int_win && first_dec_win){
		integer_result[0]--;
		decimal_result[0]=10-decimal_result[0];
		if (integer_result[0]<0){
			for (int i=0;i<int_length;i++){
				if (abs(integer_result[i])>0 && i!=0){
					for (int j=i;j>0;j--){
						integer_result[j]--;
						integer_result[j-1]+=10;
					}
					if (integer_result[0]>0)
						break;
				}	
			}
		}
		for (int i=0;i<dec_length-1;i++){
			decimal_result[i]--;
			decimal_result[i+1]=10-decimal_result[i+1];
		}
	}
}

int multiply(char* first,char* second){
	int temp;
    int i, j;
	for (i=0;i<strlen(first);i++){
        for(j=0;j<strlen(second);j++){
            integer_result[i+j]+=(first[i]-48)*(second[j]-48);
    		temp=integer_result[i+j]/10;
    		integer_result[i+j]%=10;
    		integer_result[i+j+1]+=temp;
        }
    }
    i--; j--;
	if(temp>0){
		temp=1;
	}

	return i+j+temp+1;
}

void multiply_prepare(char *first,char *second){
	for (int i=strlen(first)-1;i>=0;i--){
		first[i+strlen(second)]=first[i];
	}
	for (int i=strlen(second)-1;i>=0;i--){
		first[i]=second[strlen(second)-i-1];
	}
}

void initialization_char(char *list){
	for(int i = strlen(list)-1; i>=0; i--){
		list[i] = 0;
	}
} 

void initialization_int(int *list){
	for (int i=0;i<10000;i++){
		list[i]=0;
	}
}