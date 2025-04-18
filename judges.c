#include <stdio.h>
#include <stdlib.h>

#define MAX_JUDGES 100
#define MAX_LENGTH 512

char judges_array[MAX_JUDGES][MAX_LENGTH];

// 문자열 길이를 구하는 함수
int my_strlen(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// 문자열 복사 함수
void my_strcpy(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

// 입력 유효성 검사 함수
int validate_input(const char *input) {
    int count = 0;
    int i = 0;
    while (input[i] != '\0') {
        if (input[i] == ',') {
            count++;
        }
        i++;
    }
    // 쉼표가 6개면 7개의 항목이므로 올바름
    return count == 6;
}

// 항목을 추출해서 출력하는 함수
void parse_and_print(const char *input, int index) {
    int i = 0, field = 0, start = 0;
    char buffer[MAX_LENGTH];
    
    printf("[심사위원 %d]\n", index + 1);
    while (1) {
        int j = 0;
        while (input[i] != ',' && input[i] != '\0') {
            buffer[j++] = input[i++];
        }
        buffer[j] = '\0';

        switch (field) {
            case 0: printf("이름:%s\n", buffer); break;
            case 1: printf("성별:%s\n", buffer); break;
            case 2: printf("소속:%s\n", buffer); break;
            case 3: printf("직함:%s\n", buffer); break;
            case 4: printf("전문분야:%s\n", buffer); break;
            case 5: printf("메일:%s\n", buffer); break;
            case 6: printf("전화:%s\n", buffer); break;
        }

        field++;
        if (input[i] == '\0') break;
        i++;
    }
    printf("-----------------------------------\n");
}

int main() {
    char project[MAX_LENGTH];
    int total_judges, select_judges;
    int num_judges = 0;
    char input[MAX_LENGTH];
    char confirm;

    printf("####################################\n");
    printf("#      심사위원 명단 데이터 입력       #\n");
    printf("####################################\n");

    printf("> 참여 프로젝트: ");
    fgets(project, MAX_LENGTH, stdin);
    int len = my_strlen(project);
    if (len > 0 && project[len - 1] == '\n') {
        project[len - 1] = '\0';
    }

    printf("> 심사 총 인원: ");
    scanf("%d", &total_judges);
    printf("> 선발 멤버 수: ");
    scanf("%d", &select_judges);
    getchar(); // 버퍼 비우기

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("%d명의 심사위원 정보 입력을 시작합니다.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    while (num_judges < total_judges) {
        printf("*심사위원 %d: ", num_judges + 1);
        fgets(input, MAX_LENGTH, stdin);
        int len = my_strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        if (!validate_input(input)) {
            printf("입력 항목이 정확하지 않습니다. 다시 입력해주세요.\n");
            continue;
        }

        my_strcpy(judges_array[num_judges], input);
        num_judges++;
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("심사위원 정보 입력이 끝났습니다.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    printf("\"%s 심사위원 정보를 확인할까요?\" (Y/N): ", project);
    scanf(" %c", &confirm);

    if (confirm == 'Y') {
        printf("####################################\n");
        printf("#        심사위원 데이터 출력        #\n");
        printf("####################################\n");

        for (int i = 0; i < total_judges; i++) {
            parse_and_print(judges_array[i], i);
        }
    } else {
        printf("프로그램을 종료합니다.\n");
    }

    return 0;
}
