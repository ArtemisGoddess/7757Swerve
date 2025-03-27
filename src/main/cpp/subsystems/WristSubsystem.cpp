#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/WristSubsystem.h"
#include "generated/TunerConstants.h"
#include "RobotContainer.h"
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/PIDController.h>
#include <iostream>
#include <ctre/phoenix/motorcontrol/ControlMode.h>

WristSubsystem::WristSubsystem() {
    m_setpoint = WristConstants::restPID;
    controls::PositionVoltage m_initial{m_setpoint};
    controls::Follower m_follow{WristConstants::mainWristID, false};

    ctre::phoenix6::configs::TalonFXConfiguration config{};
        config.Feedback.WithFeedbackSensorSource(WristConstants::rotorSensor);
        config.Slot0.WithKP(WristConstants::kP).WithKI(WristConstants::kI).WithKD(WristConstants::kD);
        config.MotorOutput.WithNeutralMode(WristConstants::wristNeutral).WithInverted(true);
    
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

void WristSubsystem::manualRaise(units::turn_t speed) {
    controls::PositionVoltage m_request = controls::PositionVoltage{0_tr};
    units::turn_t position = m_wrist.GetPosition().GetValue();

    if (speed > 0_tr) {
        m_request.WithPosition(std::min(position + speed, WristConstants::maxPID));
    } else {
        m_request.WithPosition(std::max(position + speed, WristConstants::restPID));
    }

    m_wrist.SetControl(m_request);
}

void WristSubsystem::setPID(units::turn_t position) {
    controls::PositionVoltage m_request = controls::PositionVoltage{position};
    m_wrist.SetControl(m_request);
    m_setpoint = position;
}

void WristSubsystem::collectAlgaePID() {
    controls::PositionVoltage m_request = controls::PositionVoltage{WristConstants::collectAlgaePID};
    m_wrist.SetControl(m_request);
    m_setpoint = WristConstants::collectAlgaePID;
}

void WristSubsystem::restPID() {
    controls::PositionVoltage m_request = controls::PositionVoltage{WristConstants::restPID};
    m_wrist.SetControl(m_request);
    m_setpoint = WristConstants::restPID;
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

bool WristSubsystem::isAtRest() {
    return (std::abs(double(WristConstants::restPID) - m_wrist.GetPosition().GetValueAsDouble()) <= WristConstants::PIDTolerance);
}