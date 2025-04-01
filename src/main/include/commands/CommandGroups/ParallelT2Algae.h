#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/ParallelCommandGroup.h>
#include "subsystems/LiftSubsystem.h"
#include "subsystems/WristSubsystem.h"
#include "commands/LiftT2Algae.h"
#include "commands/WristT2Algae.h"

class ParallelT2Algae : public frc2::CommandHelper<frc2::ParallelCommandGroup, ParallelT2Algae> {
public:
    ParallelT2Algae(LiftSubsystem* lift, WristSubsystem* wrist);
};