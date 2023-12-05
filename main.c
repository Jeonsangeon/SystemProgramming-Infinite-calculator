#include"node.h"
#include"operation.h"
#include"exception.h"
#include <sys/stat.h>

int main() {
    FILE* input = fopen("input.txt","w");
    char c;
    c = fgetc(stdin);
    while (c != EOF)
    {
        switch (c)
        {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
        case '+':
        case '-':
        case '*':
        case '.':
        case '(':
        case ')':
            fputc(c, input);
            break;
        default:
            break;
        }
        c = fgetc(stdin);
    }
    fclose(input);
    
    Exception_Control();

    node* head = (node* )malloc(sizeof(node));
    head->data = 0;
    head->next = NULL;
    FILE* ptr;
    char ch;
    // Opening file in reading mode
    ptr = fopen("output.txt", "r");
    // Printing what is written in file
    // character by character using loop.
    int k=0,p=0,insert_num=0;
    do {
        ch = fgetc(ptr);
		if (('0'<=ch && ch<='9') ||  ch=='.'){
			num[p][insert_num]=ch;
			insert_num++;
		}
		else if (42<=ch && ch<=45){
			p++;
			insert_num=0;
		}
        insert_node(head,k,ch);
        k++;
        // Checking if character is not EOF.
        // If it is EOF stop eading.
    } while (ch != EOF);
    fclose(ptr);
	int index;
	int postfix_length=store(head);
	char *e,x;
	char convert[20000];
	int seq=0;
	e = exp_;
    
    while(*e != '\0')
    {
        if(isalnum(*e))
            convert[seq++]=*e;
        else if(*e == '(')
            push(*e);
        else if(*e == ')')
        {
            while((x = pop()) != '(')
                convert[seq++]=x;
        }
        else
        {
            while(priority(stack[top]) >= priority(*e))
                convert[seq++]=pop();
            push(*e);
        }
        e++;
    }
    
    while(top != -1)
    {
        convert[seq++]=pop();
    }
    if (true){
    	int cnt=0;
    	int before=-1;
	    for (int i=0;i<strlen(convert);i++){
	    	// printf("%c",convert[i]);
	    	if ('0'<=convert[i] && convert[i]<='9'){
		    	if (before>(convert[i]-'0'))
		    		cnt++;
		    	before=convert[i]-'0';
		    	exp_int[i]=10*cnt+convert[i]-'0';
		    	before=convert[i]-'0';
		    }
		    else
		    	exp_int[i]=convert[i]-'0';
		    
		}
	}
    
	// for (int i=0;i<postfix_length;i++){
	// 	printf("%d ",exp_int[i]);
	// }
	
	for (int i=0;i<postfix_length/2;i++){
		int change_int=exp_int[i];
		exp_int[i]=exp_int[postfix_length-1-i];
		exp_int[postfix_length-1-i]=change_int;
	}
	
	/* for (int i=0;i<postfix_length;i++){
		printf("%d ",exp_int[i]);
        // if (exp_int[i]>=0){
        //     for (int j=0;j<strlen(num[exp_int[i]]);j++)
        //         printf("%c",num[exp_int[i]][j]);
        //     printf("\n");
        // }
	}
    printf("\n"); */
	for (int i=postfix_length-1;i>=0;i--){
/*         for (int j=0;j<postfix_length;j++)
            printf("%d ",exp_int[j]); */
        int temp=0;
		char first_1[10000];
        char second_1[10000];
        int first_1_minus=0,second_1_minus=0;
		if (exp_int[i]==-6 || exp_int[i]==-5 || exp_int[i]==-3){
            // printf("%d\n",exp_int[i]);

			for (int j=0;j<strlen(num[exp_int[i+1]]);j++){
                if (num[exp_int[i+1]][j]=='-'){
                    second_1_minus=1;
                    continue;
                }
                if(second_1_minus == 1){
                    second_1[j-1]=num[exp_int[i+1]][j];
                }else{
                    second_1[j]=num[exp_int[i+1]][j];
                }
			}
			for (int j=0;j<strlen(num[exp_int[i+2]]);j++){
                if (num[exp_int[i+2]][j]=='-'){
                    first_1_minus=1;
                    continue;
                }
                if(first_1_minus == 1){
                    first_1[j-1]=num[exp_int[i+2]][j];
                }else{
                    first_1[j]=num[exp_int[i+2]][j];
                }
			}
            // for (int j=0;j<postfix_length;j++){
            //     printf("%d ",exp_int[j]);
            // }
            // printf("\n");

            // '+' : -5 , '-' : -3 , '*' : -6 
            
            if (second_1_minus==0 && first_1_minus==0 && exp_int[i]==-5){//양수+양수
                plus_operation(first_1,second_1);
            }
            else if (second_1_minus==0 && first_1_minus==0 && exp_int[i]==-3){//양수-양수
                minus_operation(first_1,second_1);

            }
            else if (second_1_minus==0 && first_1_minus==0 && exp_int[i]==-6){//양수*양수
                multiply_operation(first_1,second_1);
            }
            else if (second_1_minus==1 && first_1_minus==0 && exp_int[i]==-5){//양수+음수=양수-양수
                minus_operation(first_1,second_1);
            }
            else if (second_1_minus==0 && first_1_minus==1 && exp_int[i]==-5){//음수+양수=-(양수-양수)
                minus_operation(second_1,first_1);
            }
            else if (second_1_minus==1 && first_1_minus==1 && exp_int[i]==-5){//음수+음수=음수
                plus_operation(second_1,first_1);
                temp++;
                num[exp_int[i+2]][0]='-';
            }
            else if (second_1_minus==1 && first_1_minus==0 && exp_int[i]==-3){//뺄셈 양수-음수=양수+양수
                plus_operation(first_1,second_1);// 값이 양수 
            }
            else if (second_1_minus==0 && first_1_minus==1 && exp_int[i]==-3){//p-q => 음수+음수
                plus_operation(first_1,second_1);// 값이 음수 
                temp++;
                num[exp_int[i+2]][0]='-';
            }
            else if (second_1_minus==1 && first_1_minus==1 && exp_int[i]==-3){// 음수-양수=음수+음수
                plus_operation(second_1,first_1);// 값이 음수
            }
            else if (second_1_minus==1 && first_1_minus==0 && exp_int[i]==-6){//곱셈
                multiply_operation(first_1,second_1);
                temp++;
                num[exp_int[i+2]][0]='-';
            }
            else if (second_1_minus==0 && first_1_minus==1 && exp_int[i]==-6){
                multiply_operation(first_1,second_1);
                temp++;
                num[exp_int[i+2]][0]='-';
            }
            else if (second_1_minus==1 && first_1_minus==1 && exp_int[i]==-6){
                multiply_operation(first_1,second_1);
            }
            // printf("\nhere : ");
            // for (int j=0;j<postfix_length;j++)
            //     printf("%d ",exp_int[j]);
            // i=postfix_length-1;

            for (int j=0;j<strlen(result);j++){// 값 업데이트 해주는 부분
			    num[exp_int[i+2]][j+temp]=result[j];
            }

            for (int j=i;j<postfix_length-2;j++)
                exp_int[j]=exp_int[j+2];
            postfix_length-=2;

            for (int j=strlen(first_1)-1;j>=0;j--){//초기화
                first_1[j]=0;
            }
            for (int j=strlen(second_1)-1;j>=0;j--){
                second_1[j]=0;
            }
		}
	}
    printf("ans : ");
	for (int i=0;i<strlen(num[0]);i++){
		printf("%c",num[0][i]);
	}
}