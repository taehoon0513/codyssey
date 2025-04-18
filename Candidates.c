#include <stdio.h>
#include <stdlib.h>
C

char *member_info[11] = {
    "성명", "생일", "성별", "메일", "국적", "BMI", "주스킬", "보조스킬", "TOPIK", "MBTI", "소개"
};

char candidate01[11][100], candidate02[11][100], candidate03[11][100];
char candidate04[11][100], candidate05[11][100], candidate06[11][100];
char (*candidates[6])[11][100] = {
    &candidate01, &candidate02, &candidate03, &candidate04, &candidate05, &candidate06
};

char group_name[100];

int calculate_age(const char *birth) {
    int byear, bmonth, bday;
    int cyear = 2025, cmonth = 4, cday = 18;

    sscanf(birth, "%4d/%2d/%2d", &byear, &bmonth, &bday);
    int age = cyear - byear;
    if (cmonth < bmonth || (cmonth == bmonth && cday < bday)) {
        age--;
    }
    return age;
}

void flush_input() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int main() {
    int i, j;

    printf("####################################\n");
    printf("  오디션 그룹명을 입력하세요: ");
    fgets(group_name, sizeof(group_name), stdin);
    for (i = 0; group_name[i] != '\0'; i++) {
        if (group_name[i] == '\n') {
            group_name[i] = '\0';
        }
    }
    printf("####################################\n");
    printf("[%s] 오디션 후보자 데이터 입력\n", group_name);
    printf("####################################\n");

    i = 0;
    while (i < MAX) {
        printf("첫 번째 후보자의 정보를 입력합니다.\n");
        printf("---------------------------------\n");
        for (j = 0; j < 11; j++) {
            printf("%d. %s: ", j + 1, member_info[j]);
            fgets((*candidates[i])[j], 100, stdin);
            if ((*candidates[i])[j][0] == '\n') j--;
            else {
                size_t len = 0;
                while ((*candidates[i])[j][len] != '\0') {
                    if ((*candidates[i])[j][len] == '\n') {
                        (*candidates[i])[j][len] = '\0';
                        break;
                    }
                    len++;
                }
            }
        }
        i++;
        if (i < MAX)
            printf("=================================\n%d 번째 후보자를 입력합니다.\n---------------------------------\n", i + 1);
    }

    printf("\n####################################\n");
    printf("[%s] 오디션 후보자 데이터 조회\n", group_name);
    printf("####################################\n");

    printf("=============================================================================================================\n");
    printf("성   명 | 생일    | 성별 | 메일                | 국적 | BMI  | 주스킬 | 보조스킬 | TOPIK  | MBTI |\n");
    printf("=============================================================================================================\n");

    for (i = 0; i < MAX; i++) {
        int age = calculate_age((*candidates[i])[1]);
        printf("%s(%d) |%s| %s  | %-20s| %-4s | %-4s | %-6s | %-8s |",
            (*candidates[i])[0], age, (*candidates[i])[1],
            (*candidates[i])[2][0] == 'F' ? "여" : "남",
            (*candidates[i])[3],
            (*candidates[i])[4],
            (*candidates[i])[5],
            (*candidates[i])[6],
            (*candidates[i])[7]
        );
        int topik = atoi((*candidates[i])[8]);
        if (topik == 0)
            printf(" 원어민 |");
        else
            printf(" %d급    |", topik);
        printf(" %s |\n", (*candidates[i])[9]);
        printf("-------------------------------------------------------------------------------------------------------------\n");
        printf("%s\n", (*candidates[i])[10]);
        printf("-------------------------------------------------------------------------------------------------------------\n");
    }

    return 0;
}
