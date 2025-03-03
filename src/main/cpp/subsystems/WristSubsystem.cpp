#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/WristSubsystem.h"
#include "generated/TunerConstants.h"
#include "RobotContainer.h"
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/PIDController.h>
#include <iostream>
#include <ctre/phoenix/motorcontrol/ControlMode.h>

frc::DigitalInput sensor{9};

WristSubsystem::WristSubsystem() {

}

frc2::CommandPtr WristSubsystem::Wrist(const units::angle::turn_t turns) {
    return this->RunOnce(
        [this] {
            WristMotor.SetControl(m_request.WithPosition(1_tr));
            //m_request.Position;
        }
    ).AndThen(
        [this] {
            WristMotor.SetControl(m_request.WithPosition(0_tr));
        }
    );
}

void WristSubsystem::InitSendable(wpi::SendableBuilder& builder) {
    SubsystemBase::InitSendable(builder);
}