#pragma once

#include "Telemetry.h" //You need this for the motors!
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h> //Subsystem things
#include <frc/controller/SimpleMotorFeedforward.h>
#include <ctre/phoenix6/configs/Configs.hpp>
#include "Config.h"
#include "generated/TunerConstants.h"
#include "RobotContainer.h"

#include <generated/TunerConstants.h>


class TestSubsystem : public frc2::SubsystemBase {
    public:
        TestSubsystem();

        frc2::CommandPtr SetMotorPosition(units::angle::turn_t turns);

        frc2::CommandPtr testtest(units::angle::turn_t turns);

        frc2::CommandPtr victorOff();

        void InitSendable(wpi::SendableBuilder& builder) override;

    private:
        //ctre::phoenix6::hardware::TalonFX T_Motor{11, can};
        //frc::SimpleMotorFeedforward<units::radians> m_shooterFeedforward{(units::volt_t)0.1};

        controls::PositionVoltage m_request = controls::PositionVoltage{0_tr}.WithSlot(0);
};