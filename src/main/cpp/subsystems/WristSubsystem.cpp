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
            m_request.Position += turns;
            WristMotor.SetControl(m_request);

            //WristMotor.Set(0.5);
        }
    ).FinallyDo(
        [this] {
            //WristMotor.Set(0);
            //WristMotor.SetControl(test);
        }
    );
}

frc2::CommandPtr WristSubsystem::WristRight(units::angle::turn_t turns) {
    return this->Run(
        [this, turns] {
            m_request.Position -= turns;
            WristMotor.SetControl(m_request);

            //WristMotor.Set(-0.5);
        }
    ).FinallyDo(
        [this] {
            //WristMotor.Set(0);
            //WristMotor.SetControl(test);
        }
    );
}

void WristSubsystem::InitSendable(wpi::SendableBuilder& builder) { SubsystemBase::InitSendable(builder); }