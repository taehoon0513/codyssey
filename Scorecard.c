#include <stdio.h>
#include <stdlib.h>

#define NUM_CANDIDATES 6
#define NUM_FIELDS 5
#define MAX_NAME_LEN 30
#define MAX_FIELD_LEN 15

const char* field_names[NUM_FIELDS] = {"음악", "댄스", "보컬", "비주얼", "전달력"};

const char* candidate_names[NUM_CANDIDATES] = {
    "박지연", "Ethan Smith", "Helena Silva", "Liam Wilson", "김서준", "Emily Zhang"
};

int candidate_ids[NUM_CANDIDATES] = {123456, 234567, 345678, 456789, 567890, 678901};

// 후보자별 점수 배열: [음악, 댄스, 보컬, 비주얼, 전달력, 총점]
int scoring_sheet[NUM_CANDIDATES][NUM_FIELDS + 1] = {0};

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int get_field_index(const char* field) {
    int i;
    for (i = 0; i < NUM_FIELDS; i++) {
        int j = 0;
        int match = 1;
        while (field[j] != '\0' && field_names[i][j] != '\0') {
            if (field[j] != field_names[i][j]) {
                match = 0;
                break;
            }
            j++;
        }
        if (field[j] != '\0' || field_names[i][j] != '\0') {
            match = 0;
        }
        if (match) return i;
    }
    return -1;
}

void remove_newline(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
}

void input_scores() {
    char judge_name[MAX_NAME_LEN];
    char field[MAX_FIELD_LEN];
    int field_index;

    while (1) {
        printf("####################################\n");
        printf("#       오디션 심사 결과 입력       #\n");
        printf("####################################\n");
        printf("> 심사위원 이름: ");
        if (scanf("%s", judge_name) != 1) {
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        printf("> 전문 분야: ");
        if (fgets(field, sizeof(field), stdin) == NULL) {
            field[0] = '\0';
        }
        remove_newline(field);

        field_index = get_field_index(field);
        if (field_index == -1) {
            printf("전문 분야가 올바르지 않습니다. 다시 입력하세요.\n\n");
            continue;
        }

        printf("++++++++++++++++++++++++++++++++++++\n");
        int i;
        for (i = 0; i < NUM_CANDIDATES; i++) {
            int score;
            do {
                printf("후보자: %s\n", candidate_names[i]);
                printf("%s: ", field_names[field_index]);
                if (scanf("%d", &score) != 1) {
                    clear_input_buffer();
                    score = -1;
                }
                if (score < 10 || score > 100) {
                    printf("잘못된 점수입니다. 10에서 100 사이로 입력하세요.\n");
                }
            } while (score < 10 || score > 100);
            scoring_sheet[i][field_index] = score;
            printf("------------------------------------\n");
        }
        break;
    }
}

void calculate_totals() {
    int i, j;
    for (i = 0; i < NUM_CANDIDATES; i++) {
        int total = 0;
        for (j = 0; j < NUM_FIELDS; j++) {
            total += scoring_sheet[i][j];
        }
        scoring_sheet[i][NUM_FIELDS] = total;
    }
}

void print_scores(int field_index) {
    int i;
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("입력을 모두 완료했습니다.\n");
    printf("입력하신 내용을 검토하세요!\n");
    printf("------------------------------------\n");
    for (i = 0; i < NUM_CANDIDATES; i++) {
        printf("%s: %d\n", candidate_names[i], scoring_sheet[i][field_index]);
    }
}

void modify_scores() {
    while (1) {
        int id, found = 0;
        printf("수정할 후보자의 6자리 ID (종료는 0 입력): ");
        if (scanf("%d", &id) != 1) {
            clear_input_buffer();
            continue;
        }
        if (id == 0) break;

        int i;
        for (i = 0; i < NUM_CANDIDATES; i++) {
            if (candidate_ids[i] == id) {
                found = 1;
                printf("수정할 분야 (0:음악 1:댄스 2:보컬 3:비주얼 4:전달력): ");
                int f;
                if (scanf("%d", &f) != 1) {
                    clear_input_buffer();
                    printf("잘못된 입력입니다.\n");
                    break;
                }
                if (f >= 0 && f < NUM_FIELDS) {
                    int new_score;
                    do {
                        printf("새 점수 (10~100): ");
                        if (scanf("%d", &new_score) != 1) {
                            clear_input_buffer();
                            new_score = -1;
                        }
                    } while (new_score < 10 || new_score > 100);
                    scoring_sheet[i][f] = new_score;
                    printf("수정 완료.\n");
                } else {
                    printf("잘못된 분야입니다.\n");
                }
                break;
            }
        }
        if (!found) printf("존재하지 않는 ID입니다.\n");
    }
}

void print_finalists() {
    int order[NUM_CANDIDATES];
    int i, j;
    for (i = 0; i < NUM_CANDIDATES; i++) order[i] = i;

    // 점수 내림차순 정렬 (단순 선택 정렬)
    for (i = 0; i < NUM_CANDIDATES - 1; i++) {
        for (j = i + 1; j < NUM_CANDIDATES; j++) {
            if (scoring_sheet[order[i]][NUM_FIELDS] < scoring_sheet[order[j]][NUM_FIELDS]) {
                int tmp = order[i];
                order[i] = order[j];
                order[j] = tmp;
            }
        }
    }

    printf("=======================================\n");
    printf("후보 선발 결과 집계 중 ...\n");
    printf("=======================================\n");
    printf("#######################################\n");
    printf("# 밀리웨이즈의 멤버가 된 걸축하합니다!  #\n");
    printf("#######################################\n");
    for (i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, candidate_names[order[i]]);
    }
}

int main() {
    while (1) {
        input_scores();
        calculate_totals();

        char submit;
        while (1) {
            print_scores(NUM_FIELDS); // 총점 출력
            printf("제출하시겠습니까? (Y/N): ");
            clear_input_buffer();
            if (scanf("%c", &submit) != 1) continue;
            if (submit == 'Y' || submit == 'y') {
                printf("***최종 제출을 완료했습니다.***\n");
                break;
            } else if (submit == 'N' || submit == 'n') {
                modify_scores();
                calculate_totals();
            }
        }
        break;
    }

    print_finalists();

    return 0;
}
