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

inline ctre::phoenix6::hardware::TalonFX UpperIntake{12, CAN}; //Self explainitory naming scheme
inline ctre::phoenix6::hardware::TalonFX LowerIntake{11, CAN};

inline ctre::phoenix6::hardware::TalonFX LiftMotor{99, CAN};
inline ctre::phoenix6::hardware::TalonFX LiftFollower1{98, CAN};
inline ctre::phoenix6::hardware::TalonFX LiftFollower2{97, CAN};

inline ctre::phoenix6::hardware::TalonFX ClimberMotor{20, CAN};
inline ctre::phoenix6::hardware::TalonFX ClimberFollower1{21, CAN}; //Left
inline ctre::phoenix6::hardware::TalonFX ClimberFollower2{22, CAN}; //Right

inline ctre::phoenix6::hardware::TalonFX WristMotor{15, CAN}; //Top
inline ctre::phoenix6::hardware::TalonFX WristFollower{16, CAN}; //Bottom

//inline frc::Timer *TimerMagic;

inline std::vector<ctre::phoenix6::hardware::TalonFX*> TalonList{&LiftMotor, &LiftFollower1, &LiftFollower2, &ClimberMotor, &ClimberFollower1, &ClimberFollower2, &UpperIntake, &LowerIntake}; //A list of all the Talon Motors. Can be used in the multi-talon default config setup
inline std::vector<ctre::phoenix6::hardware::TalonFX*> WristTalonList{&WristMotor, &WristFollower}; //A list of all the Talon Motors. Can be used in the multi-talon default config setup

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
    config.Slot0.WithKP(2.4).WithKI(0).WithKD(0.1); //KP for motor speed << This is technically right and wrong
    config.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);

    for (ctre::phoenix6::hardware::TalonFX* Talon : Talons) {
        Talon->GetConfigurator().Apply(config);
    }
}

inline void configWristDefault(std::vector<ctre::phoenix6::hardware::TalonFX*> Talons) {
    ctre::phoenix6::configs::TalonFXConfiguration config{};
    config.Feedback.WithFeedbackSensorSource(ctre::phoenix6::signals::FeedbackSensorSourceValue::RotorSensor);
    config.Slot0.WithKP(2.4).WithKI(0).WithKD(0.1); //KP for motor speed << This is technically right and wrong
    config.Voltage.WithPeakForwardVoltage(12_V).WithPeakReverseVoltage(-12_V);
    config.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);
    config.MotorOutput.WithInverted(true);

    for (ctre::phoenix6::hardware::TalonFX* Talon : Talons) {
        Talon->GetConfigurator().Apply(config);
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

// port 0 digital imput
// Y high
// A low