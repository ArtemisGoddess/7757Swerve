#include "subsystems/LiftSubsystem.h"

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

void LiftSubsystem::restPID() {
    controls::PositionVoltage m_request = controls::PositionVoltage{LiftConstants::restPID};
    m_lift.SetControl(m_request);
    m_setpoint = LiftConstants::restPID;
}

void LiftSubsystem::maxPID() {
    controls::PositionVoltage m_request = controls::PositionVoltage{LiftConstants::maxPID};
    m_lift.SetControl(m_request);
    m_setpoint = LiftConstants::maxPID;
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

void LiftSubsystem::collectAlgaePID() {
    controls::PositionVoltage m_request = controls::PositionVoltage{LiftConstants::collectAlgaePID};
    m_lift.SetControl(m_request);
    m_setpoint = LiftConstants::collectAlgaePID;
}

void LiftSubsystem::t1ReefAlgae() {
    controls::PositionVoltage m_request = controls::PositionVoltage{LiftConstants::t1ReefAlgaePID};
    m_lift.SetControl(m_request);
    m_setpoint = LiftConstants::t1ReefAlgaePID;
}

void LiftSubsystem::t2ReefAlgae() {
    controls::PositionVoltage m_request = controls::PositionVoltage{LiftConstants::t2ReefAlgaePID};
    m_lift.SetControl(m_request);
    m_setpoint = LiftConstants::t2ReefAlgaePID;
}

void LiftSubsystem::scoreNetAlgae() {
    controls::PositionVoltage m_request = controls::PositionVoltage{LiftConstants::netScorePID};
    m_lift.SetControl(m_request);
    m_setpoint = LiftConstants::netScorePID;
}

void LiftSubsystem::scoreProcessAlgae() {
    controls::PositionVoltage m_request = controls::PositionVoltage{LiftConstants::processScorePID};
    m_lift.SetControl(m_request);
    m_setpoint = LiftConstants::processScorePID;
}

units::turn_t LiftSubsystem::getPIDPosition() {
    return m_lift.GetPosition().GetValue();
}

bool LiftSubsystem::isAtSetpoint() {
    return (units::math::abs(m_setpoint - m_lift.GetPosition().GetValue()) <= LiftConstants::PIDTolerance);
}

bool LiftSubsystem::isAtRest() {
    return (units::math::abs(LiftConstants::restPID - m_lift.GetPosition().GetValue()) <= LiftConstants::PIDTolerance);
}