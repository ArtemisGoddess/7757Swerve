#pragma once

#include "Telemetry.h" //You need this for the motors!
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h> //Subsystem things

class MotorTurn : public frc2::SubsystemBase {
    public:
        MotorTurn();

        frc2::CommandPtr TurnLeft();

        frc2::CommandPtr TurnRight();

        frc2::CommandPtr StopIt();

        frc2::CommandPtr SetMotorPosition(units::angle::turn_t turns);

        void InitSendable(wpi::SendableBuilder& builder) override;

    private:
        ctre::phoenix6::hardware::TalonFX T_Motor;
        controls::PositionVoltage m_request = controls::PositionVoltage{0_tr}.WithSlot(0);
};