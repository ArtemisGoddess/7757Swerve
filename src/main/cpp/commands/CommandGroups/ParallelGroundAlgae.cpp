#include "commands/CommandGroups/ParallelGroundAlgae.h"

ParallelGroundAlgae::ParallelGroundAlgae(LiftSubsystem* lift, WristSubsystem* wrist) {
    AddCommands(
        LiftAlgaePickupPID(lift),
        WristAlgaePickupPID(wrist)
    );
}