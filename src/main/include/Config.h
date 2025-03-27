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

inline ctre::phoenix6::hardware::Pigeon2 Pigey{0, SwerveCAN};

inline frc2::CommandXboxController joystick{0};

inline ctre::phoenix6::hardware::TalonFX ClimberMotor{20, CAN};
inline ctre::phoenix6::hardware::TalonFX ClimberFollower1{21, CAN}; //Left
inline ctre::phoenix6::hardware::TalonFX ClimberFollower2{22, CAN}; //Right

inline std::vector<ctre::phoenix6::hardware::TalonFX*> TalonList{&ClimberMotor, &ClimberFollower1, &ClimberFollower2}; //A list of all the Talon Motors. Can be used in the multi-talon default config setup

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


//Not to be confused with TunerConstants, this is for subsystem control.
class DrivebaseConstants {
    public:
        static constexpr units::radians_per_second_t MaxAngularRate = 0.75_tps;
        static constexpr units::meters_per_second_t MaxSpeed = 4.73_mps;
};

class WristConstants {
    public:
        //Base settings
        static constexpr int mainWristID = 15;
        static constexpr int followerWristID = 16;
        static constexpr int rotorSensor = 0;
        static constexpr int wristNeutral = 1;
        static constexpr double maxSpeed = 0.8;
        static constexpr double minSpeed = -0.8;
        static constexpr int stopSpeed = 0;
        static constexpr double PIDTolerance = 0.05;
        static constexpr double kP = 2.4;
        static constexpr int kI = 0;
        static constexpr int kD = 0;

        //PID for intake/storing
        static constexpr units::turn_t restPID = 0_tr;
        static constexpr units::turn_t maxPID = 2.76_tr;

        //PID for coral scoring
        static constexpr units::turn_t t1PID = 2_tr;
        static constexpr units::turn_t t2PID = 0_tr;
        static constexpr units::turn_t t3PID = 0_tr;
        static constexpr units::turn_t t4PID = 0_tr;

        //Constants for coral
        static constexpr double coralSpeed = 0.3;

        //PID for algae scoring
        static constexpr units::turn_t collectAlgaePID = 2.76_tr;
        static constexpr units::turn_t netScorePID = 0_tr;
        static constexpr units::turn_t processScorePID = 0_tr;

        //Constants for algae
        static constexpr double algaeSpeed = 0.3;
};

class LiftConstants {
    public:
        //Base settings
        static constexpr int mainLiftID = 99;
        static constexpr int followerLiftID1 = 98;
        static constexpr int followerLiftID2 = 97;
        static constexpr int rotorSensor = 0;
        static constexpr int liftNeutral = 1;
        static constexpr double maxSpeed = 0.8;
        static constexpr double minSpeed = -0.8;
        static constexpr int stopSpeed = 0;
        static constexpr double PIDTolerance = 0.05;
        static constexpr double kP = 2.4;
        static constexpr int kI = 0;
        static constexpr int kD = 0;

        //PID for intake/storing/maximum position
        static constexpr units::turn_t restPID = 0_tr;
        static constexpr units::turn_t maxPID = 4_tr;
        

        //PID for coral scoring
        static constexpr units::turn_t t1PID = 0_tr;
        static constexpr units::turn_t t2PID = 0_tr;
        static constexpr units::turn_t t3PID = 0_tr;
        static constexpr units::turn_t t4PID = 0_tr;

        //Constants for coral
        static constexpr double coralSpeed = 0.3;
        static constexpr double coralkP = 2.4;
        static constexpr int coralkI = 0;
        static constexpr int coralkD = 0;

        //PID for algae scoring
        static constexpr units::turn_t collectAlgaePID = 0_tr;
        static constexpr units::turn_t netScorePID = 0_tr;
        static constexpr units::turn_t processScorePID = 0_tr;

        //Constants for algae
        static constexpr double algaeSpeed = 0.3;
        static constexpr double algaekP = 2.4;
        static constexpr int algaekI = 0;
        static constexpr int algaekD = 0;
};

class IntakeConstants {
    public:
        //Base settings
        static constexpr int mainIntakeID = 12;
        static constexpr int followerIntakeID = 11;
        static constexpr int liftNeutral = 1;
        static constexpr double maxSpeed = 0.8;
        static constexpr double minSpeed = -0.8;
        static constexpr int stopSpeed = 0;
        static constexpr double kP = 2.4;
        static constexpr int kI = 0;
        static constexpr int kD = 0;
};