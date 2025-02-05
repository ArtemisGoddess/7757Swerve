#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/MotorTurn.h"
#include "generated/TunerConstants.h"
#include "RobotContainer.h"
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/PIDController.h>
#include <iostream>

MotorTurn::MotorTurn() {
}

frc2::CommandPtr MotorTurn::TurnLeft() {
    return this->RunOnce([this] {T_Motor.Set(1);});
}

frc2::CommandPtr MotorTurn::TurnRight() {
    return this->RunOnce([this] {T_Motor.Set(-0.1);}
    
    );
}

frc2::CommandPtr MotorTurn::StopIt() {
    return this->RunOnce([this] {T_Motor.Disable();}

    );
}

frc2::CommandPtr MotorTurn::SetMotorPosition(const units::angle::turn_t turns) {
    units::angle::turn_t totalTurns;


    return this->RunOnce(
        [this, turns] {
            T_Motor.SetControl(m_request.WithPosition(m_request.Position + turns));
            //T_Motor.SetControl(controls::MotionMagicVoltage{100_tr});
            //T_Motor.Set(0.1);
            //m_request.Position;
        }
    );
}

frc2::CommandPtr MotorTurn::testtest(const units::angle::turn_t turns) {
    return this->RunOnce(
        [this, turns] {
            T_Motor.SetControl(m_request.WithPosition(turns));
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

    T_Motor.GetConfigurator().Apply(config);
}

void MotorTurn::test() {
    T_Motor.SetControl(m_request.WithPosition(0_tr));
}

void MotorTurn::InitSendable(wpi::SendableBuilder& builder) {
    SubsystemBase::InitSendable(builder);
}

/*void MotorTurn::magicThings(ctre::phoenix6::hardware::TalonFX motor) {
    frc::TrapezoidProfile<units::angle::turn_t> m_profile{{80_tps, 160_tr_per_s_sq}};
    // Final target of 200 rot, 0 rps
    frc::TrapezoidProfile<units::turn_t>::State m_goal{200_tr, 0_tps};
    frc::TrapezoidProfile<units::turn_t>::State m_setpoint{};

    // create a position closed-loop request, voltage output, slot 0 configs
    controls::PositionVoltage m_request = controls::PositionVoltage{0_tr}.WithSlot(2);

    // calculate the next profile setpoint
    m_setpoint = m_profile.Calculate(20_ms, m_setpoint, m_goal);

    // send the request to the device
    m_request.Position = m_setpoint.position;
    m_request.Velocity = m_setpoint.velocity;
    motor.SetControl(m_request);
}*/