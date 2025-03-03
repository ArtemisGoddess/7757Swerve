#include <frc/DigitalInput.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <ctre/phoenix6/CANBus.hpp>
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>
#include <Vector>

ctre::phoenix6::CANBus CAN{""}; //The main CAN network. Use this with everything.
ctre::phoenix6::CANBus SwerveCAN{"Motors"}; //The swerve motor CANivore system. ONLY FOR THE SWERVE MODULES.

frc::DigitalInput Distance{9};

ctre::phoenix6::hardware::Pigeon2 Pigey{0, CAN};

ctre::phoenix::motorcontrol::can::VictorSPX UpperIntake{5}; //Self explainitory naming scheme
ctre::phoenix::motorcontrol::can::VictorSPX LowerIntake{5};

ctre::phoenix6::hardware::TalonFX A_Motor{12, CAN};

ctre::phoenix6::hardware::TalonFX motor{12, CAN};

ctre::phoenix6::hardware::TalonFX ArmMotor{10, CAN};

ctre::phoenix6::hardware::TalonFX LiftMotor{10, CAN};
ctre::phoenix6::hardware::TalonFX LiftFollower1{10, CAN};
ctre::phoenix6::hardware::TalonFX LiftFollower2{10, CAN};

std::vector<ctre::phoenix6::hardware::TalonFX*> TalonList{&A_Motor, &motor, &ArmMotor, &LiftMotor, &LiftFollower1, &LiftFollower2}; //A list of all the Talon Motors. Can be used in the multi-talon default config setup

//Configures a single motor for initial usage
void configMotorDefault(ctre::phoenix6::hardware::TalonFX TalonFX) { 
    ctre::phoenix6::configs::TalonFXConfiguration config{};

    config.Feedback.WithFeedbackSensorSource(ctre::phoenix6::signals::FeedbackSensorSourceValue::RotorSensor);
    config.Slot0.WithKP(2.4).WithKI(0).WithKD(0.1);

    TalonFX.GetConfigurator().Apply(config);
}

//Configures a vector of motors for initial usage
void configMotorsDefault(std::vector<ctre::phoenix6::hardware::TalonFX*> Talons) {
    ctre::phoenix6::configs::TalonFXConfiguration config{};
    config.Feedback.WithFeedbackSensorSource(ctre::phoenix6::signals::FeedbackSensorSourceValue::RotorSensor);
    config.Slot0.WithKP(2.4).WithKI(0).WithKD(0.1);

    for (ctre::phoenix6::hardware::TalonFX* Talon : Talons) {
        Talon->GetConfigurator().Apply(config);
    }
}