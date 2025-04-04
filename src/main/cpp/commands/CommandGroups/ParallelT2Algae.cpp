#include "commands/CommandGroups/ParallelT2Algae.h"

ParallelT2Algae::ParallelT2Algae(LiftSubsystem* lift, WristSubsystem* wrist) {
    AddCommands(
        LiftT2Algae(lift),
        WristT2Algae(wrist)
    );
}