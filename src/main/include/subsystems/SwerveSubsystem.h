// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <cmath>

#include <frc2/command/SubsystemBase.h>

#include <ctre/phoenix6/TalonFX.hpp>
#include <frc/motorcontrol/MotorControllerGroup.h>

#include <frc/SPI.h>

#include <frc/geometry/Rotation2d.h>

#include <frc/drive/DifferentialDrive.h>

#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>

#include <pathplanner/lib/auto/AutoBuilder.h>
#include <frc/geometry/Pose2d.h>
#include <frc/kinematics/ChassisSpeeds.h>
#include <frc/kinematics/DifferentialDriveWheelSpeeds.h>

#include "generated/TunerConstants.h"

class SwerveSubsystem : public frc2::SubsystemBase {
  
  
 public:
  SwerveSubsystem();

  frc::Rotation2d getHeading();

  double getHeadingAsAngle();

  frc::Rotation2d getPitch();

  double getPitchAsAngle();

  void resetGyro();
  
  frc::Pose2d getPose();

  frc::Pose2d resetPose(frc::Pose2d);

  frc::ChassisSpeeds getRobotRelativeSpeeds();

  frc::DifferentialDriveWheelSpeeds driveRobotRelative(frc::ChassisSpeeds);



  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  private:

    // Components (e.g. motor controllers and sensors) should generally be
    // declared private and exposed only through public methods.
    nt::NetworkTableInstance m_inst = nt::NetworkTableInstance::GetDefault();
    std::shared_ptr<nt::NetworkTable> slam = m_inst.GetTable("slam");


    ctre::phoenix6::hardware::Pigeon2 gyro{1, "rio"}; 
};