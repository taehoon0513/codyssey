#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMBER_COUNT 5
#define HEALTH_TEST_COUNT 7
#define INPUT_LEN 100
#define DAYS 6
#define MAX_EXERCISE_NAME_LEN 30

// 멤버 이름과 닉네임
char milliways_members[MEMBER_COUNT][2][30] = {
    {"김명현", "myeonghyeon"},
    {"박태훈", "taehoon"},
    {"이수진", "sujin"},
    {"최민수", "minsoo"},
    {"정하나", "hana"}
};

// 운동 유형 배열
const char *exercise_types[5][3] = {
    {"러닝", "자전거", "빠른 걷기"},        // 유산소
    {"푸시업", "스쿼트", NULL},             // 전신 근력
    {"레그 프레스", "레그 컬", NULL},       // 하체 근력
    {"철봉", "풀업 바", NULL},              // 상체 근력
    {"플랭크", "크런치", NULL}              // 코어
};

const char *exercise_type_names[5] = {
    "유산소", "전신 근력", "하체 근력", "상체 근력", "코어"
};

// 멤버별 운동 루틴 저장 [멤버수][6일][운동 2개]
char member_routine[MEMBER_COUNT][DAYS][2][MAX_EXERCISE_NAME_LEN] = {{{""}}};

// 기타 기존 코드: 체력 점수, 입력함수 등은 생략 (문제 2번에서 구현한 코드 사용)

// 공통 멤버 목록 출력 함수 (보너스)
void printMemberList() {
    int i;
    printf("\n[멤버 목록]\n");
    for (i = 0; i < MEMBER_COUNT; i++) {
        printf("%d. 이름: %s, 닉네임: %s\n", i + 1, milliways_members[i][0], milliways_members[i][1]);
    }
    printf("\n");
}

// 문자열 앞뒤 개행 제거
void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len == 0) return;
    if (str[len - 1] == '\n') str[len - 1] = '\0';
}

// 멤버 이름으로 인덱스 찾기
int find_member_index_by_name(const char *name) {
    int i;
    for (i = 0; i < MEMBER_COUNT; i++) {
        if (strcmp(milliways_members[i][0], name) == 0) {
            return i;
        }
    }
    return -1;
}

// 문자열 비교용, NULL 체크된 운동 이름 출력용 헬퍼
void print_exercise(const char *ex) {
    if (ex && strlen(ex) > 0)
        printf("%s", ex);
    else
        printf("-");
}

// 운동 루틴 설정 함수
void setExerciseRoutine() {
    char input[INPUT_LEN];
    int member_idx = -1;
    int i, j;
    int core_used = 0; // 코어 운동 사용 횟수 (1회만 가능)

    printf("\n=== 기초 운동 루틴 설정 ===\n");
    printMemberList();

    printf("운동 루틴을 설정할 멤버 이름을 입력하세요: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("입력 오류\n");
        return;
    }
    trim_newline(input);

    member_idx = find_member_index_by_name(input);
    if (member_idx == -1) {
        printf("존재하지 않는 멤버 이름입니다.\n");
        return;
    }

    printf("\n--- 운동 유형 ---\n");
    for (i = 0; i < 5; i++) {
        printf("%d. %s: ", i + 1, exercise_type_names[i]);
        for (j = 0; j < 3; j++) {
            if (exercise_types[i][j] != NULL) {
                printf("%s", exercise_types[i][j]);
                if (j < 2 && exercise_types[i][j + 1] != NULL) printf(", ");
            }
        }
        printf("\n");
    }

    printf("\n[루틴 조건]\n- 월~토요일 6일간\n- 매일 유산소 운동 1개 + 근력 또는 코어 운동 1개\n- 코어 운동은 멤버당 하루 1회만 가능\n");

    for (i = 0; i < DAYS; i++) {
        char aerobic[INPUT_LEN] = "";
        char strength_or_core[INPUT_LEN] = "";
        int aerobic_valid = 0;
        int strength_core_valid = 0;

        printf("\n%d일차 운동 루틴 설정\n", i + 1);

        // 유산소 운동 입력
        while (!aerobic_valid) {
            printf("유산소 운동 중 하나 입력 (러닝, 자전거, 빠른 걷기): ");
            if (fgets(aerobic, sizeof(aerobic), stdin) == NULL) {
                printf("입력 오류\n");
                return;
            }
            trim_newline(aerobic);

            // 입력 유효성 검사: 유산소 3종 중 하나인지 확인
            for (j = 0; j < 3; j++) {
                if (strcmp(aerobic, exercise_types[0][j]) == 0) {
                    aerobic_valid = 1;
                    break;
                }
            }
            if (!aerobic_valid) {
                printf("유효하지 않은 유산소 운동입니다. 다시 입력하세요.\n");
            }
        }

        // 근력 또는 코어 운동 입력
        while (!strength_core_valid) {
            printf("근력 운동 또는 코어 운동 중 하나 입력\n");
            printf("(전신 근력: 푸시업, 스쿼트 / 하체 근력: 레그 프레스, 레그 컬 / 상체 근력: 철봉, 풀업 바 / 코어: 플랭크, 크런치): ");
            if (fgets(strength_or_core, sizeof(strength_or_core), stdin) == NULL) {
                printf("입력 오류\n");
                return;
            }
            trim_newline(strength_or_core);

            // 근력 또는 코어인지 검사
            int found = 0;
            int type_idx = -1;
            for (j = 1; j < 5; j++) {
                int k;
                for (k = 0; k < 3; k++) {
                    if (exercise_types[j][k] == NULL) continue;
                    if (strcmp(strength_or_core, exercise_types[j][k]) == 0) {
                        found = 1;
                        type_idx = j;
                        break;
                    }
                }
                if (found) break;
            }

            if (!found) {
                printf("유효하지 않은 근력 또는 코어 운동입니다. 다시 입력하세요.\n");
                continue;
            }

            // 코어 운동이면 하루 1회 제한 체크
            if (type_idx == 4) { // 코어 운동 타입
                if (core_used >= 1) {
                    printf("코어 운동은 하루 1회만 가능합니다. 다른 운동을 선택하세요.\n");
                    continue;
                } else {
                    core_used++;
                }
            }

            strength_core_valid = 1;
        }

        // 입력 완료 후 저장
        strncpy(member_routine[member_idx][i][0], aerobic, MAX_EXERCISE_NAME_LEN - 1);
        member_routine[member_idx][i][0][MAX_EXERCISE_NAME_LEN - 1] = '\0';

        strncpy(member_routine[member_idx][i][1], strength_or_core, MAX_EXERCISE_NAME_LEN - 1);
        member_routine[member_idx][i][1][MAX_EXERCISE_NAME_LEN - 1] = '\0';

        printf("%d일차 루틴 저장 완료: %s + %s\n", i + 1, member_routine[member_idx][i][0], member_routine[member_idx][i][1]);
    }

    printf("\n운동 루틴 설정이 완료되었습니다.\n");
}

// 운동 루틴 조회 함수
void getExerciseRoutine() {
    char input[INPUT_LEN];
    int member_idx;

    printf("\n=== 기초 운동 루틴 조회 ===\n");
    printMemberList();

    printf("운동 루틴을 조회할 멤버 이름을 입력하세요: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("입력 오류\n");
        return;
    }
    trim_newline(input);

    member_idx = find_member_index_by_name(input);
    if (member_idx == -1) {
        printf("존재하지 않는 멤버 이름입니다.\n");
        return;
    }

    printf("\n멤버 이름: %s, 닉네임: %s\n", milliways_members[member_idx][0], milliways_members[member_idx][1]);
    printf("월~토요일 운동 루틴:\n");

    for (int i = 0; i < DAYS; i++) {
        printf("%d일차: %s + %s\n", i + 1, member_routine[member_idx][i][0], member_routine[member_idx][i][1]);
    }
}

// 문제2의 trainingMenu 확장
void trainingMenu() {
    char input[INPUT_LEN];
    int choice;

    while (1) {
        printf("\n=== 훈련 메뉴 ===\n");
        printf("1. 체력 상태 입력\n");
        printf("2. 체력 상태 조회\n");
        printf("3. 기초 운동 루틴 설정\n");
        printf("4. 기초 운동 루틴 조회\n");
        printf("0. 상위 메뉴로\n");
        printf("선택: ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("입력 오류\n");
            continue;
        }
        choice = atoi(input);

        switch (choice) {
            case 1:
                // setHealth() 함수 구현 필요 (문제 2 참조)
                printf("체력 상태 입력 기능 호출\n");
                break;
            case 2:
                // getHealth() 함수 구현 필요 (문제 2 참조)
                printf("체력 상태 조회 기능 호출\n");
                break;
            case 3:
                setExerciseRoutine();
                break;
            case 4:
                getExerciseRoutine();
                break;
            case 0:
                return;
            default:
                printf("잘못된 선택입니다.\n");
        }
    }
}

int main() {
    trainingMenu();
    return 0;
}
