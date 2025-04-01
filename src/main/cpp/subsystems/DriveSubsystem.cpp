#include "subsystems/DriveSubsystem.h"
#include "generated/TunerConstants.h"
#include "RobotContainer.h"
#include <ctre/phoenix/motorcontrol/ControlMode.h>

DriveSubsystem::DriveSubsystem() {
    drive
        .WithDeadband(DrivebaseConstants::MaxSpeed * 0.1).WithRotationalDeadband(DrivebaseConstants::MaxAngularRate * 0.1) // Add a 10% deadband (Taken from RobotContainer)
        .WithDriveRequestType(swerve::DriveRequestType::OpenLoopVoltage);
    driveField
        .WithForwardPerspective(swerve::requests::ForwardPerspectiveValue::OperatorPerspective)
        .WithDeadband(DrivebaseConstants::MaxSpeed * 0.1).WithRotationalDeadband(DrivebaseConstants::MaxAngularRate * 0.1)
        .WithDriveRequestType(swerve::DriveRequestType::OpenLoopVoltage);
}

void DriveSubsystem::moveDrivebase(subsystems::CommandSwerveDrivetrain* drivetrain, double angle, units::length::meter_t x, units::length::meter_t y) {
    units::length::meter_t xGoTo = std::min(x - drivetrain->GetState().Pose.X(), 3_m);
    units::length::meter_t yGoTo = std::min(y - drivetrain->GetState().Pose.X(), 3_m);
    units::angular_velocity::turns_per_second_t rotGoTo = std::min(units::angular_velocity::turns_per_second_t(angle - drivetrain->GetPigeon2().GetAngle()), 1_tps);

    drivetrain->SetControl(drive.WithRotationalRate(rotGoTo).WithVelocityX(xGoTo).WithVelocityY(yGoTo));

    targetAngle = angle;
    targetX = x;
    targetY = y;
}

void DriveSubsystem::positionDrivebase(subsystems::CommandSwerveDrivetrain* drivetrain, units::length::meter_t x, units::length::meter_t y) {
    units::length::meter_t xGoTo = std::min(x - drivetrain->GetState().Pose.X(), 3_m);
    units::length::meter_t yGoTo = std::min(y - drivetrain->GetState().Pose.X(), 3_m);
    
    drivetrain->SetControl(drive.WithVelocityX(xGoTo).WithVelocityY(yGoTo));

    targetX = x;
    targetY = y;
}

void DriveSubsystem::rotateDrivebase(subsystems::CommandSwerveDrivetrain* drivetrain, double angle) {
    units::angular_velocity::turns_per_second_t rotGoTo = std::min(units::angular_velocity::turns_per_second_t(angle - drivetrain->GetPigeon2().GetAngle()), 1_tps);

    drivetrain->SetControl(drive.WithRotationalRate(rotGoTo));

    targetAngle = angle;
}

units::length::meter_t DriveSubsystem::xPositionMath(subsystems::CommandSwerveDrivetrain* drivetrain, units::length::meter_t x) { //Getter methods, should you want them
    units::length::meter_t xGoTo = std::min(x - drivetrain->GetState().Pose.X(), 3_m);
    return xGoTo;
}

units::length::meter_t DriveSubsystem::yPositionMath(subsystems::CommandSwerveDrivetrain* drivetrain, units::length::meter_t y) {
    units::length::meter_t yGoTo = std::min(y - drivetrain->GetState().Pose.X(), 3_m);
    return yGoTo;
}

double DriveSubsystem::rotMath(subsystems::CommandSwerveDrivetrain* drivetrain, double angle) {
    double rotGoTo = std::min(angle - drivetrain->GetPigeon2().GetAngle(), 1.0);
    return rotGoTo;
}

bool DriveSubsystem::isAtRot(subsystems::CommandSwerveDrivetrain* drivetrain) {
    return (std::abs(targetAngle - drivetrain->GetPigeon2().GetAngle()) <= LimelightConstants::DegTolerance);
}

bool DriveSubsystem::isAtPos(subsystems::CommandSwerveDrivetrain* drivetrain) {
    return ((std::abs(double(targetX) - double(drivetrain->GetState().Pose.X())) <= LimelightConstants::xTolerance)&&(std::abs(double(targetY) - double(drivetrain->GetState().Pose.Y())) <= LimelightConstants::yTolerance));
}
