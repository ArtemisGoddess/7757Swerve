#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <ctre/phoenix6/CANBus.hpp>
#include <ctre/phoenix6/TalonFX.hpp>

ctre::phoenix6::CANBus canNet{"", "./logs/example.hoot"};

ctre::phoenix::motorcontrol::can::VictorSPX victor{5};

ctre::phoenix6::hardware::TalonFX T_Motor{11, canNet};

ctre::phoenix6::hardware::TalonFX motor{12, canNet};

ctre::phoenix6::hardware::TalonFX ArmMotor{10, canNet};