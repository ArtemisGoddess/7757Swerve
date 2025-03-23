#include <wpi/sendable/SendableBuilder.h>
#include "subsystems/localization/VisionTargettingSubsystem.h"
#include "generated/TunerConstants.h"
#include "RobotContainer.h"
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/controller/PIDController.h>
#include <iostream>
#include <ctre/phoenix/motorcontrol/ControlMode.h>

VisSubsystem::VisSubsystem(subsystems::CommandSwerveDrivetrain& drivetrain) : drivetrain(drivetrain) {}

frc2::CommandPtr VisSubsystem::ScanForTarget() {
    return this->Run(
        [this] {
            double targetVisible = limelight->GetDoubleTopic("tv").GetEntry(0.0).Get();
            if (targetVisible > 0.0) {
                double tx = limelight->GetDoubleTopic("tx").GetEntry(0.0).Get();

                if (tx > 5.0) {
                    drivetrain.SetControl(drive.WithRotationalRate(-0.01_tps * tx).WithVelocityX(-joystick.GetLeftY() * MaxSpeed).WithVelocityY(-joystick.GetLeftX() * MaxSpeed));
                } else if (tx < -5.0) {
                    drivetrain.SetControl(drive.WithRotationalRate(0.01_tps * -tx).WithVelocityX(-joystick.GetLeftY() * MaxSpeed).WithVelocityY(-joystick.GetLeftX() * MaxSpeed));
                }
            } else {
                drivetrain.SetControl(drive.WithRotationalRate(0_tps).WithVelocityX(joystick.GetLeftY() * MaxSpeed).WithVelocityY(-joystick.GetLeftX() * MaxSpeed));
            }
        }
    );
}



void VisSubsystem::InitSendable(wpi::SendableBuilder& builder) { SubsystemBase::InitSendable(builder); }