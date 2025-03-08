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
            while((units::angle::turn_t)m_request.Position() < 5_tr) {
                incrmentPosition(m_request, 5_tr, 0.5);
                ClimberMotor.SetControl(m_request);
            }
        }
    );
}

frc2::CommandPtr ClimberSubsystem::ClimbDown() {
    return this->RunOnce(
        [this] {
            while((units::angle::turn_t)m_request.Position() < -2_tr) {
                incrmentPosition(m_request, -2_tr, 0.5);
                ClimberMotor.SetControl(m_request);
            }
        }
    );
}

void ClimberSubsystem::InitSendable(wpi::SendableBuilder& builder) {
    SubsystemBase::InitSendable(builder);
}