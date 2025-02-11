// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SwerveSubsystem.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableValue.h"

#include <pathplanner/lib/auto/AutoBuilder.h>
#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/geometry/Translation2d.h>
#include <frc/kinematics/ChassisSpeeds.h>
#include <pathplanner/lib/controllers/PPHolonomicDriveController.h>

#include <units/velocity.h>
#include <frc/DriverStation.h>

using namespace pathplanner;
SwerveSubsystem::SwerveSubsystem() {
    RobotConfig config = RobotConfig::fromGUISettings();
    
    resetGyro();


    AutoBuilder::configure(
    [this]() -> frc::Pose2d { return getPose(); },              // Lambda for Robot pose supplier
    [this](frc::Pose2d pose) { resetPose(pose); },              // Lambda for resetting odometry
    [this]() -> frc::ChassisSpeeds { return getRobotRelativeSpeeds(); },  // Lambda for ChassisSpeeds supplier (MUST BE ROBOT RELATIVE)
    [this](frc::ChassisSpeeds speeds) { driveRobotRelative(speeds); },   // Lambda for driving the robot given ROBOT RELATIVE ChassisSpeeds
    std::make_shared<PPHolonomicDriveController>(
        PIDConstants(5.0, 0.0, 0.0),
        PIDConstants(5.0, 0.0, 0.0)
    ),
    config,                                         // Default path replanning config
    []() {
            // Boolean supplier that controls when the path will be mirrored for the red alliance
            // This will flip the path being followed to the red side of the field.
            // THE ORIGIN WILL REMAIN ON THE BLUE SIDE

            auto alliance = frc::DriverStation::GetAlliance();
            if (alliance) {
                return alliance.value() == frc::DriverStation::Alliance::kRed;
            }
            return false;
        },
        this                                                       // Reference to this subsystem to set requirements
    );  
}

frc::Rotation2d SwerveSubsystem::getHeading() {
    units::degree_t deg{-gyro.GetYaw().GetValue()};
    return frc::Rotation2d(deg);
}

double SwerveSubsystem::getHeadingAsAngle() {
    return getHeading().Degrees().value();
}

frc::Rotation2d SwerveSubsystem::getPitch() {
    units::degree_t deg{gyro.GetPitch().GetValue()};
    return frc::Rotation2d(deg);
}

frc::Pose2d SwerveSubsystem::getPose(){
    units::meter_t posX{slam.get()->GetNumber("PositionX", 0.0)};
    units::meter_t posY{slam.get()->GetNumber("PositionY", 0.0)};
    units::degree_t deg{gyro.GetPitch().GetValue()};
    return frc::Pose2d(posX, posY, deg);
}


frc::Pose2d SwerveSubsystem::resetPose(frc::Pose2d pose){
    return frc::Pose2d();
}

frc::ChassisSpeeds SwerveSubsystem::getRobotRelativeSpeeds(){

    units::meters_per_second_t speedX{slam.get()->GetNumber("VelocityX", 0.0)};
    units::meters_per_second_t speedY{slam.get()->GetNumber("VelocityY", 0.0)};

    frc::ChassisSpeeds speeds{speedX, -speedY,
    units::radians_per_second_t(std::numbers::pi)};
    return frc::ChassisSpeeds(speeds);
}

frc::DifferentialDriveWheelSpeeds SwerveSubsystem::driveRobotRelative(frc::ChassisSpeeds speeds){
    // Creating my kinematics object: track width of 23 inches (Calculated from Robot CAD)
    frc::DifferentialDriveKinematics kinematics{23_in};

// Convert to wheel speeds. Here, we can use C++17's structured bindings
// feature to automatically split the DifferentialDriveWheelSpeeds
// struct into left and right velocities.
    auto [left,right] = kinematics.ToWheelSpeeds(speeds);
    return frc::DifferentialDriveWheelSpeeds(left, right);

}

double SwerveSubsystem::getPitchAsAngle() {
    return getPitch().Degrees().value();
}

void SwerveSubsystem::resetGyro() {
    gyro.Reset();
}

void SwerveSubsystem::Periodic() { 
    
}