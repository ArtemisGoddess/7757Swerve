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

frc2::CommandPtr IntakeSubsystem::Intake() {
    return this->Run(
        [this] {
            LowerIntake.Set(0.8);
            UpperIntake.Set(-0.8);
        }
    ).FinallyDo(
        [this] {
            LowerIntake.Set(0.0);
            UpperIntake.Set(-0.0);
        }
    );
}

frc2::CommandPtr IntakeSubsystem::Outtake() {
    return this->Run(
        [this] {
            LowerIntake.Set(-0.8);
            UpperIntake.Set(0.8);
        }
    ).FinallyDo(
        [this] {
            LowerIntake.Set(0.0);
            UpperIntake.Set(-0.0);
        }
    );
}

void IntakeSubsystem::InitSendable(wpi::SendableBuilder& builder) { SubsystemBase::InitSendable(builder); }