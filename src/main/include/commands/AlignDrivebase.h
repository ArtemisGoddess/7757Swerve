#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/Command.h>
#include "subsystems/localization/VisionTargettingSubsystem.h"

class AlignDrivebase : public frc2::CommandHelper<frc2::Command, AlignDrivebase> {
public:
    AlignDrivebase(VisSubsystem* vis, subsystems::CommandSwerveDrivetrain* drivetrain);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;

private:
    VisSubsystem* m_vis;
    subsystems::CommandSwerveDrivetrain* m_drivetrain;
};