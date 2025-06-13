#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 최대 후보자 수 */
#define MAX_CANDIDATES 6
#define MAX_MEMBERS 4

/* 후보자 구조체 */
typedef struct {
    char id[10];
    char name[30];
    char nickname[30];
    char education[30];
    float height;      // m 단위
    float weight;      // kg 단위
    char blood_type[3];
    char allergy[50];
    char hobby[100];
    char sns[50];
    int birthdate;     // YYYYMMDD
    int passed;        // 합격 여부 (0 or 1)
    float bmi;
} Candidate;

/* 문제 3과 5에서 가져온 후보자 데이터(예시) */
Candidate candidate_arr[MAX_CANDIDATES] = {
    {"ID001", "박지연", "Ariel", "고1중퇴", 1.68, 0, "A", "유제품", "댄스 연습, 작곡", "Instagram - @Ariel_Jiyeon", 20030405, 1, 0.0},
    {"ID002", "Ethan Smith", "Simba", "중3중퇴", 1.78, 0, "O", "땅콩", "노래 작곡, 헬스 트레이닝", "Twitter - @Simba_Ethan", 20021212, 1, 0.0},
    {"ID003", "Helena Silva", "Belle", "중졸", 1.63, 0, "B", "생선", "노래 부르기, 그림 그리기", "Instagram - @Belle_Helena", 20040101, 1, 0.0},
    {"ID004", "Liam Wilson", "Aladdin", "중2중퇴", 1.75, 0, "AB", "갑각류", "춤추기, 음악 프로듀싱", "Instagram - @Aladdin_Liam", 20021123, 0, 0.0},
    {"ID005", "Candidate5", "Nick5", "고졸", 1.70, 0, "A", "없음", "축구, 게임", "Twitter - @Nick5", 20030505, 0, 0.0},
    {"ID006", "Candidate6", "Nick6", "대졸", 1.82, 0, "B", "없음", "독서, 코딩", "Instagram - @Nick6", 20010909, 0, 0.0}
};

/* 합격자 4명으로 복사할 배열 */
Candidate milliways_arr[MAX_MEMBERS];
int milliways_count = 0;

/* BMI 범위 구분자 */
typedef enum {
    UNDERWEIGHT,
    NORMAL,
    OVERWEIGHT,
    OBESITY
} BmiCategory;

/* BMI 카테고리 계산 함수 */
BmiCategory get_bmi_category(float bmi)
{
    if (bmi < 18.5f) {
        return UNDERWEIGHT;
    } else if (bmi < 24.9f) {
        return NORMAL;
    } else if (bmi < 29.9f) {
        return OVERWEIGHT;
    } else {
        return OBESITY;
    }
}

/* BMI 카테고리 문자열 출력 */
const char* bmi_category_str(BmiCategory cat)
{
    switch(cat) {
        case UNDERWEIGHT: return "저체중";
        case NORMAL:      return "정상";
        case OVERWEIGHT:  return "과체중";
        case OBESITY:     return "비만";
        default:          return "알수없음";
    }
}

/* 인터뷰 추가 정보를 입력 받는 함수 */
void interview_additional_data(Candidate *c)
{
    float bmi_input;

    printf("\n=== %s (%s) 인터뷰 ===\n", c->name, c->nickname);

    /* 키는 이미 있음, BMI를 입력받아 몸무게 계산 */
    printf("BMI 값을 입력하세요 (예: 22.5): ");
    scanf("%f", &bmi_input);
    c->bmi = bmi_input;

    /* 몸무게 계산 BMI = weight / (height*height) => weight = BMI * height^2 */
    c->weight = bmi_input * (c->height * c->height);

    /* 추가 정보 입력 */
    printf("학력 입력: ");
    scanf(" %29[^\n]", c->education);

    printf("혈액형 입력: ");
    scanf(" %2s", c->blood_type);

    printf("알러지 입력: ");
    scanf(" %49[^\n]", c->allergy);

    printf("취미 입력: ");
    scanf(" %99[^\n]", c->hobby);

    printf("SNS 입력: ");
    scanf(" %49[^\n]", c->sns);
}

/* milliways_arr 내용을 리스트 형식으로 출력 */
void print_milliways_list()
{
    int i;
    printf("\n--- 밀리웨이즈 멤버 리스트 ---\n");
    printf("ID      이름       닉네임    학력      키(m) 몸무게(kg) 혈액형 알러지    취미                 SNS                BMI   상태\n");
    printf("----------------------------------------------------------------------------------------------\n");

    for(i=0; i < milliways_count; i++) {
        Candidate *c = &milliways_arr[i];
        BmiCategory cat = get_bmi_category(c->bmi);

        printf("%-7s %-10s %-8s %-8s %5.2f %10.2f %-5s %-8s %-20s %-18s %5.1f %-6s\n",
            c->id, c->name, c->nickname, c->education, c->height,
            c->weight, c->blood_type, c->allergy, c->hobby, c->sns,
            c->bmi, bmi_category_str(cat));
    }
}

int main(void)
{
    int i;

    printf("== 합격자 인터뷰 및 밀리웨이즈 멤버 데이터 수집 ==\n");

    /* candidate_arr에서 합격자만 milliways_arr에 복사 */
    for(i=0; i < MAX_CANDIDATES; i++) {
        if(candidate_arr[i].passed == 1) {
            if(milliways_count < MAX_MEMBERS) {
                /* 기본 기초 정보 복사 */
                milliways_arr[milliways_count] = candidate_arr[i];

                /* 몸무게, BMI 초기화 0 (인터뷰에서 입력 예정) */
                milliways_arr[milliways_count].weight = 0.0f;
                milliways_arr[milliways_count].bmi = 0.0f;

                /* 인터뷰 진행 */
                interview_additional_data(&milliways_arr[milliways_count]);

                milliways_count++;
            }
        }
    }

    /* 리스트 출력 */
    print_milliways_list();

    return 0;
}
