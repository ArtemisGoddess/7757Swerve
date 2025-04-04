#include "commands/CommandGroups/ParallelRest.h"

ParallelRest::ParallelRest(LiftSubsystem* lift, WristSubsystem* wrist) {
    AddCommands(
        LiftRestPID(lift),
        WristRestPID(wrist)
    );
}