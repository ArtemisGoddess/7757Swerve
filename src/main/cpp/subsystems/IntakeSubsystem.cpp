#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/IntakeSubsystem.h"
#include "generated/TunerConstants.h"
#include "RobotContainer.h"
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/PIDController.h>
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <Robot.h>

IntakeSubsystem::IntakeSubsystem() {}

frc2::CommandPtr IntakeSubsystem::IntakeCoral() {
    return this->Run(
        [this] {
            if (Distance.Get()) {
                UpperIntake.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.8);
            } else {
                UpperIntake.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
            }
        }
    ).FinallyDo(
        [this] {
            UpperIntake.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
        }
    );
}

frc2::CommandPtr IntakeSubsystem::OuttakeCoral() {
    return this->Run(
        [this] {
            UpperIntake.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.8);
        }
    ).FinallyDo(
        [this] {
            UpperIntake.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
        }
    );
}

frc2::CommandPtr IntakeSubsystem::IntakeAlgae() {
    return this->RunOnce(
        [this] {
            LowerIntake.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.8);
            UpperIntake.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, -0.8);
        }
    ).FinallyDo(
        [this] {
            LowerIntake.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
            UpperIntake.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, -0.0);
        }
    );
}

frc2::CommandPtr IntakeSubsystem::OuttakeAlgae() {
    return this->RunOnce(
        [this] {
            LowerIntake.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, -0.8);
            UpperIntake.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.8);
        }
    ).FinallyDo(
        [this] {
            LowerIntake.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.0);
            UpperIntake.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, -0.0);
        }
    );
}

void IntakeSubsystem::InitSendable(wpi::SendableBuilder& builder) {
    SubsystemBase::InitSendable(builder);
}