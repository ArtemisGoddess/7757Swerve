#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/LiftSubsystem.h"
#include "generated/TunerConstants.h"
#include "RobotContainer.h"
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/PIDController.h>
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <Robot.h>

LiftSubsystem::LiftSubsystem() {
    m_setpoint = LiftConstants::restPID;
    controls::PositionVoltage m_initial{m_setpoint};
    controls::Follower m_follow{LiftConstants::mainLiftID, false};

    ctre::phoenix6::configs::TalonFXConfiguration config{};
        config.Feedback.WithFeedbackSensorSource(LiftConstants::rotorSensor);
        config.Slot0.WithKP(LiftConstants::kP).WithKI(LiftConstants::kI).WithKD(LiftConstants::kD);
        config.MotorOutput.WithNeutralMode(LiftConstants::liftNeutral).WithInverted(true);
    
    m_lift.GetConfigurator().Apply(config);
    l_follower1.GetConfigurator().Apply(config);
    l_follower2.GetConfigurator().Apply(config);

    m_lift.SetControl(m_initial);
    l_follower1.SetControl(m_follow);
    l_follower2.SetControl(m_follow);
}

void LiftSubsystem::raise() {
    m_lift.Set(LiftConstants::maxSpeed);
}

void LiftSubsystem::lower() {
    m_lift.Set(LiftConstants::minSpeed);
}

void LiftSubsystem::stop() {
    m_lift.Set(LiftConstants::stopSpeed);
}

void LiftSubsystem::manualRaise(units::turn_t speed) {
    controls::PositionVoltage m_request = controls::PositionVoltage{0_tr};
    units::turn_t position = m_lift.GetPosition().GetValue();

    if (speed > 0_tr) {
        m_request.WithPosition(std::min(position + speed, LiftConstants::maxPID));
    } else {
        m_request.WithPosition(std::max(position + speed, LiftConstants::restPID));
    }

    m_lift.SetControl(m_request);
}

void LiftSubsystem::setPID(units::turn_t position) {
    controls::PositionVoltage m_request = controls::PositionVoltage{position};
    m_lift.SetControl(m_request);
    m_setpoint = position;
}

void LiftSubsystem::collectAlgaePID() {
    controls::PositionVoltage m_request = controls::PositionVoltage{LiftConstants::collectAlgaePID};
    m_lift.SetControl(m_request);
    m_setpoint = LiftConstants::collectAlgaePID;
}

void LiftSubsystem::restPID() {
    controls::PositionVoltage m_request = controls::PositionVoltage{LiftConstants::restPID};
    m_lift.SetControl(m_request);
    m_setpoint = LiftConstants::restPID;
}

void LiftSubsystem::t1Coral() {
    controls::PositionVoltage m_request = controls::PositionVoltage{LiftConstants::t1PID};
    m_lift.SetControl(m_request);
    m_setpoint = LiftConstants::t1PID;
}

void LiftSubsystem::t2Coral() {
    controls::PositionVoltage m_request = controls::PositionVoltage{LiftConstants::t2PID};
    m_lift.SetControl(m_request);
    m_setpoint = LiftConstants::t2PID;
}

void LiftSubsystem::t3Coral() {
    controls::PositionVoltage m_request = controls::PositionVoltage{LiftConstants::t3PID};
    m_lift.SetControl(m_request);
    m_setpoint = LiftConstants::t3PID;
}

void LiftSubsystem::t4Coral() {
    controls::PositionVoltage m_request = controls::PositionVoltage{LiftConstants::t4PID};
    m_lift.SetControl(m_request);
    m_setpoint = LiftConstants::t4PID;
}

units::turn_t LiftSubsystem::getPIDPosition() {
    return m_lift.GetPosition().GetValue();
}

bool LiftSubsystem::isAtSetpoint() {
    return (std::abs(double(m_setpoint) - m_lift.GetPosition().GetValueAsDouble()) <= LiftConstants::PIDTolerance);
}

bool LiftSubsystem::isAtRest() {
    return (std::abs(double(LiftConstants::restPID) - m_lift.GetPosition().GetValueAsDouble()) <= LiftConstants::PIDTolerance);
}