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

inline nt::NetworkTableInstance m_inst = nt::NetworkTableInstance::GetDefault();
inline std::shared_ptr<nt::NetworkTable> slam = m_inst.GetTable("slam");
inline std::shared_ptr<nt::NetworkTable> limelight = m_inst.GetTable("limelight");

inline frc::DigitalInput Distance{9};

inline ctre::phoenix6::hardware::Pigeon2 Pigey{0, CAN};

inline frc2::CommandXboxController joystick{0};

inline ctre::phoenix::motorcontrol::can::VictorSPX UpperIntake{6}; //Self explainitory naming scheme
inline ctre::phoenix::motorcontrol::can::VictorSPX LowerIntake{5};

inline ctre::phoenix6::hardware::TalonFX LiftMotor{99, CAN};
inline ctre::phoenix6::hardware::TalonFX LiftFollower1{98, CAN};
inline ctre::phoenix6::hardware::TalonFX LiftFollower2{97, CAN};

inline ctre::phoenix6::hardware::TalonFX ClimberMotor{100, CAN};
inline ctre::phoenix6::hardware::TalonFX ClimberFollower1{101, CAN}; //Left
inline ctre::phoenix6::hardware::TalonFX ClimberFollower2{102, CAN}; //Right

inline ctre::phoenix6::hardware::TalonFX WristMotor{15, CAN}; //Top
inline ctre::phoenix6::hardware::TalonFX WristFollower{16, CAN}; //Bottom

//inline frc::Timer *TimerMagic;

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
    config.Slot0.WithKP(4.4).WithKI(0).WithKD(0.1); //KP for motor speed
    config.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);

    for (ctre::phoenix6::hardware::TalonFX* Talon : Talons) {
        Talon->GetConfigurator().Apply(config);
        Talon->SetSafetyEnabled(false);
    }
}

inline void testConfig(std::vector<ctre::phoenix6::hardware::TalonFX*> Talons) {
    ctre::phoenix6::configs::TalonFXConfiguration config{};
    config.Feedback.WithFeedbackSensorSource(ctre::phoenix6::signals::FeedbackSensorSourceValue::RotorSensor);
    auto& slot0Configs = config.Slot0;
    slot0Configs.kS = 0.25; // Add 0.25 V output to overcome static friction
    slot0Configs.kV = 0.12; // A velocity target of 1 rps results in 0.12 V output
    slot0Configs.kA = 0.01; // An acceleration of 1 rps/s requires 0.01 V output
    slot0Configs.kP = 4.8; // A position error of 2.5 rotations results in 12 V output
    slot0Configs.kI = 0; // no output for integrated error
    slot0Configs.kD = 0.1; // A velocity error of 1 rps results in 0.1 V output

    auto& motionMagicConfigs = config.MotionMagic;
    motionMagicConfigs.MotionMagicCruiseVelocity = 80_tps; // Target cruise velocity of 80 rps
    motionMagicConfigs.MotionMagicAcceleration = 160_tr_per_s_sq; // Target acceleration of 160 rps/s (0.5 seconds)
    motionMagicConfigs.MotionMagicJerk = 1600_tr_per_s_cu;


    for (ctre::phoenix6::hardware::TalonFX* Talon : Talons) {
        Talon->GetConfigurator().Apply(config);
    }
}

//Goes in a for loop, increments position
/*inline void incrmentPosition(ctre::phoenix6::controls::PositionVoltage m_request, units::angle::turn_t positionToReach, double incrementBy, double timeOver) {
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
}*/