#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/WristSubsystem.h"
#include "generated/TunerConstants.h"
#include "RobotContainer.h"
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/PIDController.h>
#include <iostream>
#include <ctre/phoenix/motorcontrol/ControlMode.h>

WristSubsystem::WristSubsystem() {}

frc2::CommandPtr WristSubsystem::Wrist1() { //For auto
    return this->RunOnce(
        [this] {
            WristMotor.SetControl(m_request.WithPosition(0_tr));
        }
    )
    .WithInterruptBehavior(frc2::Command::InterruptionBehavior::kCancelSelf);
}

frc2::CommandPtr WristSubsystem::Wrist2() { //For auto
    return this->RunOnce(
        [this] {
            WristMotor.SetControl(m_request.WithPosition(2_tr));
        }
    )
    .WithInterruptBehavior(frc2::Command::InterruptionBehavior::kCancelSelf);
}



frc2::CommandPtr WristSubsystem::WristLeft() {
    return this->Run(   
        [this] {
            if (WristMotor.GetPosition().GetValue() < 0_tr) {
                WristMotor.SetControl(m_request.WithPosition(0_tr));
            } else {
                WristMotor.SetControl(m_request.WithPosition(WristMotor.GetPosition().GetValue() - 1_tr));
            }
        }
    )

    .WithInterruptBehavior(frc2::Command::InterruptionBehavior::kCancelSelf);
}

frc2::CommandPtr WristSubsystem::WristRight() {
    return this->Run(
        [this] {
            if (WristMotor.GetPosition().GetValue() > 2.76_tr) {
                WristMotor.SetControl(m_request.WithPosition(2.76_tr));
            } else { 
                WristMotor.SetControl(m_request.WithPosition(WristMotor.GetPosition().GetValue() + 0.5_tr));
            }
            //WristMotor.Set(-0.5);
        }
    )
    .WithInterruptBehavior(frc2::Command::InterruptionBehavior::kCancelSelf);
}

void WristSubsystem::InitSendable(wpi::SendableBuilder& builder) { SubsystemBase::InitSendable(builder); }