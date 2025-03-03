#pragma once

#include "Telemetry.h" //You need this for the motors!
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h> //Subsystem things
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/DigitalInput.h>
#include "Config.h"

#include <generated/TunerConstants.h>


class ClimberSubsystem : public frc2::SubsystemBase {
    public:
        ClimberSubsystem();

        frc2::CommandPtr ClimbUp();

        void InitSendable(wpi::SendableBuilder& builder) override;

    private:
        //ctre::phoenix6::hardware::TalonFX A_Motor{12, can};

        controls::PositionVoltage m_request = controls::PositionVoltage{0_tr}.WithSlot(0);
};