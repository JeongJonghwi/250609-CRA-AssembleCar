#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assemble.h"
#include "gmock/gmock.h"

void delay(int ms) {
    volatile int sum = 0;
    while (sum++ < ms * 1000 * 1000)
        ;
}

void printErrorAndDelay(const char* errMsg, int ms)
{
    printf("ERROR :: %s\n", errMsg);
    delay(ms);
}

bool Assemble::isUserInputExit()
{
    if (!strcmp(buf, "exit")) {
        printf("바이바이\n");
        return true;
    }
    return false;
}

bool Assemble::isInvalidUserInput(int stepForAssemble)
{
    char* checkNumber;
    userInput = strtol(buf, &checkNumber, 10);

    if (*checkNumber != '\0') {
        printErrorAndDelay("숫자만 입력 가능", 800);
        return true;
    }

    if (stepForAssemble == CarType_Q && !(userInput >= CARTYPE_START && userInput <= CARTYPE_END)) {
        printErrorAndDelay("차량 타입은 1 ~ 3 범위만 선택 가능", 800);
        return true;
    }

    if (stepForAssemble == Engine_Q && !(userInput >= ENGINE_START && userInput <= ENGINE_END)) {
        printErrorAndDelay("엔진은 1 ~ 4 범위만 선택 가능", 800);
        return true;
    }

    if (stepForAssemble == brakeSystem_Q && !(userInput >= BRAKE_START && userInput <= BRAKE_END)) {
        printErrorAndDelay("제동장치는 1 ~ 3 범위만 선택 가능", 800);
        return true;
    }

    if (stepForAssemble == SteeringSystem_Q && !(userInput >= STEERING_START && userInput <= STEERING_END)) {
        printErrorAndDelay("조향장치는 1 ~ 2 범위만 선택 가능", 800);
        return true;
    }

    if (stepForAssemble == Run_Test && !(userInput >= 0 && userInput <= 2)) {
        printErrorAndDelay("Run 또는 Test 중 하나를 선택 필요", 800);
        return true;
    }

    return false;
}

bool Assemble::runStepForAssemble(int &stepForAssemble)
{
    if (userInput == 0 && stepForAssemble == Run_Test) {
        stepForAssemble = CarType_Q;
        return false;
    }

    if (userInput == 0 && stepForAssemble >= 1) {
        stepForAssemble -= 1;
        return false;
    }

    if (stepForAssemble == CarType_Q) {
        car->setCarType(userInput);
        delay(800);
        stepForAssemble = Engine_Q;
    } else if (stepForAssemble == Engine_Q) {
        car->setEngine(userInput);
        delay(800);
        stepForAssemble = brakeSystem_Q;
    } else if (stepForAssemble == brakeSystem_Q) {
        car->setBrakeSystem(userInput);
        delay(800);
        stepForAssemble = SteeringSystem_Q;
    } else if (stepForAssemble == SteeringSystem_Q) {
        car->setSteeringSystem(userInput);
        delay(800);
        stepForAssemble = Run_Test;
    } else if (stepForAssemble == Run_Test) {
        runProduceOrTest();
        delay(2000);
    }
    return true;
}

void Assemble::runProduceOrTest()
{
    if (userInput == 1) {
        car->runProducedCar();
    } else if (userInput == 2) {
        printf("Test...\n");
        delay(1500);
        car->testProducedCar();
    }
}