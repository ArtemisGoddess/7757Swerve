// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc2/command/button/JoystickButton.h>
#include <pathplanner/lib/commands/PathPlannerAuto.h>
#include <pathplanner/lib/events/EventTrigger.h>
#include <pathplanner/lib/auto/NamedCommands.h>

#include "RobotContainer.h"

#include "commands/TeleopWrist.h"
#include "commands/Intake.h"
#include "commands/Outtake.h"
#include "commands/AlignDrivebase.h"
#include "commands/WristAuto.h"
#include "commands/LiftRestPID.h"
#include "commands/LiftMaxPID.h"

#include "commands/CommandGroups/ParallelGroundAlgae.h"
#include "commands/CommandGroups/ParallelT1Algae.h"
#include "commands/CommandGroups/ParallelT2Algae.h"
#include "commands/CommandGroups/ParallelNetAlgae.h"
#include "commands/CommandGroups/ParallelProcessAlgae.h"
#include "commands/CommandGroups/ParallelRest.h"

RobotContainer::RobotContainer()//Passes the drivetrain to the targetting subsystem so it may move
{
    pathplanner::NamedCommands::registerCommand("CoralOuttake", std::make_shared<Intake>(&m_intakeSubsystem, 0.4)); //This is technically the outtake for the coral
    pathplanner::NamedCommands::registerCommand("AlgaeOuttake", std::make_shared<Outtake>(&m_intakeSubsystem, 0.8)); //This is technically the outtake for the coral
    pathplanner::NamedCommands::registerCommand("AlgaeIntake", std::make_shared<Intake>(&m_intakeSubsystem, 0.8));
    pathplanner::NamedCommands::registerCommand("CoralScorePos", std::make_shared<WristT1Algae>(&m_wristSubsystem));
    pathplanner::NamedCommands::registerCommand("ParallelT1Algae", std::make_shared<ParallelT1Algae>(&m_liftSubsystem, &m_wristSubsystem));
    pathplanner::NamedCommands::registerCommand("ParallelT2Algae", std::make_shared<ParallelT2Algae>(&m_liftSubsystem, &m_wristSubsystem));
    pathplanner::NamedCommands::registerCommand("ParallelRest", std::make_shared<ParallelRest>(&m_liftSubsystem, &m_wristSubsystem));

    ConfigureBindings();
}

void RobotContainer::ConfigureBindings() {
    // Note that X is defined as forward according to WPILib convention,
    // and Y is defined as to the left according to WPILib convention.
    drivetrain.SetDefaultCommand(
        // Drivetrain will execute this command periodically
        drivetrain.ApplyRequest([this]() -> auto&& {
            return drive.WithVelocityX(-joystick.GetLeftY() * MaxSpeed) // Drive forward with Y (forward)
                .WithVelocityY(-joystick.GetLeftX() * MaxSpeed) // Drive left with X (left)
                .WithRotationalRate(-joystick.GetRightX() * MaxAngularRate); // Drive counterclockwise with negative X (left)
        })
    );

    // 
    // Operator controls below
    // 

    operatorJoystick.LeftTrigger(0.5) //Wrist Up
        .WhileTrue(new TeleopWrist(&m_wristSubsystem, -0.5_tr));

    (frc2::JoystickButton(&operatorJoystick.GetHID(), frc::XboxController::Button::kLeftBumper)) //Wrist Down
        .WhileTrue(new TeleopWrist(&m_wristSubsystem, 0.5_tr));

    operatorJoystick.RightTrigger(0.5) //Lift Up
        .WhileTrue(new LiftMaxPID(&m_liftSubsystem));

    (frc2::JoystickButton(&operatorJoystick.GetHID(), frc::XboxController::Button::kRightBumper)) //Lift Down
        .WhileTrue(new LiftRestPID(&m_liftSubsystem));

    operatorJoystick.POVUp()
        .OnTrue(new ParallelT2Algae(&m_liftSubsystem, &m_wristSubsystem)); //Parallel t2 algae pickup test

    operatorJoystick.POVRight()
        .OnTrue(new ParallelT1Algae(&m_liftSubsystem, &m_wristSubsystem)); //Paralell t1 algae pickup test

    operatorJoystick.POVDown()
        .OnTrue(new ParallelGroundAlgae(&m_liftSubsystem, &m_wristSubsystem)); //Paralell ground algae pickup test

    (frc2::JoystickButton(&operatorJoystick.GetHID(), frc::XboxController::Button::kY)) //Parallel net score test
        .OnTrue(new ParallelNetAlgae(&m_liftSubsystem, &m_wristSubsystem));

    (frc2::JoystickButton(&operatorJoystick.GetHID(), frc::XboxController::Button::kB)) //Parallel Rest test
        .OnTrue(new ParallelProcessAlgae(&m_liftSubsystem, &m_wristSubsystem));   

    (frc2::JoystickButton(&operatorJoystick.GetHID(), frc::XboxController::Button::kX)) //Parallel Rest test
        .OnTrue(new ParallelRest(&m_liftSubsystem, &m_wristSubsystem));  

    //
    // Driver controls below
    //

    joystick.LeftTrigger(0.1)
        .WhileTrue(new Intake(&m_intakeSubsystem, 0.8));
    
    joystick.RightTrigger(0.1)
        .WhileTrue(new Outtake(&m_intakeSubsystem, 0.8));
    
    (frc2::JoystickButton(&joystick.GetHID(), frc::XboxController::Button::kB)) //Algae alignment (Should work)
        .WhileTrue(new AlignDrivebase(&m_visionSubsystem, &drivetrain));

    drivetrain.RegisterTelemetry([this](auto const &state) { logger.Telemeterize(state); });
}
    
frc2::CommandPtr RobotContainer::GetAutonomousCommand()
{
    return pathplanner::PathPlannerAuto("Drive-Forward").ToPtr();
}
