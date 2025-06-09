#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLEAR_SCREEN "\033[H\033[2J"
#define MAX_PARTS_NUM 10
#define MAX_BUF_SIZE 100

int parts[MAX_PARTS_NUM];

void showMenuAndGetAnswer(int step, char buf[MAX_BUF_SIZE]);
bool isAnswerExit(char buf[MAX_BUF_SIZE]);
bool isInvalidAnswer(int& answer, char buf[MAX_BUF_SIZE], int step);
void runStep(int answer, int& step);
void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runOrTest(int answer);
void runProducedCar();
void testProducedCar();
bool isAllPartsValid(bool test);

enum QuestionType {
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

enum CarType {
    CARTYPE_START = 1,
    SEDAN = CARTYPE_START,
    SUV,
    TRUCK,
    CARTYPE_END = TRUCK,
};
const char* carTypeToString(int type)
{
    if (type == SEDAN)
        return "Sedan";
    if (type == SUV)
        return "SUV";
    return "Truck";
}

enum Engine {
    ENGINE_START,
    GM,
    TOYOTA,
    WIA,
    ENGINE_END = WIA,
};
static const char* engineToString(int engine)
{
    if (engine == GM)
        return "GM";
    if (engine == TOYOTA)
        return "TOYOTA";
    return "WIA";
}

enum brakeSystem {
    BRAKE_START,
    MANDO,
    CONTINENTAL,
    BOSCH_B,
    BRAKE_END = BOSCH_B,
};
static const char* brakeToString(int brake)
{
    if (brake == MANDO)
        return "Mando";
    if (brake == CONTINENTAL)
        return "Continental";
    return "Bosch";
}

enum SteeringSystem {
    STEERING_START,
    BOSCH_S,
    MOBIS,
    STEERING_END = MOBIS,
};
static const char* steeringToString(int steering)
{
    if (steering == BOSCH_S)
        return "Bosch";
    return "Mobis";
}

static inline void delay(int ms)
{
    volatile int sum = 0;
    while (sum++ < ms * 1000 * 1000);
}

int main()
{
    char buf[MAX_BUF_SIZE];
    int step = CarType_Q;
    int answer;

    while (1) {
        showMenuAndGetAnswer(step, buf);

        if (isAnswerExit(buf))
            break;

        if (isInvalidAnswer(answer, buf, step))
            continue;

        runStep(answer, step);
    }
}

void showMenuAndGetAnswer(int step, char buf[MAX_BUF_SIZE])
{
    printf(CLEAR_SCREEN);
    if (step == CarType_Q) {
        printf("        ______________\n");
        printf("       /|             | \n");
        printf("  ____/_|_____________|____\n");
        printf(" |                      O  |\n");
        printf(" '-(@)----------------(@)--'\n");
        printf("===============================\n");
        printf("어떤 차량 타입을 선택할까요?\n");
        printf("1. Sedan\n");
        printf("2. SUV\n");
        printf("3. Truck\n");
    } else if (step == Engine_Q) {
        printf("어떤 엔진을 탑재할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. GM\n");
        printf("2. TOYOTA\n");
        printf("3. WIA\n");
        printf("4. 고장난 엔진\n");
    } else if (step == brakeSystem_Q) {
        printf("어떤 제동장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. MANDO\n");
        printf("2. CONTINENTAL\n");
        printf("3. BOSCH\n");
    } else if (step == SteeringSystem_Q) {
        printf("어떤 조향장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. BOSCH\n");
        printf("2. MOBIS\n");
    } else if (step == Run_Test) {
        printf("멋진 차량이 완성되었습니다.\n");
        printf("어떤 동작을 할까요?\n");
        printf("0. 처음 화면으로 돌아가기\n");
        printf("1. RUN\n");
        printf("2. Test\n");
    }
    printf("===============================\n");
    printf("INPUT > ");
    fgets(buf, sizeof(buf), stdin);

    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);
}

bool isAnswerExit(char buf[MAX_BUF_SIZE])
{
    if (!strcmp(buf, "exit")) {
        printf("바이바이\n");
        return true;
    }
    return false;
}

bool isInvalidAnswer(int& answer, char buf[MAX_BUF_SIZE], int step)
{
    char* checkNumber;
    answer = strtol(buf, &checkNumber, 10);

    if (*checkNumber != '\0') {
        printf("ERROR :: 숫자만 입력 가능\n");
        delay(800);
        return true;
    }

    if (step == CarType_Q && !(answer >= CARTYPE_START && answer <= CARTYPE_END)) {
        printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
        delay(800);
        return true;
    }

    if (step == Engine_Q && !(answer >= ENGINE_START && answer <= ENGINE_END)) {
        printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
        delay(800);
        return true;
    }

    if (step == brakeSystem_Q && !(answer >= BRAKE_START && answer <= BRAKE_END)) {
        printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
        delay(800);
        return true;
    }

    if (step == SteeringSystem_Q && !(answer >= STEERING_START && answer <= STEERING_END)) {
        printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
        delay(800);
        return true;
    }

    if (step == Run_Test && !(answer >= 0 && answer <= 2)) {
        printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
        delay(800);
        return true;
    }

    return false;
}

void runStep(int answer, int& step)
{
    if (answer == 0 && step == Run_Test) {
        step = CarType_Q;
        return;
    }

    if (answer == 0 && step >= 1) {
        step -= 1;
        return;
    }

    if (step == CarType_Q) {
        selectCarType(answer);
        delay(800);
        step = Engine_Q;
    } else if (step == Engine_Q) {
        selectEngine(answer);
        delay(800);
        step = brakeSystem_Q;
    } else if (step == brakeSystem_Q) {
        selectbrakeSystem(answer);
        delay(800);
        step = SteeringSystem_Q;
    } else if (step == SteeringSystem_Q) {
        selectSteeringSystem(answer);
        delay(800);
        step = Run_Test;
    } else if (step == Run_Test) {
        runOrTest(answer);
        delay(2000);
    }
}

void selectCarType(int answer)
{
    parts[CarType_Q] = answer;
    printf("차량 타입으로 %s을 선택하셨습니다.\n", carTypeToString(answer));
}

void selectEngine(int answer)
{
    parts[Engine_Q] = answer;
    printf("%s 엔진을 선택하셨습니다.\n", engineToString(answer));
}

void selectbrakeSystem(int answer)
{
    parts[brakeSystem_Q] = answer;
    printf("%s 제동장치를 선택하셨습니다.\n", brakeToString(answer));
}

void selectSteeringSystem(int answer)
{
    parts[SteeringSystem_Q] = answer;
    printf("%s 조향장치를 선택하셨습니다.\n", steeringToString(answer));
}

void runOrTest(int answer)
{
    if (answer == 1) {
        runProducedCar();
    } else if (answer == 2) {
        printf("Test...\n");
        delay(1500);
        testProducedCar();
    }
}

void runProducedCar()
{
    if (isAllPartsValid(false)) {
        if (parts[Engine_Q] > ENGINE_END) {
            printf("엔진이 고장나있습니다.\n");
            printf("자동차가 움직이지 않습니다.\n");
        } else {
            printf("Car Type : %s\n", carTypeToString(parts[CarType_Q]));
            printf("Engine : %s\n", engineToString(parts[Engine_Q]));
            printf("Brake System : %s\n", brakeToString(parts[brakeSystem_Q]));
            printf("Steering System : %s\n", steeringToString(parts[brakeSystem_Q]));
            printf("자동차가 동작됩니다.\n");
        }
    } else {
        printf("자동차가 동작되지 않습니다\n");
    }
}

void testProducedCar()
{
    isAllPartsValid(true);
}

bool isAllPartsValid(bool test)
{
    if (parts[CarType_Q] == SEDAN && parts[brakeSystem_Q] == CONTINENTAL) {
        if (test) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Sedan에는 Continental제동장치 사용 불가\n");
        }
        return false;
    }
    if (parts[CarType_Q] == SUV && parts[Engine_Q] == TOYOTA) {
        if (test) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("SUV에는 TOYOTA엔진 사용 불가\n");
        }
        return false;
    }
    if (parts[CarType_Q] == TRUCK && parts[Engine_Q] == WIA) {
        if (test) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Truck에는 WIA엔진 사용 불가\n");
        }
        return false;
    }
    if (parts[CarType_Q] == TRUCK && parts[brakeSystem_Q] == MANDO) {
        if (test) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Truck에는 Mando제동장치 사용 불가\n");
        }
        return false;
    }
    if (parts[brakeSystem_Q] == BOSCH_B && parts[SteeringSystem_Q] != BOSCH_S) {
        if (test) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
        }
        return false;
    }

    if (test)
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
    return true;
}