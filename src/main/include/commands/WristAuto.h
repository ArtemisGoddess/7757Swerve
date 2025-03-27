#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/Command.h>
#include "subsystems/WristSubsystem.h"

class WristAuto : public frc2::CommandHelper<frc2::Command, WristAuto> {
public:
    WristAuto(WristSubsystem* wrist);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;

private:
    WristSubsystem* m_wrist;
};