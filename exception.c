
#include "exception.h"

void Exception_Control(void)
{
    int front_bracket = 0; // '(' 개수
    int back_bracket = 0; // ')' 개수
    int operator_duplicated = 0; // 0이면 operator 없음, 1이면 operator 1개 있음(뒤에 -는 올 수 있음), 2이면 operator뒤에 -와서 다음에 아무것도 못들어옴
    bool integer = false; //마지막 입력이 정수인지 확인
    bool dot = false; //마지막입력이 소숫점인지 확인
    FILE* input = fopen("input.txt","r+"); //입력받는파일
    FILE* output = fopen("output.txt","w+"); //예외처리가 끝난 파일
    char c = fgetc(input);
    fseek(input, -1, SEEK_CUR);
    while (c != EOF){
        c = fgetc(input);
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
                operator_duplicated = 0;
                integer = true;
                fputc(c, output);
            break;

            case '0':
                switch (integer)
                {
                case true:
                    fputc(c, output);
                    operator_duplicated = 0;
                    integer = true;
                break;
                default:{
                    fseek(output, -1, SEEK_CUR);
                    char pre = fgetc(output);
                    switch (pre)
                    {
                    case '*':
                    case '-':
                    case '+':
                        {
                        char post = fgetc(input);
                        fseek(input, -1, SEEK_CUR);
                        switch (post)
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
                        break;
                        default:
                            fputc(c, output);
                            operator_duplicated = 0;
                            integer = true;
                        break;
                        }
                        }
                    break;
                    case '.':
                        fputc(c, output);
                        operator_duplicated = 0;
                        integer = true;
                    break;
                    default:
                    break;
                    }
                    }
                break;
                }
            break;

            case '+':
                switch (operator_duplicated)
                {
                    case 0:
                        fputc(c, output);
                        operator_duplicated = 1;
                        integer = false;
                        dot = false;
                    break;
                    default:
                    break;
                }
            break;

            case '-':
                switch (operator_duplicated)
                {
                    case 0:
                        fputc(c, output);
                        operator_duplicated = 1;
                        integer = false;
                        dot = false;
                        break;
                    case 1:
                    {
                        fseek(output, -1, SEEK_CUR);
                        char pre = fgetc(output);
                        switch (pre)
                        {
                        case '-':
                            fseek(output, -1, SEEK_CUR);
                            fputc('+', output);
                            operator_duplicated = 2;
                            integer = false;
                            dot = false;
                            break;
                        default:
                            fputc(c, output);
                            operator_duplicated = 2;
                            integer = false;
                            dot = false;
                            break;
                        }
                    }
                    break;
                    default://2
                    break;
                }
            break;

            case '*':
                switch (operator_duplicated)
                {
                    case 0:
                        fputc(c, output);
                        operator_duplicated = 1;
                        integer = false;
                        dot = false;
                        break;
                    default:
                        break;
                }
            break;

            case '.':
            {
                fseek(output, -1, SEEK_CUR);
                char pre = fgetc(output);
                switch (pre)
                {
                    case '(':
                    case '*':
                    case '-':
                    case '+':
                    case '\0':
                    case EOF:
                        fputc('0', output);
                        fputc(c, output);
                        operator_duplicated = 2;
                        integer = false;
                        dot = true;
                    break;
                    case ')':
                        fputc('*', output);
                        fputc('0', output);
                        fputc(c, output);
                        operator_duplicated = 2;
                        integer = false;
                        dot = true;
                    break;
                    case '.':
                        break;
                    default:
                        switch (dot)
                        {
                        case false:
                            fputc(c, output);
                            operator_duplicated = 2;
                            integer = false;
                            dot = true;
                        break;
                        default:
                        break;
                        }
                    break;
                }
            }
            break;             
                
            case '(':
            {
                fseek(output, -1, SEEK_CUR);
                char pre = fgetc(output);
                switch (pre)
                {
                case '*':
                case '-':
                case '+':
                case '(':
                    fputc(c, output);
                    front_bracket++;
                    operator_duplicated = 0;
                    integer = false;
                    dot = false;
                break;
                case '.':
                    fputc('0', output);
                    fputc('*', output);
                    fputc(c, output);
                    front_bracket++;
                    operator_duplicated = 0;
                    integer = false;
                    dot = false;
                break;
                default://0~9, )
                    fputc('*', output);
                    fputc(c, output);
                    front_bracket++;
                    operator_duplicated = 0;
                    integer = false;
                    dot = false;
                break;
                }
            }
            break;

            case ')':
                if(front_bracket > back_bracket)
                {
                    fseek(output, -1, SEEK_CUR);
                    char pre = fgetc(output);
                    switch (pre)
                    {
                    case '+':
                    case '*':
                        fseek(output, -1, SEEK_CUR);
                        fputc(c, output);
                        back_bracket++;
                        operator_duplicated = 0;
                        integer = false;
                        dot = false;
                    break;
                    case '-':
                        switch (operator_duplicated)
                        {
                        case false:
                            fseek(output, -1, SEEK_CUR);
                            fputc(c, output);
                            back_bracket++;
                            operator_duplicated = 0;
                            integer = false;
                            dot = false;
                        break;
                        default:
                            fseek(output, -2, SEEK_CUR);
                            fputc(c, output);
                            back_bracket++;
                            fputc(' ', output);
                            fseek(output, -1, SEEK_CUR);
                            operator_duplicated = 0;
                            integer = false;
                            dot = false;
                        break;
                        }
                    break;
                    case '.':
                        fseek(output, -1, SEEK_CUR);
                        fputc(c, output);
                        back_bracket++;
                        operator_duplicated = 0;
                        integer = false;
                        dot = false;
                    break;
                    case '(':
                        fseek(output, -1, SEEK_CUR);
                        fputc('*', output);
                        front_bracket--;
                    break;
                    default:// ), 0~9
                        fputc(c, output);
                        back_bracket++;
                        operator_duplicated = 0;
                        integer = false;
                        dot = false;
                    break;
                    }
                }
                else
                {
                    switch (operator_duplicated)
                    {
                    case 0:
                        fseek(output, -1, SEEK_CUR);
                        char pre = fgetc(output);
                        switch (pre)
                        {
                        case '.':
                            fseek(output, -1, SEEK_CUR);
                            fputc('*', output);
                            back_bracket++;
                            operator_duplicated = 1;
                            integer = false;
                            dot = false;
                        break;
                        default:
                            break;
                        }
                    default:
                        break;
                    }
                }
            break;

            default:
            break;
        }
        {   // )로 끝났을때 곱셈이 필요하면 넣어줌
        fseek(output, -1, SEEK_CUR);
        char pre = fgetc(output);
        switch (pre)
        {
        case ')':
        {
            char post = fgetc(input);
            fseek(input, -1, SEEK_CUR);
            switch (post)
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
                putc('*', output);
                operator_duplicated = 0;
                integer = false;
                dot = true;
            break;
            default:
            break;
            }
        }
        break;
                
        default:
            break;
        }
        }
    }
    fseek(output, -1, SEEK_END);
    char ispredicate = fgetc(output);
    switch (ispredicate)
    {
    case '+':
    case '-':
    case '*':
        fseek(output, -1, SEEK_CUR);
        fputc(EOF, output);
        fseek(output, -1, SEEK_CUR);
        break;
    default:
        break;
    }
    if(front_bracket > back_bracket)
    {
        for(int i = 0; i < front_bracket - back_bracket; i++)
        {fputc(')', output);}
    }
    fclose(input);
    fclose(output);
    FILE* result = fopen("output.txt", "r");
    char resultchar = fgetc(result);
    while (resultchar != EOF){
        printf("%c", resultchar);
        resultchar = fgetc(result);
    }
}