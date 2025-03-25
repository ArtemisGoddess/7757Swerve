#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/IntakeSubsystem.h"
#include "generated/TunerConstants.h"
#include "RobotContainer.h"
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/PIDController.h>
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <Robot.h>

IntakeSubsystem::IntakeSubsystem() {
    intakeActive = false;
    intakeDirectionVal = 0;
    controls::Follower m_follow{IntakeConstants::mainIntakeID, true};

    ctre::phoenix6::configs::TalonFXConfiguration config{};
        config.Feedback.WithFeedbackSensorSource(WristConstants::rotorSensor);
        config.Slot0.WithKP(IntakeConstants::kP).WithKI(IntakeConstants::kI).WithKD(IntakeConstants::kD);
        config.MotorOutput.WithNeutralMode(WristConstants::wristNeutral);
    
    m_intake.GetConfigurator().Apply(config);
    i_follower.GetConfigurator().Apply(config);

    i_follower.SetControl(m_follow);
}

void IntakeSubsystem::intake(double speed) {
    m_intake.Set(std::min(speed, IntakeConstants::maxSpeed));
    intakeActive = true;
    intakeDirectionVal = 1; 
}

void IntakeSubsystem::outtake(double speed) {
    m_intake.Set(std::max(-speed, IntakeConstants::minSpeed));
    intakeActive = true;
    intakeDirectionVal = 2;
}

void IntakeSubsystem::stop() {
    m_intake.Set(IntakeConstants::stopSpeed);
    intakeActive = false;
    intakeDirectionVal = 0;
}

bool IntakeSubsystem::isIntaking() {
    return intakeActive;
}

int IntakeSubsystem::intakeDirection() {
    return intakeDirectionVal;
}