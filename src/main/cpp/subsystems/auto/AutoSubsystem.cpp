#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/auto/AutoSubsystem.h"
#include "generated/TunerConstants.h"
#include <frc/controller/PIDController.h>
#include <iostream>
#include <ctre/phoenix/motorcontrol/ControlMode.h>

AutoSubsystem::AutoSubsystem() {} //Initilizer

frc2::CommandPtr AutoSubsystem::testPointer() { //Basic commandPtr constructer
    return this->RunOnce(
        [this] {
            //Code goes here, as you would a periodic robot command. Ish.
        }
    );
}

void AutoSubsystem::InitSendable(wpi::SendableBuilder& builder) { SubsystemBase::InitSendable(builder); } //required to schedule the subsystem