#pragma once
#include "car.h"
#include <sstream>

#define CLEAR_SCREEN "\033[H\033[2J"
#define MAX_PARTS_NUM 10
#define MAX_BUF_SIZE 100

enum QuestionType {
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

class Assemble {
public:
    Assemble(std::shared_ptr<Car> car, const char* _buf)
        : car { car }
    {
        strcpy_s(buf, MAX_BUF_SIZE, _buf);
    }

    Assemble(std::shared_ptr<Car> car, int _userInput)
        : car { car }
        , userInput { _userInput }
    {
    }

    bool isUserInputExit();
    bool isInvalidUserInput(int stepForAssemble);
    bool runStepForAssemble(int &stepForAssemble);
    void runProduceOrTest();

private:
    char buf[MAX_BUF_SIZE];
    int userInput;
    std::shared_ptr<Car> car;
};