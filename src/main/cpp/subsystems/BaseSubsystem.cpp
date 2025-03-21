#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/BaseSubsystem.h"
#include "generated/TunerConstants.h"
#include <frc/controller/PIDController.h>
#include <iostream>
#include <ctre/phoenix/motorcontrol/ControlMode.h>

BaseSubsystem::BaseSubsystem() {} //Initilizer

frc2::CommandPtr BaseSubsystem::testPointer() { //Basic commandPtr constructer
    return this->RunOnce(
        [this] {
            //Code goes here, as you would a periodic robot command
        }
    );
}

void BaseSubsystem::InitSendable(wpi::SendableBuilder& builder) { SubsystemBase::InitSendable(builder); } //required to schedule the subsystem