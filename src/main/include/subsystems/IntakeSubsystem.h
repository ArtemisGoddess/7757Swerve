#pragma once

#include "Telemetry.h" //You need this for the motors!
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h> //Subsystem things
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/DigitalInput.h>

#include <generated/TunerConstants.h>


class IntakeSubsystem : public frc2::SubsystemBase {
    public:
        IntakeSubsystem();

        frc2::CommandPtr Intake(units::angle::turn_t turns);

        void InitSendable(wpi::SendableBuilder& builder) override;

        void setConfig();

        double getRots(); //gets rotations and sends them

        bool override();

        bool sensorBool1;

    private:
        ctre::phoenix6::CANBus can{"", "./logs/example.hoot"};
        //ctre::phoenix6::hardware::TalonFX T_Motor{11, can};

        controls::PositionVoltage a_request = controls::PositionVoltage{0_tr}.WithSlot(0);
};