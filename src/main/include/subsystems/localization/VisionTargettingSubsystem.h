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
        VisSubsystem();

        bool seesColor();
        bool seesAprilTag();

        void alignDrivebase(bool aprilTags, subsystems::CommandSwerveDrivetrain* drivetrain);
        void alignAndDrive(bool aprilTags, subsystems::CommandSwerveDrivetrain* drivetrain);

    private:
        swerve::requests::RobotCentric drive = swerve::requests::RobotCentric{};
        int tagID;
};