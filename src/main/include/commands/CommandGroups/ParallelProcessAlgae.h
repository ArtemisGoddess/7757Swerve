#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/ParallelCommandGroup.h>
#include "subsystems/LiftSubsystem.h"
#include "subsystems/WristSubsystem.h"
#include "commands/LiftProcessAlgae.h"
#include "commands/WristProcessAlgae.h"

class ParallelProcessAlgae : public frc2::CommandHelper<frc2::ParallelCommandGroup, ParallelProcessAlgae> {
public:
    ParallelProcessAlgae(LiftSubsystem* lift, WristSubsystem* wrist);
};