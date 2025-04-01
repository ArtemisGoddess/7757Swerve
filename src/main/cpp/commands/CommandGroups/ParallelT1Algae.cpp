#include "commands/CommandGroups/ParallelT1Algae.h"

ParallelT1Algae::ParallelT1Algae(LiftSubsystem* lift, WristSubsystem* wrist) {
    AddCommands(
        LiftT1Algae(lift),
        WristT1Algae(wrist)
    );
}