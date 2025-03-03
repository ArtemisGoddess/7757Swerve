#pragma once

#include "Telemetry.h" //You need this for the motors!
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h> //Subsystem things
#include <frc/controller/SimpleMotorFeedforward.h>
#include <ctre/phoenix6/configs/Configs.hpp>

#include <generated/TunerConstants.h>


class MotorTurn : public frc2::SubsystemBase {
    public:
        MotorTurn();

        frc2::CommandPtr SetMotorPosition(units::angle::turn_t turns);

        frc2::CommandPtr testtest(units::angle::turn_t turns);

        frc2::CommandPtr victorOff();

        void InitSendable(wpi::SendableBuilder& builder) override;

        void setConfig();

        void test();

    private:
        //ctre::phoenix6::hardware::TalonFX T_Motor{11, can};
        //frc::SimpleMotorFeedforward<units::radians> m_shooterFeedforward{(units::volt_t)0.1};

        controls::PositionVoltage m_request = controls::PositionVoltage{0_tr}.WithSlot(0);
};