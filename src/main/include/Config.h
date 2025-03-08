#pragma once

#include <frc/DigitalInput.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <ctre/phoenix6/CANBus.hpp>
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>
#include <Vector>
#include <ctre/phoenix6/Pigeon2.hpp>
#include <frc2/command/button/CommandXboxController.h>

inline ctre::phoenix6::CANBus CAN{""}; //The main CAN network. Use this with everything.
inline ctre::phoenix6::CANBus SwerveCAN{"SwerveMotors"}; //The swerve motor CANivore system. ONLY FOR THE SWERVE MODULES AND PIGEON.

inline frc::DigitalInput Distance{9};

inline ctre::phoenix6::hardware::Pigeon2 Pigey{0, CAN};

inline frc2::CommandXboxController joystick{0};

inline ctre::phoenix::motorcontrol::can::VictorSPX UpperIntake{6}; //Self explainitory naming scheme
inline ctre::phoenix::motorcontrol::can::VictorSPX LowerIntake{5};

inline ctre::phoenix6::hardware::TalonFX LiftMotor{99, CAN};
inline ctre::phoenix6::hardware::TalonFX LiftFollower1{98, CAN};
inline ctre::phoenix6::hardware::TalonFX LiftFollower2{97, CAN};

inline ctre::phoenix6::hardware::TalonFX ClimberMotor{20, CAN};
inline ctre::phoenix6::hardware::TalonFX ClimberFollower1{21, CAN}; //Left
inline ctre::phoenix6::hardware::TalonFX ClimberFollower2{22, CAN}; //Right

inline ctre::phoenix6::hardware::TalonFX WristMotor{15, CAN}; //Top
inline ctre::phoenix6::hardware::TalonFX WristFollower{16, CAN}; //Bottom

inline frc::Timer *TimerMagic;

inline std::vector<ctre::phoenix6::hardware::TalonFX*> TalonList{&LiftMotor, &LiftFollower1, &LiftFollower2, &ClimberMotor, &ClimberFollower1, &ClimberFollower2, &WristMotor, &WristFollower}; //A list of all the Talon Motors. Can be used in the multi-talon default config setup

//Configures a single motor for initial usage
inline void configMotorDefault(ctre::phoenix6::hardware::TalonFX TalonFX) { 
    ctre::phoenix6::configs::TalonFXConfiguration config{};

    config.Feedback.WithFeedbackSensorSource(ctre::phoenix6::signals::FeedbackSensorSourceValue::RotorSensor);
    config.Slot0.WithKP(2.4).WithKI(0).WithKD(0.1);

    TalonFX.GetConfigurator().Apply(config);
}

//Configures a vector of motors for initial usage
inline void configMotorsDefault(std::vector<ctre::phoenix6::hardware::TalonFX*> Talons) {
    ctre::phoenix6::configs::TalonFXConfiguration config{};
    config.Feedback.WithFeedbackSensorSource(ctre::phoenix6::signals::FeedbackSensorSourceValue::RotorSensor);
    config.Slot0.WithKP(2.4).WithKI(0).WithKD(0.1); //KP for motor speed
    config.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);

    for (ctre::phoenix6::hardware::TalonFX* Talon : Talons) {
        Talon->GetConfigurator().Apply(config);
    }
}

//Goes in a for loop, increments position
inline void incrmentPosition(ctre::phoenix6::controls::PositionVoltage m_request, units::angle::turn_t positionToReach, double incrementBy, double timeOver) {
    TimerMagic -> Reset();
    while (TimerMagic -> Get() <= (units::time::second_t)timeOver) {
        if (TimerMagic -> Get() == (units::time::second_t)timeOver) {
            if ((double)positionToReach > 0) {
                if ((units::angle::turn_t)m_request.Position() < positionToReach) {
                    m_request.WithPosition((units::angle::turn_t)(m_request.Position() + incrementBy));
                }
            } else {
                if ((units::angle::turn_t)m_request.Position() > positionToReach) {
                    m_request.WithPosition((units::angle::turn_t)(m_request.Position() + incrementBy));
                }
            }
        }
    }
}