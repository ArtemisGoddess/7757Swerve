// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <ctre/phoenix6/swerve/SwerveRequest.hpp>
#include "subsystems/CommandSwerveDrivetrain.h"
#include "Telemetry.h"
#include "Config.h"

#include "subsystems/IntakeSubsystem.h"
#include "subsystems/ClimberSubsystem.h"
#include "subsystems/WristSubsystem.h"
#include "subsystems/LiftSubsystem.h"
#include "subsystems/localization/VisionTargettingSubsystem.h"
#include "subsystems/DriveSubsystem.h"

//swerve::requests::ForwardPerspectiveValue FieldCentric = swerve::requests::ForwardPerspectiveValue::BlueAlliance;
//swerve::requests::ForwardPerspectiveValue OperaterCentric = swerve::requests::ForwardPerspectiveValue::OperatorPerspective;

class RobotContainer {
private:
    units::meters_per_second_t MaxSpeed = TunerConstants::kSpeedAt12Volts; // kSpeedAt12Volts desired top speed
    units::radians_per_second_t MaxAngularRate = 0.75_tps; // 3/4 of a rotation per second max angular velocity

    /* Setting up bindings for necessary control of the swerve drive platform */
    //swerve::requests::RobotCentric drive = swerve::requests::RobotCentric{}
    swerve::requests::FieldCentric drive = swerve::requests::FieldCentric{}
        .WithForwardPerspective(swerve::requests::ForwardPerspectiveValue::OperatorPerspective)
        .WithDeadband(MaxSpeed * 0.1).WithRotationalDeadband(MaxAngularRate * 0.1) // Add a 10% deadband
        .WithDriveRequestType(swerve::DriveRequestType::OpenLoopVoltage); // Use open-loop control for drive motors 
    swerve::requests::SwerveDriveBrake brake{};
    swerve::requests::PointWheelsAt point{};

    /* Note: This must be constructed before the drivetrain, otherwise we need to
     *       define a destructor to un-register the telemetry from the drivetrain */
    Telemetry logger{MaxSpeed};

public:
    subsystems::CommandSwerveDrivetrain drivetrain{TunerConstants::CreateDrivetrain()};

    RobotContainer();

    frc2::CommandPtr GetAutonomousCommand();
    
private:
    void ConfigureBindings();

    IntakeSubsystem m_intakeSubsystem;
    ClimberSubsystem m_climber;
    WristSubsystem m_wristSubsystem;
    LiftSubsystem m_liftSubsystem;
    VisSubsystem m_visionSubsystem;
    DriveSubsystem m_driveSubsystem;
};
