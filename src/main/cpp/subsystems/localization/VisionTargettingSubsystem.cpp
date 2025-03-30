#include "subsystems/localization/VisionTargettingSubsystem.h"
#include "generated/TunerConstants.h"
#include "RobotContainer.h"
#include <ctre/phoenix/motorcontrol/ControlMode.h>

VisSubsystem::VisSubsystem() {
    drive
        .WithDeadband(DrivebaseConstants::MaxSpeed * 0.1).WithRotationalDeadband(DrivebaseConstants::MaxAngularRate * 0.1) // Add a 10% deadband (Taken from RobotContainer)
        .WithDriveRequestType(swerve::DriveRequestType::OpenLoopVoltage);
}

//pulls from the limelight if it sees color or not
bool VisSubsystem::seesColor() {
    limelight->PutNumber("getpipe", 0.0);
    return bool(limelight->GetDoubleTopic("tv").GetEntry(0.0).Get());
}


void VisSubsystem::alignDrivebase(subsystems::CommandSwerveDrivetrain* drivetrain) {
    limelight->PutNumber("getpipe", 0.0);
    double tx = limelight->GetDoubleTopic("tx").GetEntry(0.0).Get(); //The offset from the camera on the x axis

    if (bool(limelight->GetDoubleTopic("tv").GetEntry(0.0).Get())) {
        if (tx > 5.0) {
            drivetrain->SetControl(drive.WithRotationalRate(-0.01_tps * tx).WithVelocityX(-joystick.GetLeftY() * DrivebaseConstants::MaxSpeed).WithVelocityY(-joystick.GetLeftX() * DrivebaseConstants::MaxSpeed));
        } else if (tx < -5.0) {
            drivetrain->SetControl(drive.WithRotationalRate(0.01_tps * -tx).WithVelocityX(-joystick.GetLeftY() * DrivebaseConstants::MaxSpeed).WithVelocityY(-joystick.GetLeftX() * DrivebaseConstants::MaxSpeed));
        }
    }
}

/*Should, in theory, drive forward towards to a positon while within acceptable distance
* - When aprilTags is true, drives towards the closest reef april tag it sees.
* - When aprilTags is false, drives towards pipeline zero's color calibration
*/
void VisSubsystem::alignAndDrive(subsystems::CommandSwerveDrivetrain* drivetrain) {
    limelight->PutNumber("getpipe", 0.0);
    double tx = limelight->GetDoubleTopic("tx").GetEntry(0.0).Get(); //The offset from the camera on the x axis

    if (bool(limelight->GetDoubleTopic("tv").GetEntry(0.0).Get())) {
        if (tx > 2.0) {
            drivetrain->SetControl(drive.WithRotationalRate(-0.01_tps * tx).WithVelocityX(-0.25 * DrivebaseConstants::MaxSpeed).WithVelocityY(-joystick.GetLeftX() * DrivebaseConstants::MaxSpeed));
        } else if (tx < -2.0) {
            drivetrain->SetControl(drive.WithRotationalRate(0.01_tps * -tx).WithVelocityX(-0.25 * DrivebaseConstants::MaxSpeed).WithVelocityY(-joystick.GetLeftX() * DrivebaseConstants::MaxSpeed));
        }
    }
}

bool VisSubsystem::seesAprilTag() {
    limelight->PutNumber("getpipe", 1.0);
    return bool(limelight->GetDoubleTopic("tv").GetEntry(0.0).Get());
}

double VisSubsystem::getTagID() {
    limelight->PutNumber("getpipe", 1.0);
    return limelight->GetDoubleTopic("distToRobot").GetEntry(0.0).Get(); //Replace with ntable for ID
}

double VisSubsystem::distanceToTag() {
    limelight->PutNumber("getpipe", 1.0);
    return limelight->GetDoubleTopic("distToRobot").GetEntry(0.0).Get();
}

