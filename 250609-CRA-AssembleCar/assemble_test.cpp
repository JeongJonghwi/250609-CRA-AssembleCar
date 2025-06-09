#include "gmock/gmock.h"
#include "assemble.h"
#include <sstream>

class CarFixture : public ::testing::Test {
public:
    std::shared_ptr<Car> car = std::make_shared<Car>();

    void carSetting(int type, int engine, int brake, int steering) {
        car->setCarType(type);
        car->setEngine(engine);
        car->setBrakeSystem(brake);
        car->setSteeringSystem(steering);
    }
};

class AssembleFixture : public ::testing::Test {
public:
    std::shared_ptr<Assemble> assemble = nullptr;
    std::shared_ptr<Car> car = std::make_shared<Car>();

    void assembleSetting(const char* buf)
    {
        assemble = std::make_shared<Assemble>(car, buf);
    }

    void assembleSetting(int userInput) {
        assemble = std::make_shared<Assemble>(car, userInput);
    }
};

TEST_F(CarFixture, testValidCarProducedFail1)
{
    carSetting(SEDAN, BROKEN, MANDO, BOSCH_S);
    car->runProducedCar();
}

TEST_F(CarFixture, testValidCarProducedFail2)
{
    carSetting(SEDAN, GM, CONTINENTAL, BOSCH_S);
    car->runProducedCar();
}

TEST_F(CarFixture, testSedanWithContinental1) {
    carSetting(SEDAN, GM, CONTINENTAL, BOSCH_S);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testSedanWithContinental2)
{
    carSetting(SEDAN, TOYOTA, CONTINENTAL, BOSCH_S);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testSedanWithContinental3)
{
    carSetting(SEDAN, WIA, CONTINENTAL, BOSCH_S);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testSedanWithContinental4)
{
    carSetting(SEDAN, GM, CONTINENTAL, MOBIS);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testSedanWithContinental5)
{
    carSetting(SEDAN, TOYOTA, CONTINENTAL, MOBIS);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testSedanWithContinental6)
{
    carSetting(SEDAN, WIA, CONTINENTAL, MOBIS);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testSUVWithTOYOTA1) {
    carSetting(SUV, TOYOTA, MANDO, BOSCH_S);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testSUVWithTOYOTA2)
{
    carSetting(SUV, TOYOTA, CONTINENTAL, BOSCH_S);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testSUVWithTOYOTA3)
{
    carSetting(SUV, TOYOTA, BOSCH_B, BOSCH_S);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testSUVWithTOYOTA4)
{
    carSetting(SUV, TOYOTA, MANDO, MOBIS);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testSUVWithTOYOTA5)
{
    carSetting(SUV, TOYOTA, CONTINENTAL, MOBIS);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testSUVWithTOYOTA6)
{
    carSetting(SUV, TOYOTA, BOSCH_B, MOBIS);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testTruckWithWIA1)
{
    carSetting(TRUCK, WIA, MANDO, BOSCH_S);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testTruckWithWIA2)
{
    carSetting(TRUCK, WIA, CONTINENTAL, BOSCH_S);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testTruckWithWIA3)
{
    carSetting(TRUCK, WIA, BOSCH_B, BOSCH_S);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testTruckWithWIA4)
{
    carSetting(TRUCK, WIA, MANDO, MOBIS);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testTruckWithWIA5)
{
    carSetting(TRUCK, WIA, CONTINENTAL, MOBIS);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testTruckWithWIA6)
{
    carSetting(TRUCK, WIA, BOSCH_B, MOBIS);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testTruckWithMando1)
{
    carSetting(TRUCK, GM, MANDO, BOSCH_S);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testTruckWithMando2)
{
    carSetting(TRUCK, TOYOTA, MANDO, BOSCH_S);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testTruckWithMando3)
{
    carSetting(TRUCK, GM, MANDO, MOBIS);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testTruckWithMando4)
{
    carSetting(TRUCK, TOYOTA, MANDO, MOBIS);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(CarFixture, testBoschWithMobis1)
{
    carSetting(SEDAN, GM, BOSCH_B, MOBIS);
    EXPECT_FALSE(car->isAllPartsValid(true));
}

TEST_F(AssembleFixture, testIsUserInputExit)
{
    assembleSetting("exit");
    EXPECT_TRUE(assemble->isUserInputExit());
}

TEST_F(AssembleFixture, testIsNotUserInputExit)
{
    assembleSetting("1");
    EXPECT_FALSE(assemble->isUserInputExit());
}

TEST_F(AssembleFixture, testValidUserInput)
{
    assembleSetting("1");
    EXPECT_FALSE(assemble->isInvalidUserInput(CarType_Q));
}

TEST_F(AssembleFixture, testInvalidUserInput)
{
    assembleSetting("asdf");
    EXPECT_TRUE(assemble->isInvalidUserInput(CarType_Q));
}

TEST_F(AssembleFixture, testInvalidCarType) {
    assembleSetting("0");
    EXPECT_TRUE(assemble->isInvalidUserInput(CarType_Q));
}

TEST_F(AssembleFixture, testInvalidEngine)
{
    assembleSetting("5");
    EXPECT_TRUE(assemble->isInvalidUserInput(Engine_Q));
}

TEST_F(AssembleFixture, testInvalidBrake)
{
    assembleSetting("4");
    EXPECT_TRUE(assemble->isInvalidUserInput(brakeSystem_Q));
}

TEST_F(AssembleFixture, testInvalidSteering)
{
    assembleSetting("3");
    EXPECT_TRUE(assemble->isInvalidUserInput(SteeringSystem_Q));
}

TEST_F(AssembleFixture, testInvalidRunTest)
{
    assembleSetting("3");
    EXPECT_TRUE(assemble->isInvalidUserInput(Run_Test));
}

TEST_F(AssembleFixture, testRunStepForAssemble1) {
    int step = Run_Test;
    assembleSetting(0);
    EXPECT_FALSE(assemble->runStepForAssemble(step));
}

TEST_F(AssembleFixture, testRunStepForAssemble2)
{
    int step = Engine_Q;
    assembleSetting(0);
    EXPECT_FALSE(assemble->runStepForAssemble(step));
}

TEST_F(AssembleFixture, testRunStepForAssemble3)
{
    int step = CarType_Q;
    assembleSetting(1);
    EXPECT_TRUE(assemble->runStepForAssemble(step));
}

TEST_F(AssembleFixture, testRunStepForAssemble4)
{
    int step = Engine_Q;
    assembleSetting(1);
    EXPECT_TRUE(assemble->runStepForAssemble(step));
}

TEST_F(AssembleFixture, testRunStepForAssemble5)
{
    int step = brakeSystem_Q;
    assembleSetting(1);
    EXPECT_TRUE(assemble->runStepForAssemble(step));
}

TEST_F(AssembleFixture, testRunStepForAssemble6)
{
    int step = SteeringSystem_Q;
    assembleSetting(1);
    EXPECT_TRUE(assemble->runStepForAssemble(step));
}

TEST_F(AssembleFixture, testRunStepForAssemble7)
{
    int step = Run_Test;
    assembleSetting(1);
    EXPECT_TRUE(assemble->runStepForAssemble(step));
}

TEST_F(AssembleFixture, testRunStepForAssemble8)
{
    int step = Run_Test;
    assembleSetting(2);
    EXPECT_TRUE(assemble->runStepForAssemble(step));
}