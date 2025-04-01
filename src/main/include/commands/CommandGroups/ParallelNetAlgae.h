#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/ParallelCommandGroup.h>
#include "subsystems/LiftSubsystem.h"
#include "subsystems/WristSubsystem.h"
#include "commands/LiftNetAlgae.h"
#include "commands/WristNetAlgae.h"

class ParallelNetAlgae : public frc2::CommandHelper<frc2::ParallelCommandGroup, ParallelNetAlgae> {
public:
    ParallelNetAlgae(LiftSubsystem* lift, WristSubsystem* wrist);
};