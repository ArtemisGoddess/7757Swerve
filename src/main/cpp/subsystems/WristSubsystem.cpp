#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/WristSubsystem.h"
#include "generated/TunerConstants.h"
#include "RobotContainer.h"
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/PIDController.h>
#include <iostream>
#include <ctre/phoenix/motorcontrol/ControlMode.h>

WristSubsystem::WristSubsystem() {
    m_setpoint = WristConstants::putAwayPID;
    controls::PositionVoltage m_initial{m_setpoint};
    controls::StrictFollower m_follow{WristConstants::mainWristID};

    ctre::phoenix6::configs::TalonFXConfiguration config{};
        config.Feedback.WithFeedbackSensorSource(WristConstants::rotorSensor);
        config.Slot0.WithKP(WristConstants::kP).WithKI(WristConstants::kI).WithKD(WristConstants::kD);
        config.MotorOutput.WithNeutralMode(WristConstants::wristNeutral);
    
    m_wrist.GetConfigurator().Apply(config);
    w_follower.GetConfigurator().Apply(config);

    m_wrist.SetControl(m_initial);
    w_follower.SetControl(m_follow);
}

void WristSubsystem::raise() {
    m_wrist.Set(WristConstants::maxSpeed);
}

void WristSubsystem::lower() {
    m_wrist.Set(WristConstants::minSpeed);
}

void WristSubsystem::stop() {
    m_wrist.Set(WristConstants::stopSpeed);
}

void WristSubsystem::manualRaise(double speed) {
    m_wrist.Set(speed);
}

void WristSubsystem::groundIntakePID() {
    controls::PositionVoltage m_request = controls::PositionVoltage{WristConstants::groundIntakePID};
    m_wrist.SetControl(m_request);
    m_setpoint = WristConstants::groundIntakePID;
}

void WristSubsystem::storePID() {
    controls::PositionVoltage m_request = controls::PositionVoltage{WristConstants::putAwayPID};
    m_wrist.SetControl(m_request);
    m_setpoint = WristConstants::putAwayPID;
}

void WristSubsystem::t1Coral() {
    controls::PositionVoltage m_request = controls::PositionVoltage{WristConstants::t1PID};
    m_wrist.SetControl(m_request);
    m_setpoint = WristConstants::t1PID;
}

void WristSubsystem::t2Coral() {
    controls::PositionVoltage m_request = controls::PositionVoltage{WristConstants::t2PID};
    m_wrist.SetControl(m_request);
    m_setpoint = WristConstants::t2PID;
}

void WristSubsystem::t3Coral() {
    controls::PositionVoltage m_request = controls::PositionVoltage{WristConstants::t3PID};
    m_wrist.SetControl(m_request);
    m_setpoint = WristConstants::t3PID;
}

void WristSubsystem::t4Coral() {
    controls::PositionVoltage m_request = controls::PositionVoltage{WristConstants::t4PID};
    m_wrist.SetControl(m_request);
    m_setpoint = WristConstants::t4PID;
}

units::turn_t WristSubsystem::getPIDPosition() {
    return m_wrist.GetPosition().GetValue();
}

bool WristSubsystem::isAtSetpoint() {
    return (std::abs(double(m_setpoint) - m_wrist.GetPosition().GetValueAsDouble()) <= WristConstants::PIDTolerance);
}

bool WristSubsystem::isPutAway() {
    return (std::abs(double(WristConstants::putAwayPID) - m_wrist.GetPosition().GetValueAsDouble()) <= WristConstants::PIDTolerance);
}