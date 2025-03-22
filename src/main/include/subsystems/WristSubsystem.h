#pragma once

#include "Telemetry.h" //You need this for the motors!
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h> //Subsystem things
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/DigitalInput.h>
#include "Config.h"

#include <generated/TunerConstants.h>


class WristSubsystem : public frc2::SubsystemBase {
    public:
        WristSubsystem();

        frc2::CommandPtr Wrist(units::angle::turn_t turns); //For auto, and so I don't cry

        frc2::CommandPtr WristLeft();

        frc2::CommandPtr WristRight();

        void InitSendable(wpi::SendableBuilder& builder) override;

    private:
        //ctre::phoenix6::hardware::TalonFX A_Motor{12, can};

        controls::PositionVoltage m_request = controls::PositionVoltage{0_tr}.WithSlot(0).WithOverrideBrakeDurNeutral(true);
};