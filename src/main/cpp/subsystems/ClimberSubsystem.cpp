#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/ClimberSubsystem.h"
#include "generated/TunerConstants.h"
#include <frc/controller/PIDController.h>
#include <iostream>
#include <ctre/phoenix/motorcontrol/ControlMode.h>

ClimberSubsystem::ClimberSubsystem() {}


frc2::CommandPtr ClimberSubsystem::ClimbUp() {
    return this->RunOnce(
        [this] {
            //ClimberMotor.SetControl(m_request.WithPosition(5_tr));
        }
    );
}

frc2::CommandPtr ClimberSubsystem::ClimbDown() {
    return this->RunOnce(
        [this] {
            //ClimberMotor.SetControl(m_request.WithPosition(-2_tr));
        }
    );
}

void ClimberSubsystem::InitSendable(wpi::SendableBuilder& builder) {
    SubsystemBase::InitSendable(builder);
}