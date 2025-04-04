#include "subsystems/DriveSubsystem.h"
#include "generated/TunerConstants.h"
#include "RobotContainer.h"

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
    units::meters_per_second_t xGoTo = units::math::min(x - drivetrain->GetState().Pose.X(), 3.0_m)/1_s;
    units::meters_per_second_t yGoTo = units::math::min(y - drivetrain->GetState().Pose.Y(), 3.0_m)/1_s;
    units::angular_velocity::turns_per_second_t rotGoTo = units::math::min(units::angular_velocity::turns_per_second_t(angle - drivetrain->GetPigeon2().GetYaw().GetValueAsDouble()), 1_tps);

    drivetrain->SetControl(drive.WithRotationalRate(rotGoTo).WithVelocityX(xGoTo).WithVelocityY(yGoTo));

    targetAngle = angle;
    targetX = x;
    targetY = y;
}

void DriveSubsystem::positionDrivebase(subsystems::CommandSwerveDrivetrain* drivetrain, units::length::meter_t x, units::length::meter_t y) {
    units::meters_per_second_t xGoTo = units::math::min(x - drivetrain->GetState().Pose.X(), 3_m)/1_s;
    units::meters_per_second_t yGoTo = units::math::min(y - drivetrain->GetState().Pose.Y(), 3_m)/1_s;
    
    drivetrain->SetControl(drive.WithVelocityX(xGoTo).WithVelocityY(yGoTo));

    targetX = x;
    targetY = y;
}

void DriveSubsystem::rotateDrivebase(subsystems::CommandSwerveDrivetrain* drivetrain, double angle) {
    units::angular_velocity::turns_per_second_t rotGoTo = units::math::min(units::angular_velocity::turns_per_second_t(angle - drivetrain->GetPigeon2().GetYaw().GetValueAsDouble()), 1_tps);

    drivetrain->SetControl(drive.WithRotationalRate(rotGoTo));

    targetAngle = angle;
}

units::meters_per_second_t DriveSubsystem::xPositionMath(subsystems::CommandSwerveDrivetrain* drivetrain, units::length::meter_t x) { //Getter methods, should you want them
    units::meters_per_second_t xGoTo = units::math::min(x - drivetrain->GetState().Pose.X(), 3_m)/1_s;
    return xGoTo;
}

units::meters_per_second_t DriveSubsystem::yPositionMath(subsystems::CommandSwerveDrivetrain* drivetrain, units::length::meter_t y) {
    units::meters_per_second_t yGoTo = units::math::min(y - drivetrain->GetState().Pose.X(), 3_m)/1_s;
    return yGoTo;
}

double DriveSubsystem::rotMath(subsystems::CommandSwerveDrivetrain* drivetrain, double angle) {
    double rotGoTo = std::min(angle - drivetrain->GetPigeon2().GetYaw().GetValueAsDouble(), 1.0);
    return rotGoTo;
}

bool DriveSubsystem::isAtRot(subsystems::CommandSwerveDrivetrain* drivetrain) {
    return (std::abs(targetAngle - drivetrain->GetPigeon2().GetYaw().GetValueAsDouble()) <= AprilTagConstants::DegTolerance);
}

bool DriveSubsystem::isAtPos(subsystems::CommandSwerveDrivetrain* drivetrain) {
    return ((units::math::abs(targetX - drivetrain->GetState().Pose.X()) <= AprilTagConstants::xTolerance)&&(units::math::abs(targetY - drivetrain->GetState().Pose.Y()) <= AprilTagConstants::yTolerance));
}