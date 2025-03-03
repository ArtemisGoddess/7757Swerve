#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/TestSubsystem.h"
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/PIDController.h>
#include <iostream>
#include <ctre/phoenix/motorcontrol/ControlMode.h>

TestSubsystem::TestSubsystem() {}

frc2::CommandPtr TestSubsystem::SetMotorPosition(const units::angle::turn_t turns) {
    return this->RunOnce(
        [this, turns] {
            //T_Motor.SetControl(m_request.WithPosition(m_request.Position + turns));
            //T_Motor.SetControl(controls::MotionMagicVoltage{100_tr});
            //T_Motor.Set(0.1);
            //m_request.Position;
        }
    );
}

frc2::CommandPtr TestSubsystem::testtest(const units::angle::turn_t turns) {
    return this->Run(
        [this, turns] {
            if (Distance.Get()) {
                //victor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.1);
            } else {
                //victor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
            }
            
            //victor.Set(ctre::phoenix::motorcontrol::ControlMode::Position, 100);
            //T_Motor.SetControl(m_request.WithPosition(turns));
            //T_Motor.SetControl(controls::MotionMagicVoltage{100_tr});
            //T_Motor.Set(0.1);
            //m_request.Position;
        }
    );
}

frc2::CommandPtr TestSubsystem::victorOff() {
    return this->RunOnce(
        [this] {
            //victor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
        }
    );
}

void TestSubsystem::InitSendable(wpi::SendableBuilder& builder) {
    SubsystemBase::InitSendable(builder);
}