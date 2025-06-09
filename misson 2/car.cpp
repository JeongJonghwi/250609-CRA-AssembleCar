#include "car.h"

void Car::setCarType(int type)
{
    carType = type;
    printf("���� Ÿ������ %s�� �����ϼ̽��ϴ�.\n", carTypeToString(type));
}

void Car::setEngine(int _engine)
{
    engine = _engine;
    printf("%s ������ �����ϼ̽��ϴ�.\n", engineToString(engine));
}

void Car::setBrakeSystem(int brake)
{
    brakeSystem = brake;
    printf("%s ������ġ�� �����ϼ̽��ϴ�.\n", brakeToString(brake));
}

void Car::setSteeringSystem(int steering)
{
    steeringSystem = steering;
    printf("%s ������ġ�� �����ϼ̽��ϴ�.\n", steeringToString(steering));
}

void Car::runProducedCar()
{
    if (isAllPartsValid(false)) {
        if (engine == BROKEN) {
            printf("������ ���峪�ֽ��ϴ�.\n");
            printf("�ڵ����� �������� �ʽ��ϴ�.\n");
        } else {
            printf("Car Type : %s\n", carTypeToString(carType));
            printf("Engine : %s\n", engineToString(engine));
            printf("Brake System : %s\n", brakeToString(brakeSystem));
            printf("Steering System : %s\n", steeringToString(steeringSystem));
            printf("�ڵ����� ���۵˴ϴ�.\n");
        }
    } else {
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
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
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
            printf("Sedan���� Continental������ġ ��� �Ұ�\n");
        }
        return false;
    }
    if (carType == SUV && engine == TOYOTA) {
        if (test) {
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
            printf("SUV���� TOYOTA���� ��� �Ұ�\n");
        }
        return false;
    }
    if (carType == TRUCK && engine == WIA) {
        if (test) {
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
            printf("Truck���� WIA���� ��� �Ұ�\n");
        }
        return false;
    }
    if (carType == TRUCK && brakeSystem == MANDO) {
        if (test) {
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
            printf("Truck���� Mando������ġ ��� �Ұ�\n");
        }
        return false;
    }
    if (brakeSystem == BOSCH_B && steeringSystem != BOSCH_S) {
        if (test) {
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
            printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
        }
        return false;
    }

    if (test)
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
    return true;
}