/* splash.c */
#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 100
#define MAX_DATE_LENGTH 11

/* 날짜 형식이 yyyy-mm-dd인지 확인하는 함수 */
int is_valid_date_format(const char *date)
{
    int i;

    for (i = 0; date[i] != '\0'; i++) {
        if (i >= 10) return 0;
    }
    if (i != 10) return 0;

    for (i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            if (date[i] != '-') return 0;
        } else {
            if (date[i] < '0' || date[i] > '9') return 0;
        }
    }

    return 1;
}

/* 날짜에서 년, 월, 일을 분리해서 출력 형태로 바꾸는 함수 */
void format_date(const char *input, char *output)
{
    int i;
    int out_i = 0;

    /* 연도 복사 */
    for (i = 0; i < 4; i++) {
        output[out_i++] = input[i];
    }
    output[out_i++] = '년';
    output[out_i++] = ' ';

    /* 월 복사 */
    for (i = 5; i < 7; i++) {
        output[out_i++] = input[i];
    }
    output[out_i++] = '월';
    output[out_i++] = ' ';

    /* 일 복사 */
    for (i = 8; i < 10; i++) {
        output[out_i++] = input[i];
    }
    output[out_i++] = '일';
    output[out_i] = '\0';
}

int main(void)
{
    char name[MAX_NAME_LENGTH];
    char date[MAX_DATE_LENGTH];
    char formatted_date[30];
    int i;

    printf("[현재 날짜를 \"yyyy-mm-dd\" 형식으로 입력하세요]: ");
    if (scanf("%10s", date) != 1) {
        printf("날짜 입력 오류입니다.\n");
        return 1;
    }

    if (!is_valid_date_format(date)) {
        printf("잘못된 날짜 형식입니다.\n");
        return 1;
    }

    while ((i = getchar()) != '\n' && i != EOF) {
        /* 남은 입력 버퍼 비우기 */
    }

    printf("[당신의 이름을 입력하세요]: ");
    if (fgets(name, MAX_NAME_LENGTH, stdin) == NULL) {
        printf("이름 입력 오류입니다.\n");
        return 1;
    }

    /* 개행 문자 제거 */
    for (i = 0; name[i] != '\0'; i++) {
        if (name[i] == '\n') {
            name[i] = '\0';
            break;
        }
    }

    format_date(date, formatted_date);

    /* 스플래시 화면 출력 */
    printf("\n       [마그라테아 ver 0.1]                              \n");
    printf("   풀 한 포기 없는 황무지에서 반짝이는 행성을 만들내는 곳 마그라테아,         \n");
    printf(" 사람들이 보지 못하는 잠재력을 찾고 전문가의 손길을 더해 보석을 빗는 곳,    \n");
    printf("   마그라테아에 오신걸 환영합니다.   \n\n");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ \n");
    printf("[사용자]: %s                                   [실행 시간]:%s\n", name, formatted_date);

    return 0;
}
