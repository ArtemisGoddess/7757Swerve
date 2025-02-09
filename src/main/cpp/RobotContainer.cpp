// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include "subsystems/MotorTurn.h"
#include "subsystems/IntakeSubsystem.h"

#include <frc2/command/Commands.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/Command.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/smartdashboard/SmartDashboard.h>

//ctre::phoenix6::CANBus can{"", "./logs/example.hoot"};
//ctre::phoenix6::hardware::TalonFX Test{11, can};

RobotContainer::RobotContainer() 
{

    frc::Shuffleboard::GetTab("IntakeSubsystem").Add(m_intake);
    frc::Shuffleboard::GetTab("MotorTurn").Add(m_turn);

    //m_turn.setConfig();
    //m_turn.test();

    ConfigureBindings();
}

void RobotContainer::ConfigureBindings() {
    // Note that X is defined as forward according to WPILib convention,
    // and Y is defined as to the left according to WPILib convention.
    drivetrain.SetDefaultCommand(
        // Drivetrain will execute this command periodically
        drivetrain.ApplyRequest([this]() -> auto&& {
            return drive.WithVelocityX(joystick.GetLeftY() * MaxSpeed) // Drive forward with Y (forward)
                .WithVelocityY(joystick.GetLeftX() * MaxSpeed) // Drive left with X (left)
                .WithRotationalRate(-joystick.GetRightX() * MaxAngularRate); // Drive counterclockwise with negative X (left)
        })
    );

    (frc2::JoystickButton(&joystick.GetHID(), frc::XboxController::Button::kX)) //Structured activator for the command pointers. NOTE YOU MUST SPECIFY WHAT 'm_turn' IS IN THE HEADER FILE
        .WhileTrue(m_intake.Intake(0.1_tr));

    /*frc2::JoystickButton(&joystick.GetHID(), frc::XboxController::Button::kX)
        .OnTrue(m_intake.Intake(1_tr));
    frc2::JoystickButton(&joystick.GetHID(), frc::XboxController::Button::kY)
        .OnTrue(m_intake.override());*/
    
    /*frc2::JoystickButton(&joystick.GetHID(), frc::XboxController::Button::kB)
        .OnTrue(m_turn.testtest(0_tr));
        //.OnFalse(m_turn.StopIt()); //.OnChange(m_turn.TurnRight());
        //.WhileFalse(m_turn.StopIt());

    //frc2::CommandPtr test = frc2::Command::ToPtr(m_turn.setMotorTest(0));

    frc2::JoystickButton(&joystick.GetHID(), frc::XboxController::Button::kRightBumper)
        .WhileTrue(setMotorTest);
        //.WhileFalse(m_turn.StopIt());
    */
    
    drivetrain.RegisterTelemetry([this](auto const &state) { logger.Telemeterize(state); });
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand()
{
    return frc2::cmd::Print("No autonomous command configured");
}
