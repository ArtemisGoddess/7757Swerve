#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/WristSubsystem.h"
#include "generated/TunerConstants.h"
#include "RobotContainer.h"
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/PIDController.h>
#include <iostream>
#include <ctre/phoenix/motorcontrol/ControlMode.h>

WristSubsystem::WristSubsystem() {}

frc2::CommandPtr WristSubsystem::Wrist(units::turn_t position) { //For auto
    return this->RunOnce(
        [this, position] {
            WristMotor.SetControl(m_request.WithPosition(position));
        }
    );
}

frc2::CommandPtr WristSubsystem::WristLeft() {
    return this->Run(   
        [this] {
            units::angle::turn_t math = std::max(WristMotor.GetPosition().GetValue() - 1_tr, 0_tr);
            WristMotor.SetControl(m_request.WithPosition(math));
        }
    )
    .Until([this] {return std::max(WristMotor.GetPosition().GetValue() - 1_tr, 0_tr) <= 0_tr;});
}

frc2::CommandPtr WristSubsystem::WristRight() {
    return this->Run(
        [this] {
            units::angle::turn_t math = std::min(WristMotor.GetPosition().GetValue() + 0.5_tr, 2.76_tr);
            WristMotor.SetControl(m_request.WithPosition(math));
        }
    )
    .Until([this] {return std::min(WristMotor.GetPosition().GetValue() + 0.5_tr, 2.76_tr) >= 2.76_tr;});
}

void WristSubsystem::InitSendable(wpi::SendableBuilder& builder) { SubsystemBase::InitSendable(builder); }