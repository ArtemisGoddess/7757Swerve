#pragma once

#include "Telemetry.h" //You need this for the motors!
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h> //Subsystem things
#include <frc/controller/SimpleMotorFeedforward.h>
#include <ctre/phoenix6/configs/Configs.hpp>
#include "subsystems/CommandSwerveDrivetrain.h"
#include "Config.h"

#include <generated/TunerConstants.h>

class VisSubsystem : public frc2::SubsystemBase {
    public:
        VisSubsystem();

        bool seesColor();

        void alignDrivebase(subsystems::CommandSwerveDrivetrain* drivetrain);
        void alignAndDrive(subsystems::CommandSwerveDrivetrain* drivetrain);

        bool seesAprilTag();
        double getTagID();
        double distanceToTag();

        double tagHandle();

    private:
        swerve::requests::RobotCentric drive = swerve::requests::RobotCentric{};
        
        int tagID;
};