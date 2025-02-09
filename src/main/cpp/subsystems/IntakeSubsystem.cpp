#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/IntakeSubsystem.h"
#include "generated/TunerConstants.h"
#include "RobotContainer.h"
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/PIDController.h>
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <Robot.h>

frc::DigitalInput sensor{9};

IntakeSubsystem::IntakeSubsystem() {}

frc2::CommandPtr IntakeSubsystem::Intake(const units::angle::turn_t turns) {
    return this->Run(
        [this, turns] {
            if (sensor.Get()) {
                T_Motor.SetControl(a_request.WithPosition(a_request.Position + turns));
            }
        }
    );
}

double IntakeSubsystem::getRots() {
    return a_request.Position();
}

void IntakeSubsystem::setConfig() {
    configs::TalonFXConfiguration config{};

    config.Feedback.WithFeedbackSensorSource(signals::FeedbackSensorSourceValue::RotorSensor);
    config.Slot0.WithKP(2.4).WithKI(0).WithKD(0.1);
    //.WithKS(0.25).WithKV(0.12)

    T_Motor.GetConfigurator().Apply(config);
}

void IntakeSubsystem::InitSendable(wpi::SendableBuilder& builder) {
    SubsystemBase::InitSendable(builder);
}