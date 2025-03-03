#pragma once

#include "Telemetry.h" //You need this for the motors!
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h> //Subsystem things
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/DigitalInput.h>
#include "Config.h"

#include <generated/TunerConstants.h>


class ArmSubsystem : public frc2::SubsystemBase {
    public:
        ArmSubsystem();

         frc2::CommandPtr SetMotorPosition(units::angle::turn_t turns);

        frc2::CommandPtr testtest(units::angle::turn_t turns);

        frc2::CommandPtr victorOff();

        void InitSendable(wpi::SendableBuilder& builder) override;

        void setConfig();

        void test();

        bool sensorBool1;

    private:
        //ctre::phoenix6::hardware::TalonFX A_Motor{12, can};

        controls::PositionVoltage a_request = controls::PositionVoltage{0_tr}.WithSlot(0);
};