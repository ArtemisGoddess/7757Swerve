// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include "subsystems/MotorTurn.h"

#include <frc2/command/Commands.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/Command.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/trajectory/TrapezoidProfile.h>

//ctre::phoenix6::CANBus can{"", "./logs/example.hoot"};
//ctre::phoenix6::hardware::TalonFX Test{11, can};

RobotContainer::RobotContainer() 
{

    frc::Shuffleboard::GetTab("MotorTurn").Add(m_turn);

    m_turn.setConfig();

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

    joystick.A().WhileTrue(drivetrain.ApplyRequest([this]() -> auto&& { return brake; }));
    joystick.B().WhileTrue(drivetrain.ApplyRequest([this]() -> auto&& {
        return point.WithModuleDirection(frc::Rotation2d{joystick.GetLeftY(), joystick.GetLeftX()});
    }));

    // Run SysId routines when holding back/start and X/Y.
    // Note that each routine should be run exactly once in a single log.
    (joystick.Back() && joystick.Y()).WhileTrue(drivetrain.SysIdDynamic(frc2::sysid::Direction::kForward));
    (joystick.Back() && joystick.X()).WhileTrue(drivetrain.SysIdDynamic(frc2::sysid::Direction::kReverse));
    (joystick.Start() && joystick.Y()).WhileTrue(drivetrain.SysIdQuasistatic(frc2::sysid::Direction::kForward));
    (joystick.Start() && joystick.X()).WhileTrue(drivetrain.SysIdQuasistatic(frc2::sysid::Direction::kReverse));

    frc2::JoystickButton(&joystick.GetHID(), frc::XboxController::Button::kY) //Structured activator for the command pointers. NOTE YOU MUST SPECIFY WHAT 'm_turn' IS IN THE HEADER FILE
        .OnTrue(m_turn.SetMotorPosition(10_tr));
    
    frc2::JoystickButton(&joystick.GetHID(), frc::XboxController::Button::kB)
        .OnTrue(m_turn.testtest(0_tr));
        //.OnFalse(m_turn.StopIt()); //.OnChange(m_turn.TurnRight());
        //.WhileFalse(m_turn.StopIt());

    //frc2::CommandPtr test = frc2::Command::ToPtr(m_turn.setMotorTest(0));

    /*frc2::JoystickButton(&joystick.GetHID(), frc::XboxController::Button::kRightBumper)
        .WhileTrue(setMotorTest);
        //.WhileFalse(m_turn.StopIt());
    */
    
    drivetrain.RegisterTelemetry([this](auto const &state) { logger.Telemeterize(state); });
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand()
{
    return frc2::cmd::Print("No autonomous command configured");
}
