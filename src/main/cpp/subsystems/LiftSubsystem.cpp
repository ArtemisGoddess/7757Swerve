#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/LiftSubsystem.h"
#include "generated/TunerConstants.h"
#include "RobotContainer.h"
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/PIDController.h>
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <Robot.h>

LiftSubsystem::LiftSubsystem() {}

frc2::CommandPtr LiftSubsystem::LiftUp(const units::angle::turn_t turns) {
    return this->RunOnce(
        [this, turns] {
            LiftMotor.SetControl(m_request.WithPosition((units::angle::turn_t)m_request.Position() + turns));
        }
    );
}

frc2::CommandPtr LiftSubsystem::LiftDown(const units::angle::turn_t turns) {
    return this->RunOnce(
        [this, turns] {
            LiftMotor.SetControl(m_request.WithPosition((units::angle::turn_t)m_request.Position() - turns));
        }
    );
}

void LiftSubsystem::InitSendable(wpi::SendableBuilder& builder) {
    SubsystemBase::InitSendable(builder);
}