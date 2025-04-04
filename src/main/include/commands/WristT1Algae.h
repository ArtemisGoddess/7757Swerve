#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/Command.h>
#include "subsystems/WristSubsystem.h"

class WristT1Algae : public frc2::CommandHelper<frc2::Command, WristT1Algae> {
public:
    WristT1Algae(WristSubsystem* wrist);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;

private:
    WristSubsystem* m_wrist;
};