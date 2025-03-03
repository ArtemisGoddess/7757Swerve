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

        frc2::CommandPtr IntakeCoral();

        frc2::CommandPtr OuttakeCoral();

        frc2::CommandPtr IntakeAlgae();

        frc2::CommandPtr OuttakeAlgae();

        void InitSendable(wpi::SendableBuilder& builder) override;
};