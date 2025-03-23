#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/auto/AutoSubsystem.h"
#include "generated/TunerConstants.h"
#include <frc/controller/PIDController.h>
#include <iostream>
#include <ctre/phoenix/motorcontrol/ControlMode.h>
#include "Config.h"
AutoSubsystem::AutoSubsystem() {} //Initilizer

frc2::CommandPtr AutoSubsystem::testPointer() { //Basic commandPtr constructer
    return this->RunOnce(
        [this] {
            //Code goes here, as you would a periodic robot command. Ish.
        }
    );
}
frc2::CommandPtr AutoSubsystem::Outtake() {
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
void AutoSubsystem::InitSendable(wpi::SendableBuilder& builder) { SubsystemBase::InitSendable(builder); } //required to schedule the subsystem