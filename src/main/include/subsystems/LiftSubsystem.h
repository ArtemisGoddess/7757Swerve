#pragma once

#include "Telemetry.h" //You need this for the motors!
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h> //Subsystem things
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/DigitalInput.h>

#include <generated/TunerConstants.h>
#include "Config.h"


class LiftSubsystem : public frc2::SubsystemBase {
    public:
        LiftSubsystem();

        frc2::CommandPtr LiftUp(const units::angle::turn_t turns);

        frc2::CommandPtr LiftDown(const units::angle::turn_t turns);

        void InitSendable(wpi::SendableBuilder& builder) override;
    
    private:
        controls::PositionVoltage m_request = controls::PositionVoltage{0_tr}.WithSlot(0);
};