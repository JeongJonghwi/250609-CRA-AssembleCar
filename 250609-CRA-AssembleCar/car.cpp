#include "car.h"

void Car::setCarType(int type)
{
    carType = type;
    printf("차량 타입으로 %s을 선택하셨습니다.\n", carTypeToString(type));
}

void Car::setEngine(int _engine)
{
    engine = _engine;
    printf("%s 엔진을 선택하셨습니다.\n", engineToString(engine));
}

void Car::setBrakeSystem(int brake)
{
    brakeSystem = brake;
    printf("%s 제동장치를 선택하셨습니다.\n", brakeToString(brake));
}

void Car::setSteeringSystem(int steering)
{
    steeringSystem = steering;
    printf("%s 조향장치를 선택하셨습니다.\n", steeringToString(steering));
}

void Car::runProducedCar()
{
    if (isAllPartsValid(false)) {
        if (engine == BROKEN) {
            printf("엔진이 고장나있습니다.\n");
            printf("자동차가 움직이지 않습니다.\n");
        } else {
            printf("Car Type : %s\n", carTypeToString(carType));
            printf("Engine : %s\n", engineToString(engine));
            printf("Brake System : %s\n", brakeToString(brakeSystem));
            printf("Steering System : %s\n", steeringToString(steeringSystem));
            printf("자동차가 동작됩니다.\n");
        }
    } else {
        printf("자동차가 동작되지 않습니다\n");
    }
}

void Car::testProducedCar()
{
    isAllPartsValid(true);
}

bool Car::isAllPartsValid(bool test)
{
    if (carType == SEDAN && brakeSystem == CONTINENTAL) {
        if (test) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Sedan에는 Continental제동장치 사용 불가\n");
        }
        return false;
    }
    if (carType == SUV && engine == TOYOTA) {
        if (test) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("SUV에는 TOYOTA엔진 사용 불가\n");
        }
        return false;
    }
    if (carType == TRUCK && engine == WIA) {
        if (test) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Truck에는 WIA엔진 사용 불가\n");
        }
        return false;
    }
    if (carType == TRUCK && brakeSystem == MANDO) {
        if (test) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Truck에는 Mando제동장치 사용 불가\n");
        }
        return false;
    }
    if (brakeSystem == BOSCH_B && steeringSystem != BOSCH_S) {
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