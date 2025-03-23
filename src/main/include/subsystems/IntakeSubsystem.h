#pragma once

#include "Telemetry.h" //You need this for the motors!
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h> //Subsystem things
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/DigitalInput.h>

#include <generated/TunerConstants.h>
#include "Config.h"


class IntakeSubsystem : public frc2::SubsystemBase {
    public:
        IntakeSubsystem();

        frc2::CommandPtr Intake(double speed);

        frc2::CommandPtr Outtake(double speed);

        void InitSendable(wpi::SendableBuilder& builder) override;
    private:
        controls::PositionVoltage m_request = controls::PositionVoltage{0_tr}.WithSlot(0).WithOverrideBrakeDurNeutral(true);
};