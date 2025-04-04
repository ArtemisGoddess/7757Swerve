#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/ParallelCommandGroup.h>
#include "subsystems/LiftSubsystem.h"
#include "subsystems/WristSubsystem.h"
#include "commands/LiftT1Algae.h"
#include "commands/WristT1Algae.h"

class ParallelT1Algae : public frc2::CommandHelper<frc2::ParallelCommandGroup, ParallelT1Algae> {
public:
    ParallelT1Algae(LiftSubsystem* lift, WristSubsystem* wrist);
};