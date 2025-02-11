#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/MotorTurn.h"
#include "generated/TunerConstants.h"
#include "RobotContainer.h"
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/PIDController.h>
#include <iostream>

MotorTurn::MotorTurn() {
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

frc2::CommandPtr MotorTurn::testtest(const units::angle::turn_t turns) {
    return this->RunOnce(
        [this, turns] {
            //T_Motor.SetControl(m_request.WithPosition(turns));
            //T_Motor.SetControl(controls::MotionMagicVoltage{100_tr});
            //T_Motor.Set(0.1);
            //m_request.Position;
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

void MotorTurn::test() {
    //T_Motor.Set(0);
}

void MotorTurn::InitSendable(wpi::SendableBuilder& builder) {
    SubsystemBase::InitSendable(builder);
}