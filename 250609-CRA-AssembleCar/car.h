#pragma once
#include <stdio.h>

enum CarType {
    CARTYPE_START = 1,
    SEDAN = CARTYPE_START,
    SUV,
    TRUCK,
    CARTYPE_END = TRUCK,
};
static const char* carTypeToString(int type)
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
    BROKEN,
    ENGINE_END = BROKEN,
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

class Car {
public:
    void setCarType(int type);
    void setEngine(int _engine);
    void setBrakeSystem(int brake);
    void setSteeringSystem(int steering);
    void runProducedCar();
    void testProducedCar();
    bool isAllPartsValid(bool test);

private:
    int carType;
    int engine;
    int brakeSystem;
    int steeringSystem;
};