#include <stdio.h>
#include <stdlib.h>

#define MAIN_MENU_COUNT 3
#define TRAINING_MENU_COUNT 8
#define STR_LEN 50
#define INPUT_LEN 10

// 2차원 배열: 주 메뉴 (보너스 조건)
char mainMenu[MAIN_MENU_COUNT][STR_LEN] = {
    "I. 오디션 관리",
    "II. 훈련",
    "III. 데뷔"
};

// 2차원 배열: 훈련 메뉴 (보너스 조건)
char trainingMenu[TRAINING_MENU_COUNT][STR_LEN] = {
    "1. 체력과 지식",
    "2. 자기관리 및 팀워크",
    "3. 언어 및 발음",
    "4. 보컬",
    "5. 댄스",
    "6. 비주얼 및 이미지",
    "7. 연기 및 무대 퍼포먼스",
    "8. 팬 소통"
};

// 훈련 통과 상태 저장: 'P', 'F', 또는 ' '
char trainingStatus[TRAINING_MENU_COUNT] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

// 숫자인지 확인
int is_digit(char c) {
    return c >= '0' && c <= '9';
}

// 정수 문자열인지 확인
int is_numeric(const char *str) {
    int i = 0;
    while (str[i] != '\0' && str[i] != '\n') {
        if (!is_digit(str[i])) return 0;
        i++;
    }
    return i > 0;
}

// 주 메뉴 출력
void showMainMenu() {
    int i;
    printf("\n==== 프로그램 마그라테아 ====\n");
    for (i = 0; i < MAIN_MENU_COUNT; i++) {
        printf("%d. %s\n", i + 1, mainMenu[i]);
    }
    printf("0. 종료 (또는 Q/q)\n선택: ");
}

// 훈련 메뉴 출력
void showTrainingMenu() {
    int i;
    printf("\n---- 훈련 메뉴 ----\n");
    for (i = 0; i < TRAINING_MENU_COUNT; i++) {
        if (trainingStatus[i] == 'P') continue; // 이미 통과한 훈련은 제외
        if (i == 1 && trainingStatus[0] != 'P') continue; // 2번은 1번 통과 필요
        if (i >= 2 && (trainingStatus[0] != 'P' || trainingStatus[1] != 'P')) continue; // 3~8번은 1,2번 통과 필요
        printf("%d. %s\n", i + 1, trainingMenu[i]);
    }
    printf("0. 상위 메뉴로\n선택: ");
}

// 훈련 처리
void handleTraining(int idx) {
    char input[INPUT_LEN];
    printf("평가 결과를 입력하시겠습니까? (Y/N): ");
    fgets(input, INPUT_LEN, stdin);
    if (input[0] == 'Y' || input[0] == 'y') {
        printf("훈련을 마치고 인증에 통과했나요? (P/F): ");
        fgets(input, INPUT_LEN, stdin);
        if (input[0] == 'P' || input[0] == 'p') {
            trainingStatus[idx] = 'P';
            printf(">> \"%s\" 훈련을 통과했습니다.\n", trainingMenu[idx]);
        } else {
            trainingStatus[idx] = 'F';
            printf(">> \"%s\" 훈련에 실패했습니다.\n", trainingMenu[idx]);
        }
    } else {
        printf(">> 훈련 선택을 취소했습니다.\n");
    }
}

// 훈련 메뉴
void trainingMenuFunc() {
    char input[INPUT_LEN];
    int num;
    while (1) {
        showTrainingMenu();
        fgets(input, INPUT_LEN, stdin);

        if (input[0] == '0') return;

        if (!is_numeric(input)) {
            printf(">> 숫자를 입력하세요.\n");
            continue;
        }

        num = atoi(input);
        if (num < 1 || num > TRAINING_MENU_COUNT) {
            printf(">> 올바른 번호를 입력하세요.\n");
            continue;
        }

        int idx = num - 1;

        if (trainingStatus[idx] == 'P') {
            printf(">> 이미 통과한 훈련입니다.\n");
            continue;
        }

        if (idx == 1 && trainingStatus[0] != 'P') {
            printf(">> 1번 훈련을 먼저 통과해야 합니다.\n");
            continue;
        }

        if (idx >= 2 && (trainingStatus[0] != 'P' || trainingStatus[1] != 'P')) {
            printf(">> 1번과 2번 훈련을 먼저 통과해야 합니다.\n");
            continue;
        }

        handleTraining(idx);
    }
}

// 오디션 메뉴
void auditionMenu() {
    printf("\n[오디션 관리 기능은 구현 예정입니다.]\n");
}

// 데뷔 메뉴
void debutMenu() {
    printf("\n[데뷔 기능은 구현 예정입니다.]\n");
}

// 메인 함수
int main() {
    char input[INPUT_LEN];
    int choice;

    while (1) {
        showMainMenu();
        fgets(input, INPUT_LEN, stdin);

        if (input[0] == '0' || input[0] == 'Q' || input[0] == 'q' || input[0] == '\n') {
            printf("프로그램을 종료합니다.\n");
            break;
        }

        if (!is_numeric(input)) {
            printf(">> 올바른 숫자를 입력하세요.\n");
            continue;
        }

        choice = atoi(input);

        switch (choice) {
            case 1:
                auditionMenu();
                break;
            case 2:
                trainingMenuFunc();
                break;
            case 3:
                debutMenu();
                break;
            default:
                printf(">> 유효한 번호를 입력하세요.\n");
        }
    }

    return 0;
}
