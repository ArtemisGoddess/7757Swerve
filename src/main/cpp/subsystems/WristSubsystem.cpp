#include "subsystems/WristSubsystem.h"

WristSubsystem::WristSubsystem() {
    m_setpoint = WristConstants::restPID;
    controls::PositionVoltage m_initial{m_setpoint};
    controls::Follower m_follow{WristConstants::mainWristID, false};

    ctre::phoenix6::configs::TalonFXConfiguration config{};
        config.Feedback.WithFeedbackSensorSource(WristConstants::rotorSensor);
        config.Slot0.WithKP(WristConstants::kP).WithKI(WristConstants::kI).WithKD(WristConstants::kD);
        config.MotorOutput.WithNeutralMode(WristConstants::wristNeutral).WithInverted(true);
    
    m_wrist.GetConfigurator().Apply(config);
    w_follower1.GetConfigurator().Apply(config);
    w_follower2.GetConfigurator().Apply(config);

    m_wrist.SetControl(m_initial);
    w_follower1.SetControl(m_follow);
    w_follower2.SetControl(m_follow);
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

void WristSubsystem::restPID() {
    controls::PositionVoltage m_request = controls::PositionVoltage{WristConstants::restPID};
    m_wrist.SetControl(m_request);
    m_setpoint = WristConstants::restPID;
}

void WristSubsystem::maxPID() {
    controls::PositionVoltage m_request = controls::PositionVoltage{LiftConstants::maxPID};
    m_wrist.SetControl(m_request);
    m_setpoint = LiftConstants::maxPID;
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

void WristSubsystem::collectAlgaePID() {
    controls::PositionVoltage m_request = controls::PositionVoltage{WristConstants::collectAlgaePID};
    m_wrist.SetControl(m_request);
    m_setpoint = WristConstants::collectAlgaePID;
}

void WristSubsystem::t1ReefAlgae() {
    controls::PositionVoltage m_request = controls::PositionVoltage{WristConstants::t1ReefAlgaePID};
    m_wrist.SetControl(m_request);
    m_setpoint = WristConstants::t1ReefAlgaePID;
}

void WristSubsystem::t2ReefAlgae() {
    controls::PositionVoltage m_request = controls::PositionVoltage{WristConstants::t2ReefAlgaePID};
    m_wrist.SetControl(m_request);
    m_setpoint = WristConstants::t2ReefAlgaePID;
}

void WristSubsystem::scoreNetAlgae() {
    controls::PositionVoltage m_request = controls::PositionVoltage{WristConstants::netScorePID};
    m_wrist.SetControl(m_request);
    m_setpoint = WristConstants::netScorePID;
}

void WristSubsystem::scoreProcessAlgae() {
    controls::PositionVoltage m_request = controls::PositionVoltage{WristConstants::processScorePID};
    m_wrist.SetControl(m_request);
    m_setpoint = WristConstants::processScorePID;
}

units::turn_t WristSubsystem::getPIDPosition() {
    return m_wrist.GetPosition().GetValue();
}

bool WristSubsystem::isAtSetpoint() {
    return (units::math::abs(m_setpoint - m_wrist.GetPosition().GetValue()) <= WristConstants::PIDTolerance);
}

bool WristSubsystem::isAtRest() {
    return (units::math::abs(WristConstants::restPID - m_wrist.GetPosition().GetValue()) <= WristConstants::PIDTolerance);
}