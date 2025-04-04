// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc2/command/CommandScheduler.h>

Robot::Robot() { 
  m_autonomousCommand = m_container.GetAutonomousCommand();
  ctre::phoenix6::SignalLogger::Stop();

  auto const alliance = frc::DriverStation::GetAlliance().value_or(frc::DriverStation::Alliance::kBlue);
  slam->PutNumber("TeamColorRed", alliance == frc::DriverStation::Alliance::kRed);
  slam->PutNumber("ColorPosition", frc::DriverStation::GetLocation().value());
}

void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
  //m_inst.GetTable("Debuging")->PutNumber("test", (double)WristMotor.GetPosition().GetValue());
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::DisabledExit() {}

void Robot::AutonomousInit() {
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
  ctre::phoenix6::SignalLogger::Stop();
}

void Robot::TeleopPeriodic() {
  slam->PutNumber("VelocityX", m_container.drivetrain.GetState().Speeds.vx());
  slam->PutNumber("VelocityY", m_container.drivetrain.GetState().Speeds.vy());
  slam->PutNumber("PositionX", (double)m_container.drivetrain.GetState().Pose.X());
  slam->PutNumber("PositionY", (double)m_container.drivetrain.GetState().Pose.Y());
  slam->PutNumber("PoseRot", Pigey.GetYaw().GetValueAsDouble());
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
/* Get snailed
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⣦⠀⢀⠀⠀
⠀⠀⠀⠀⠀⠀⢀⣤⣶⣶⣿⣿⣷⣶⣦⣄⠀⠀⠀⠀⠀⠀⢰⡟⠈⠁⣰⣿⡗⠀
⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀⠀⠀⠀⢸⡇⠀⢠⡟⠀⠀⠀
⠀⠀⠀⣰⣿⣿⣿⣿⠟⠋⣉⣉⣉⠙⠻⣿⣿⣿⣷⡀⠀⠀⢸⡇⠀⢸⠃⠀⠀⠀
⠀⠀⢀⣿⣿⣿⣿⡇⢠⣿⣿⣿⢿⣿⣆⠘⣿⣿⣿⣷⡀⠀⢸⣧⠀⢸⡇⠀⠀⠀
⠀⠀⢸⣿⣿⣿⣿⡇⠸⣿⣿⣿⠆⣿⣿⡄⢸⣿⣿⣿⣧⠀⣼⣿⣿⣿⣇⠀⠀⠀
⠀⠀⠀⣿⣿⣿⣿⣿⣦⣈⣉⣁⣴⣿⣿⠁⣼⣿⣿⣿⣿⠀⣿⣿⣿⣿⣿⠀⠀⠀
⠀⠀⠀⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⣰⣿⣿⣿⣿⡿⠀⣿⣿⣿⣿⡿⠀⠀⠀
⠀⠀⠀⠀⠈⠻⠿⣿⣿⣿⠿⠟⠋⠀⠾⢿⣿⣿⠿⠟⢁⣼⣿⣿⣿⣿⡇⠀⠀⠀
⠀⠀⠀⠀⣀⣤⣤⣤⣤⣤⣤⣶⣿⣷⣦⣤⣤⣤⣴⣾⣿⣿⣿⣿⣿⡿⠀⠀⠀⠀
⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠋⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*/ //  :) - Celeste and Aiden