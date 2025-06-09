#include "gmock/gmock.h"
#include "assemble.h"
#include "main.h"

#ifdef _DEBUG
int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}
#else
void showMenuAndGetUserInput(int step, char buf[MAX_BUF_SIZE]);

int main()
{
    char buf[MAX_BUF_SIZE];
    int step = CarType_Q;
    std::shared_ptr<Car> car = std::make_shared<Car>();

    while (1) {
        showMenuAndGetUserInput(step, buf);
        
        std::shared_ptr<Assemble> assemble = std::make_shared<Assemble>(car, buf);

        if (assemble->isUserInputExit())
            break;

        if (assemble->isInvalidUserInput(step))
            continue;

        assemble->runStepForAssemble(step);
    }
}

void showMenuAndGetUserInput(int step, char buf[MAX_BUF_SIZE])
{
    printf(CLEAR_SCREEN);
    if (step == CarType_Q) {
        printf("        ______________\n");
        printf("       /|             | \n");
        printf("  ____/_|_____________|____\n");
        printf(" |                      O  |\n");
        printf(" '-(@)----------------(@)--'\n");
        printf("===============================\n");
        printf("� ���� Ÿ���� �����ұ��?\n");
        printf("1. Sedan\n");
        printf("2. SUV\n");
        printf("3. Truck\n");
    } else if (step == Engine_Q) {
        printf("� ������ ž���ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. GM\n");
        printf("2. TOYOTA\n");
        printf("3. WIA\n");
        printf("4. ���峭 ����\n");
    } else if (step == brakeSystem_Q) {
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. MANDO\n");
        printf("2. CONTINENTAL\n");
        printf("3. BOSCH\n");
    } else if (step == SteeringSystem_Q) {
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. BOSCH\n");
        printf("2. MOBIS\n");
    } else if (step == Run_Test) {
        printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
        printf("� ������ �ұ��?\n");
        printf("0. ó�� ȭ������ ���ư���\n");
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
#endif