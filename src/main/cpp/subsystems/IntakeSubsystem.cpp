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

frc2::CommandPtr IntakeSubsystem::RunIntake(double speed) {
    return this->Run(
        [this, speed] {
            UpperIntake.Set(speed);
            //UpperIntake.SetPosition(0_tr);
            //UpperIntake.SetControl(m_request);
        }
    ).FinallyDo(
        [this] {
            UpperIntake.Set(0);
            //UpperIntake.SetPosition(0_tr);
            //UpperIntake.SetControl(m_request);
        }
    );
}

void IntakeSubsystem::InitSendable(wpi::SendableBuilder& builder) { SubsystemBase::InitSendable(builder); }