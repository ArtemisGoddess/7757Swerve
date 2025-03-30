#pragma once

#include "Telemetry.h" //You need this for the motors!
#include <frc2/command/SubsystemBase.h> //Subsystem things
#include <ctre/phoenix6/configs/Configs.hpp>
#include "subsystems/CommandSwerveDrivetrain.h"
#include "Config.h"

#include <generated/TunerConstants.h>

class DriveSubsystem : public frc2::SubsystemBase {
    public:
        DriveSubsystem();

        void moveDrivebase(subsystems::CommandSwerveDrivetrain* drivetrain, double angle, units::length::meter_t x, units::length::meter_t y);

        void rotateDrivebase(subsystems::CommandSwerveDrivetrain* drivetrain, double angle);

        //X is forward, Y is Right
        void positionDrivebase(subsystems::CommandSwerveDrivetrain* drivetrain, units::length::meter_t x, units::length::meter_t y);

        units::length::meter_t xPositionMath(subsystems::CommandSwerveDrivetrain* drivetrain, units::length::meter_t x);
        units::length::meter_t yPositionMath(subsystems::CommandSwerveDrivetrain* drivetrain, units::length::meter_t y);

        double rotMath(subsystems::CommandSwerveDrivetrain* drivetrain, double angle);

        bool isAtRot(subsystems::CommandSwerveDrivetrain* drivetrain);

        bool isAtPos(subsystems::CommandSwerveDrivetrain* drivetrain);

    private:
        swerve::requests::RobotCentric drive = swerve::requests::RobotCentric{};
        swerve::requests::FieldCentric driveField = swerve::requests::FieldCentric{};

        int tagID;
        double targetAngle;
        units::length::meter_t targetX;
        units::length::meter_t targetY;
};