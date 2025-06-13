#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMBER_COUNT 5
#define HEALTH_TEST_COUNT 7
#define INPUT_LEN 100

// 멤버 이름과 닉네임 저장 [멤버수][2][문자열길이]
char milliways_members[MEMBER_COUNT][2][30] = {
    {"김명현", "myeonghyeon"},
    {"박태훈", "taehoon"},
    {"이수진", "sujin"},
    {"최민수", "minsoo"},
    {"정하나", "hana"}
};

// 체력 테스트 항목 이름
const char *health_test_names[HEALTH_TEST_COUNT] = {
    "1마일 러닝 테스트(분)", "스피드 스프린트(초)", "푸시업(분)",
    "스쿼트(분)", "팔굽혀 펴기(분)", "수영(분)", "무게 들기(배수)"
};

// 멤버별 체력 점수 저장 [멤버수][7개 항목]
double health_scores[MEMBER_COUNT][HEALTH_TEST_COUNT] = {0};

// 문자열 앞뒤 공백 제거 함수
void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len == 0) return;
    if (str[len-1] == '\n') str[len-1] = '\0';
}

// 닉네임으로 멤버 인덱스 찾기, 없으면 -1 반환
int find_member_index_by_nickname(const char *nickname) {
    int i;
    for (i = 0; i < MEMBER_COUNT; i++) {
        if (strcmp(milliways_members[i][1], nickname) == 0) {
            return i;
        }
    }
    return -1;
}

// 쉼표로 구분된 7개 double 값 파싱하여 health_scores에 저장
int parse_and_store_health_scores(int member_idx, const char *input) {
    char temp[INPUT_LEN];
    char *token;
    int count = 0;
    double val;
    char *endptr;

    strncpy(temp, input, INPUT_LEN);
    temp[INPUT_LEN-1] = '\0';

    token = strtok(temp, ",");
    while (token != NULL && count < HEALTH_TEST_COUNT) {
        val = strtod(token, &endptr);
        if (endptr == token) {
            // 변환 실패
            return -1;
        }
        health_scores[member_idx][count] = val;
        count++;
        token = strtok(NULL, ",");
    }

    if (count != HEALTH_TEST_COUNT) {
        return -1;
    }
    return 0;
}

// 체력 상태 입력 함수
void setHealth() {
    char input[INPUT_LEN];
    int idx;
    printf("\n=== 체력 상태 입력 ===\n");
    printf("멤버 닉네임을 입력하세요: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("입력 오류\n");
        return;
    }
    trim_newline(input);

    idx = find_member_index_by_nickname(input);
    if (idx == -1) {
        printf("존재하지 않는 닉네임입니다.\n");
        return;
    }

    printf("7가지 체력 테스트 점수를 쉼표로 구분하여 입력하세요.\n");
    printf("(1마일 러닝, 스피드 스프린트, 푸시업, 스쿼트, 팔굽혀 펴기, 수영, 무게 들기)\n");
    printf("예) 12.5,15.0,3.2,4.1,2.8,10.0,1.5\n");
    printf("입력: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("입력 오류\n");
        return;
    }
    trim_newline(input);

    if (parse_and_store_health_scores(idx, input) == 0) {
        printf("체력 점수가 저장되었습니다.\n");
    } else {
        printf("입력 형식이 올바르지 않습니다. 다시 시도하세요.\n");
    }
}

// 전체 또는 특정 닉네임 체력 점수 출력
void getHealth() {
    char input[INPUT_LEN];
    int idx, i;

    printf("\n=== 체력 상태 조회 ===\n");
    printf("전체 조회는 'all' 입력, 특정 멤버 조회는 닉네임 입력: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("입력 오류\n");
        return;
    }
    trim_newline(input);

    if (strcmp(input, "all") == 0) {
        // 전체 출력
        printf("\n전체 멤버 체력 점수:\n");
        for (idx = 0; idx < MEMBER_COUNT; idx++) {
            printf("이름: %s, 닉네임: %s\n", milliways_members[idx][0], milliways_members[idx][1]);
            for (i = 0; i < HEALTH_TEST_COUNT; i++) {
                printf("  %s : %.2f\n", health_test_names[i], health_scores[idx][i]);
            }
            printf("\n");
        }
    } else {
        idx = find_member_index_by_nickname(input);
        if (idx == -1) {
            printf("존재하지 않는 닉네임입니다.\n");
            return;
        }

        printf("\n멤버 이름: %s, 닉네임: %s\n", milliways_members[idx][0], milliways_members[idx][1]);
        printf("1~7 중 조회할 체력 항목 번호 입력 (전체는 0): ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("입력 오류\n");
            return;
        }
        int sel = atoi(input);
        if (sel < 0 || sel > HEALTH_TEST_COUNT) {
            printf("잘못된 항목 번호입니다.\n");
            return;
        }
        if (sel == 0) {
            for (i = 0; i < HEALTH_TEST_COUNT; i++) {
                printf("  %s : %.2f\n", health_test_names[i], health_scores[idx][i]);
            }
        } else {
            printf("  %s : %.2f\n", health_test_names[sel-1], health_scores[idx][sel-1]);
        }
    }
}

// 훈련 메뉴 - 체력과 지식 관련 메뉴 확장
void trainingMenu() {
    char input[INPUT_LEN];
    int choice;

    while (1) {
        printf("\n=== 훈련 메뉴 ===\n");
        printf("1. 체력 상태 입력\n");
        printf("2. 체력 상태 조회\n");
        printf("0. 상위 메뉴로\n");
        printf("선택: ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("입력 오류\n");
            continue;
        }
        choice = atoi(input);

        switch (choice) {
            case 1:
                setHealth();
                break;
            case 2:
                getHealth();
                break;
            case 0:
                return;
            default:
                printf("잘못된 선택입니다.\n");
        }
    }
}

// 메인 메뉴 예시 (간략)
void mainMenu() {
    char input[INPUT_LEN];
    int choice;

    while (1) {
        printf("\n=== 메인 메뉴 ===\n");
        printf("1. 오디션 관리\n");
        printf("2. 훈련\n");
        printf("3. 데뷔\n");
        printf("0. 종료\n");
        printf("선택: ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("입력 오류\n");
            continue;
        }
        choice = atoi(input);

        switch (choice) {
            case 1:
                printf("오디션 관리 기능은 준비 중입니다.\n");
                break;
            case 2:
                trainingMenu();
                break;
            case 3:
                printf("데뷔 기능은 준비 중입니다.\n");
                break;
            case 0:
                printf("프로그램을 종료합니다.\n");
                return;
            default:
                printf("잘못된 선택입니다.\n");
        }
    }
}

int main() {
    mainMenu();
    return 0;
}
