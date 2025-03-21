// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/CommandXboxController.h>
#include "subsystems/CommandSwerveDrivetrain.h"
#include "Telemetry.h"
#include <ctre/phoenix6/swerve/SwerveRequest.hpp>


#include "subsystems/TestSubsystem.h" 
#include "subsystems/IntakeSubsystem.h"
#include "subsystems/ClimberSubsystem.h"
#include "subsystems/WristSubsystem.h"
#include "subsystems/LiftSubsystem.h"
#include "subsystems/localization/VisionTargettingSubsystem.h"

//swerve::requests::ForwardPerspectiveValue FieldCentric = swerve::requests::ForwardPerspectiveValue::BlueAlliance;
//swerve::requests::ForwardPerspectiveValue OperaterCentric = swerve::requests::ForwardPerspectiveValue::OperatorPerspective;

class RobotContainer {
private:
    units::meters_per_second_t MaxSpeed = TunerConstants::kSpeedAt12Volts; // kSpeedAt12Volts desired top speed
    units::radians_per_second_t MaxAngularRate = 0.75_tps; // 3/4 of a rotation per second max angular velocity

    /* Setting up bindings for necessary control of the swerve drive platform */
    swerve::requests::RobotCentric drive = swerve::requests::RobotCentric{}
        //.WithForwardPerspective(swerve::requests::ForwardPerspectiveValue::OperatorPerspective)
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

    TestSubsystem m_test; //This registers and allows the use of the subsystems
    IntakeSubsystem m_intake;
    ClimberSubsystem m_climber;
    WristSubsystem m_wrist;
    LiftSubsystem m_lift;
    VisSubsystem m_vis{drivetrain};
};
