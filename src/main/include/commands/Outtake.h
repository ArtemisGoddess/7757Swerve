#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/Command.h>
#include "subsystems/IntakeSubsystem.h"

class Outtake : public frc2::CommandHelper<frc2::Command, Outtake> {
public:
    Outtake(IntakeSubsystem* intake, double speed);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;

private:
    IntakeSubsystem* m_intake;
    double m_speed;
};