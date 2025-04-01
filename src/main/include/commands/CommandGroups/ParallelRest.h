#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/ParallelCommandGroup.h>
#include "subsystems/LiftSubsystem.h"
#include "subsystems/WristSubsystem.h"
#include "commands/LiftRestPID.h"
#include "commands/WristRestPID.h"

class ParallelRest : public frc2::CommandHelper<frc2::ParallelCommandGroup, ParallelRest> {
public:
    ParallelRest(LiftSubsystem* lift, WristSubsystem* wrist);
};