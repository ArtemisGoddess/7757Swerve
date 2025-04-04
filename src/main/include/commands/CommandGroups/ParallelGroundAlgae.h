#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/ParallelCommandGroup.h>
#include "subsystems/LiftSubsystem.h"
#include "subsystems/WristSubsystem.h"
#include "commands/LiftAlgaePickupPID.h"
#include "commands/WristAlgaePickupPID.h"

class ParallelGroundAlgae : public frc2::CommandHelper<frc2::ParallelCommandGroup, ParallelGroundAlgae> {
public:
    ParallelGroundAlgae(LiftSubsystem* lift, WristSubsystem* wrist);
};