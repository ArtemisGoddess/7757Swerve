#pragma once

#include "Telemetry.h" //You need this for the motors!
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h> //Subsystem things
#include <frc/controller/SimpleMotorFeedforward.h>
#include <ctre/phoenix6/configs/Configs.hpp>
#include "subsystems/CommandSwerveDrivetrain.h"
#include "Config.h"
#include "generated/TunerConstants.h"

#include <generated/TunerConstants.h>

class VisSubsystem : public frc2::SubsystemBase {
    public:
        VisSubsystem(subsystems::CommandSwerveDrivetrain& drivetrain);

        frc2::CommandPtr ScanForTarget();

        void InitSendable(wpi::SendableBuilder& builder) override;

    private:
        subsystems::CommandSwerveDrivetrain& drivetrain;
        units::radians_per_second_t MaxAngularRate = 0.75_tps;
        units::meters_per_second_t MaxSpeed = 4.73_mps;
        swerve::requests::RobotCentric drive = swerve::requests::RobotCentric{};
};