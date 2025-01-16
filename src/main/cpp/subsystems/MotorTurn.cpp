#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/MotorTurn.h"
#include "generated/TunerConstants.h"

ctre::phoenix6::CANBus can{"", "./logs/example.hoot"};

MotorTurn::MotorTurn()
    : T_Motor{11, can} {}

frc2::CommandPtr MotorTurn::TurnLeft() {
    return this->RunOnce([this] {T_Motor.Set(0.1);});
}

frc2::CommandPtr MotorTurn::TurnRight() {
    return this->RunOnce([this] {T_Motor.Set(-0.1);}
    
    );
}

frc2::CommandPtr MotorTurn::StopIt() {
    return this->RunOnce([this] {T_Motor.Set(0);}

    );
}

void MotorTurn::InitSendable(wpi::SendableBuilder& builder) {
    SubsystemBase::InitSendable(builder);
}