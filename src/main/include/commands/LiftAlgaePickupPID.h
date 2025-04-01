#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/Command.h>
#include "subsystems/LiftSubsystem.h"

class LiftAlgaePickupPID : public frc2::CommandHelper<frc2::Command, LiftAlgaePickupPID> {
public:
    LiftAlgaePickupPID(LiftSubsystem* lift);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;

private:
    LiftSubsystem* m_lift;
};