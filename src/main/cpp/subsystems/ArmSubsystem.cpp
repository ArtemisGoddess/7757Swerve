#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/ArmSubsystem.h"
#include "generated/TunerConstants.h"
#include "RobotContainer.h"
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/PIDController.h>
#include <iostream>
#include <ctre/phoenix/motorcontrol/ControlMode.h>

frc::DigitalInput sensor{9};

ArmSubsystem::ArmSubsystem() {

}

frc2::CommandPtr MotorTurn::SetMotorPosition(const units::angle::turn_t turns) {
    return this->RunOnce(
        [this, turns] {
            //T_Motor.SetControl(m_request.WithPosition(m_request.Position + turns));
            //T_Motor.SetControl(controls::MotionMagicVoltage{100_tr});
            //T_Motor.Set(0.1);
            //m_request.Position;
        }
    );
}

frc2::CommandPtr ArmSubsystem::testtest(const units::angle::turn_t turns) {
    return this->Run(
        [this, turns] {
            if (sensor.Get()) {
                A_Motor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.1);
            } else {
                A_Motor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
            }
            
            //victor.Set(ctre::phoenix::motorcontrol::ControlMode::Position, 100);
            //T_Motor.SetControl(m_request.WithPosition(turns));
            //T_Motor.SetControl(controls::MotionMagicVoltage{100_tr});
            //T_Motor.Set(0.1);
            //m_request.Position;
        }
    );
}

frc2::CommandPtr ArmSubsystem::victorOff() {
    return this->RunOnce(
        [this] {
            A_Motor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
        }
    );
}

void MotorTurn::setConfig() {
    configs::TalonFXConfiguration config{};

    config.Feedback.WithFeedbackSensorSource(signals::FeedbackSensorSourceValue::RotorSensor);
    config.Slot0.WithKP(2.4).WithKI(0).WithKD(0.1);
    //.WithKS(0.25).WithKV(0.12)

    //T_Motor.GetConfigurator().Apply(config);
}

void ArmSubsystem::test() {
    //T_Motor.Set(0);
}

void ArmSubsystem::InitSendable(wpi::SendableBuilder& builder) {
    SubsystemBase::InitSendable(builder);
}