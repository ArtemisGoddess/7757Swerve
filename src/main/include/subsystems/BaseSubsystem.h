#pragma once

#include "Telemetry.h"
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/DigitalInput.h>
#include "Config.h"

#include <generated/TunerConstants.h>

class BaseSubsystem : public frc2::SubsystemBase {
    public:
        BaseSubsystem(); //initilizaer

        frc2::CommandPtr testPointer(); //Base CommandPtr function

        void InitSendable(wpi::SendableBuilder& builder) override; //Command scheduler

    private:
        //Variables or objects go here, like position requests or the drivetrain
};