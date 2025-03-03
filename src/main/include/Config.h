#include <frc/DigitalInput.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <ctre/phoenix6/CANBus.hpp>
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>

ctre::phoenix6::CANBus CAN{"", "./logs/example.hoot"}; //The main CAN network. Note: Rebind this to the CANivore

frc::DigitalInput Distance{9};

ctre::phoenix::motorcontrol::can::VictorSPX victor{5};

ctre::phoenix6::hardware::TalonFX A_Motor{12, CAN};

ctre::phoenix6::hardware::TalonFX T_Motor{11, CAN};

ctre::phoenix6::hardware::TalonFX motor{12, CAN};

ctre::phoenix6::hardware::TalonFX ArmMotor{10, CAN};

//Sets up a single motor for initial usage
void configMotorDefault(ctre::phoenix6::hardware::TalonFX TalonFX) { 
    ctre::phoenix6::configs::TalonFXConfiguration config{};

    config.Feedback.WithFeedbackSensorSource(ctre::phoenix6::signals::FeedbackSensorSourceValue::RotorSensor);
    config.Slot0.WithKP(2.4).WithKI(0).WithKD(0.1);

    TalonFX.GetConfigurator().Apply(config);
}