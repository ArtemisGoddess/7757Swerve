// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include "Telemetry.h"
#include "Config.h"

#include <frc2/command/Commands.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/Command.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <pathplanner/lib/commands/PathPlannerAuto.h>
#include <pathplanner/lib/events/EventTrigger.h>
#include <pathplanner/lib/auto/NamedCommands.h>
#include <iostream>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <ctre/phoenix6/CANBus.hpp>
#include <ctre/phoenix6/TalonFX.hpp>

//ctre::phoenix6::CANBus can{"", "./logs/example.hoot"};
//ctre::phoenix6::hardware::TalonFX Test{11, can};

RobotContainer::RobotContainer() : m_vis(drivetrain) //Passes the drivetrain to the targetting subsystem so it may move
{
    frc::Shuffleboard::GetTab("IntakeSubsystem").Add(m_intake);
    frc::Shuffleboard::GetTab("testSubsystem").Add(m_test);

    pathplanner::NamedCommands::registerCommand("CoralIntake", std::move(m_intake.RunIntake(-0.3)));
    pathplanner::NamedCommands::registerCommand("Wrist-Up", std::move(m_wrist.Wrist(0_tr)));
    pathplanner::NamedCommands::registerCommand("CoralOuttake", std::move(Auto.Outtake()));
    pathplanner::NamedCommands::registerCommand("Wrist-Down", std::move(m_wrist.Wrist(2.76_tr)));
    //pathplanner::NamedCommands::registerCommand("Lift-Up", std::move(m_lift.LiftUp(1_tr))); //This is a run command, might need to be changed for your needs m8
    //pathplanner::NamedCommands::registerCommand("Lift-Down", std::move(m_lift.LiftDown(1_tr))); //Same with this one
    
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

    /*(frc2::JoystickButton(&joystick.GetHID(), frc::XboxController::Button::kX)) //Structured activator for the command pointers. NOTE YOU MUST SPECIFY WHAT 'm_turn' IS IN THE HEADER FILE
        .WhileTrue(m_test.testtest());*/
    
    (frc2::JoystickButton(&joystick.GetHID(), frc::XboxController::Button::kLeftBumper)) //Self explainitory
        .WhileTrue(m_wrist.WristRight());

    joystick.LeftTrigger(0.5) //For Trigger handling
        .WhileTrue(m_wrist.WristLeft());

    (frc2::JoystickButton(&joystick.GetHID(), frc::XboxController::Button::kRightBumper))
        .WhileTrue(m_intake.RunIntake(-0.3));
    
    joystick.RightTrigger(0.5)
        .WhileTrue(m_intake.RunIntake(1.0));
    
    /*(frc2::JoystickButton(&joystick.GetHID(), frc::XboxController::Button::kY)) //Climbing Calls
        .OnTrue(m_climber.ClimbUp());

    (frc2::JoystickButton(&joystick.GetHID(), frc::XboxController::Button::kA))
        .OnTrue(m_climber.ClimbDown());*/
    
    (frc2::JoystickButton(&joystick.GetHID(), frc::XboxController::Button::kB)) //coral alignment (Should work)
        .WhileTrue(m_vis.ScanForTarget());
    
    /*joystick.POVUp()
        .WhileTrue(m_lift.LiftUp(1_tr));
        
    joysti0ck.POVDown()
        .WhileTrue(m_lift.LiftDown(1_tr));*/

    drivetrain.RegisterTelemetry([this](auto const &state) { logger.Telemeterize(state); });
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand()
{
    return pathplanner::PathPlannerAuto("Single-Score-Auto").ToPtr();
}
