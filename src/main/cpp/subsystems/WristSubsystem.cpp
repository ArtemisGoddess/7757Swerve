#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/WristSubsystem.h"
#include "generated/TunerConstants.h"
#include "RobotContainer.h"
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/PIDController.h>
#include <iostream>
#include <ctre/phoenix/motorcontrol/ControlMode.h>

WristSubsystem::WristSubsystem() {}

frc2::CommandPtr WristSubsystem::Wrist(const units::angle::turn_t turnPosition) { //For auto
    return this->RunOnce(
        [this, turnPosition] {
            WristMotor.SetControl(m_request.WithPosition(turnPosition));
        }
    );
}

frc2::CommandPtr WristSubsystem::WristLeft(units::angle::turn_t turns) {
    return this->Run(
        [this, turns] {
            WristMotor.SetControl(m_request.WithPosition(m_request.Position + turns));
        }
    );
}

frc2::CommandPtr WristSubsystem::WristRight(units::angle::turn_t turns) {
    return this->Run(
        [this, turns] {
            WristMotor.SetControl(m_request.WithPosition(m_request.Position - turns));
        }
    );
}

void WristSubsystem::InitSendable(wpi::SendableBuilder& builder) { SubsystemBase::InitSendable(builder); }