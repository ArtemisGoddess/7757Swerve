// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc2/command/CommandScheduler.h>


Robot::Robot() { 
  m_intake.setConfig();
// port 0 digital imput
// Y high
// A low
}

void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
  slam->PutNumber("VelocityX", m_container.drivetrain.GetState().Speeds.vx());
  slam->PutNumber("VelocityY", m_container.drivetrain.GetState().Speeds.vy());
  slam->PutNumber("PositionX", (double)m_container.drivetrain.GetState().Pose.X());
  slam->PutNumber("PositionY", (double)m_container.drivetrain.GetState().Pose.Y());
  slam->PutNumber("PoseRot", (double)m_pigey.GetYaw().GetValue());

  //frc::SmartDashboard::PutNumber("Test Motor Value", m_intake.getRots());
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::DisabledExit() {}

void Robot::AutonomousInit() {
  m_autonomousCommand = m_container.GetAutonomousCommand();

  if (m_autonomousCommand) {
    m_autonomousCommand->Schedule();
  }
}

void Robot::AutonomousPeriodic() {}

void Robot::AutonomousExit() {}

void Robot::TeleopInit() {
  if (m_autonomousCommand) {
    m_autonomousCommand->Cancel();
  }

  //m_turn.test();
}

void Robot::TeleopPeriodic() {
  
}

void Robot::TeleopExit() {
  
}

void Robot::TestInit() {
  frc2::CommandScheduler::GetInstance().CancelAll();
}

void Robot::TestPeriodic() {}

void Robot::TestExit() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
