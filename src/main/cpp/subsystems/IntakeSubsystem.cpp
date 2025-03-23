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
            UpperIntake.Set(-0.3);
            //UpperIntake.SetPosition(0_tr);
            //UpperIntake.SetControl(m_request);
        }
    ).FinallyDo(
        [this] { 
            UpperIntake.Set(-0.0);
            //UpperIntake.SetPosition(0_tr);

            //UpperIntake.SetControl(m_request);

        }
    );
}

frc2::CommandPtr IntakeSubsystem::Outtake() {
    return this->Run(
        [this] {
            UpperIntake.Set(1);
            //UpperIntake.SetPosition(0_tr);
            //UpperIntake.SetControl(m_request);
        }
    ).FinallyDo(
        [this] {
            UpperIntake.Set(-0.0);
            //UpperIntake.SetPosition(0_tr);
            //UpperIntake.SetControl(m_request);
        }
    );
}

void IntakeSubsystem::InitSendable(wpi::SendableBuilder& builder) { SubsystemBase::InitSendable(builder); }