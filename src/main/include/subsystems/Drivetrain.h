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
#include "RobotContainer.h"

using namespace pathplanner;

class Drivetrain : public frc2::SubsystemBase {
  
  
 public:
  Drivetrain();

  void setDriveMotors(double, double);

  void arcadeDrive(double, double);

  void stop();
  
  void flipDT();

  frc::Rotation2d getHeading();

  double getHeadingAsAngle();

  void resetEncoders();

  frc::Rotation2d getPitch();

  double getPitchAsAngle();

  double getLeftEncoderDistance();

  double getRightEncoderDistance();

  double neoTicksToInches(double);

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
 RobotContainer container;

  //ctre::phoenix::motorcontrol::can::WPI_VictorSPX leftSpark1{drivetrain::kLeftDriveSparkPort1};
  //frc::CANVenom leftSpark2{drivetrain::kLeftDriveSparkPort2};

  

  //frc::DifferentialDrive drive{leftMotors, rightMotors};

  bool flipped = false;

  

  frc::ShuffleboardTab& tab = frc::Shuffleboard::GetTab("Test");

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  
    ctre::phoenix6::hardware::Pigeon2 gyro{1, "rio"}; 
  
};