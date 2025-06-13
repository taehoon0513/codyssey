/* rememberme.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMORIAL 6
#define MAX_ROLLINGPP 20
#define MAX_STR_LEN 256

/* memorial##_arr 불합격 후보자 정보 (이름, 메일주소 등 쉼표 구분 문자열) */
/* 문제3 후보자 데이터 중 불합격자만 예시로 3명 설정 */
/* 불합격 후보자 데이터는 고정(수정 불가) */
const char memorial01_arr[MAX_MEMORIAL][MAX_STR_LEN] = {
    "Kim Minsoo,minsoo@example.com",
    "Choi Hana,hana.choi@example.com",
    "Park Joon,joonpark@example.com",
    "", "", "" /* 나머지는 빈 문자열로 채움 */
};

/* 롤링페이퍼 메시지 저장용 배열 "[name]: [message]" 형식의 JSON 문자열 */
char rollingpp01_arr[MAX_ROLLINGPP][MAX_STR_LEN] = {""};

/* 합격자 이름 저장 (최대 MAX_ROLLINGPP 명, 각 이름 최대 30자) */
char passed_candidates[MAX_ROLLINGPP][31] = {""};
int passed_count = 0;

/* 함수 원형 */
void input_passing_candidates(void);
void input_rolling_messages(void);
int select_failed_candidate(void);
void print_messages_for_failed(int idx);
void send_mail_option(int idx);

int main(void)
{
    int choice, fail_idx;

    /* 1. 합격자 이름 입력 */
    input_passing_candidates();

    /* 2. 합격자가 쓴 롤링페이퍼 메시지 입력 */
    input_rolling_messages();

    /* 3. 불합격 후보자 선택 후 메시지 조회 및 메일 발송 */
    while (1)
    {
        printf("\n=== 불합격 후보자 롤링페이퍼 조회 ===\n");
        fail_idx = select_failed_candidate();
        if (fail_idx < 0)
        {
            printf("프로그램 종료합니다.\n");
            break;
        }

        print_messages_for_failed(fail_idx);
        send_mail_option(fail_idx);
    }

    return 0;
}

/* 합격자 이름 입력 함수 */
void input_passing_candidates(void)
{
    char temp[31];
    printf("합격자 이름을 입력하세요. (종료는 빈 줄)\n");
    while (passed_count < MAX_ROLLINGPP)
    {
        printf("합격자 #%d 이름: ", passed_count + 1);
        if (fgets(temp, sizeof(temp), stdin) == NULL) break;

        /* 개행문자 제거 */
        if (temp[0] == '\n') break;
        temp[strcspn(temp, "\n")] = 0;

        if (strlen(temp) == 0) break;

        /* 저장 */
        strncpy(passed_candidates[passed_count], temp, 30);
        passed_candidates[passed_count][30] = '\0';

        passed_count++;
    }
}

/* 합격자 별 롤링페이퍼 메시지 입력 */
void input_rolling_messages(void)
{
    int i;
    char message[MAX_STR_LEN];
    int msg_count = 0;

    printf("\n=== 합격자들의 롤링페이퍼 메시지 작성 ===\n");
    for (i = 0; i < passed_count; i++)
    {
        printf("합격자 %s 에게 메시지를 입력하세요: ", passed_candidates[i]);
        if (fgets(message, sizeof(message), stdin) == NULL) break;

        /* 개행 제거 */
        message[strcspn(message, "\n")] = 0;

        if (strlen(message) == 0) continue;

        /* "[name]: [message]" JSON 문자열 생성 */
        snprintf(rollingpp01_arr[msg_count], MAX_STR_LEN, "{\"name\":\"%s\", \"message\":\"%s\"}", passed_candidates[i], message);
        msg_count++;

        if (msg_count >= MAX_ROLLINGPP) break;
    }
}

/* 불합격 후보자 선택(번호 입력) */
int select_failed_candidate(void)
{
    int i, choice;
    int available_count = 0;

    printf("\n불합격 후보자 명단:\n");
    for (i = 0; i < MAX_MEMORIAL; i++)
    {
        if (memorial01_arr[i][0] != '\0')
        {
            printf(" %d. %s\n", i + 1, memorial01_arr[i]);
            available_count++;
        }
    }
    if (available_count == 0)
    {
        printf("불합격 후보자가 없습니다.\n");
        return -1;
    }

    printf("메시지를 조회할 후보자 번호를 입력하세요(종료: 0): ");
    if (scanf("%d", &choice) != 1) {
        while(getchar() != '\n'); /* 입력 버퍼 비우기 */
        return -1;
    }
    while(getchar() != '\n'); /* 입력 버퍼 비우기 */

    if (choice == 0) return -1;
    if (choice < 1 || choice > MAX_MEMORIAL || memorial01_arr[choice - 1][0] == '\0') {
        printf("잘못된 선택입니다.\n");
        return select_failed_candidate();
    }

    return choice - 1;
}

/* 불합격 후보자에게 온 메시지 출력 */
void print_messages_for_failed(int idx)
{
    int i;
    char name[MAX_STR_LEN];
    char *comma_pos;

    /* memorial01_arr[idx] 에서 이름 추출 (쉼표 이전 부분) */
    strncpy(name, memorial01_arr[idx], MAX_STR_LEN - 1);
    name[MAX_STR_LEN - 1] = '\0';
    comma_pos = strchr(name, ',');
    if (comma_pos != NULL) *comma_pos = '\0';

    printf("\n%s 후보자에게 온 롤링페이퍼 메시지 목록:\n", name);

    /* 메시지 중 name이랑 비교해 출력 */
    for (i = 0; i < MAX_ROLLINGPP; i++)
    {
        if (rollingpp01_arr[i][0] == '\0') continue;

        /* rollingpp01_arr[i] JSON에서 name 비교 (단순 strstr로 간략 비교) */
        if (strstr(rollingpp01_arr[i], name) != NULL)
        {
            printf(" - %s\n", rollingpp01_arr[i]);
        }
    }
}

/* 메일 전송 여부 선택 및 처리 */
void send_mail_option(int idx)
{
    char input[10];
    int send_flag;
    char email[MAX_STR_LEN];
    char *comma_pos;

    /* memorial01_arr[idx] 에서 메일 주소 추출 (쉼표 뒤 부분) */
    strncpy(email, memorial01_arr[idx], MAX_STR_LEN - 1);
    email[MAX_STR_LEN - 1] = '\0';
    comma_pos = strchr(email, ',');
    if (comma_pos != NULL) 
    {
        /* 쉼표 다음 문자부터 메일주소 */
        strncpy(email, comma_pos + 1, MAX_STR_LEN - 1);
        email[MAX_STR_LEN - 1] = '\0';

        /* 앞뒤 공백 제거 */
        while(email[0] == ' ') memmove(email, email+1, strlen(email));
        /* 뒤 공백 제거 */
        while(strlen(email) > 0 && (email[strlen(email)-1] == ' ' || email[strlen(email)-1] == '\n'))
            email[strlen(email)-1] = '\0';
    }
    else
    {
        /* 메일 주소 없으면 */
        strcpy(email, "없음");
    }

    printf("이 후보자에게 메일을 전송하시겠습니까? (1: 예, 0: 아니오): ");
    if (fgets(input, sizeof(input), stdin) == NULL) return;

    send_flag = atoi(input);

    if (send_flag == 1)
    {
        printf("메일 주소: %s\n", email);
        printf("메일을 전송했습니다.\n");
    }
    else
    {
        printf("메일 전송을 취소했습니다.\n");
    }
}
