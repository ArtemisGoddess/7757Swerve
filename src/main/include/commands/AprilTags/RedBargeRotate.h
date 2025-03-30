#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/Command.h>
#include "subsystems/localization/VisionTargettingSubsystem.h"
#include "subsystems/DriveSubsystem.h"

class RedBargeRotate : public frc2::CommandHelper<frc2::Command, RedBargeRotate> {
public:
    RedBargeRotate(VisSubsystem* vis, DriveSubsystem* m_drive, subsystems::CommandSwerveDrivetrain* drivetrain, int tagID);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;

private:
    VisSubsystem* m_vis;
    DriveSubsystem* m_drive;
    subsystems::CommandSwerveDrivetrain* m_drivetrain;
    int m_tagID;
};