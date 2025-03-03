#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/ClimberSubsystem.h"
#include "generated/TunerConstants.h"
#include <frc/controller/PIDController.h>
#include <iostream>
#include <ctre/phoenix/motorcontrol/ControlMode.h>

frc::DigitalInput sensor{9};

ClimberSubsystem::ClimberSubsystem() {

}


frc2::CommandPtr ClimberSubsystem::ClimbUp() {
    return this->RunOnce(
        [this] {
            ClimberMotor.SetControl(m_request.WithPosition(1_tr));
            //m_request.Position;
        }
    ).AndThen(
        [this] {
            ClimberMotor.SetControl(m_request.WithPosition(0_tr));
        }
    );
}

void ClimberSubsystem::InitSendable(wpi::SendableBuilder& builder) {
    SubsystemBase::InitSendable(builder);
}