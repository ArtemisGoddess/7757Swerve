#include "commands/CommandGroups/ParallelNetAlgae.h"

ParallelNetAlgae::ParallelNetAlgae(LiftSubsystem* lift, WristSubsystem* wrist) {
    AddCommands(
        LiftNetAlgae(lift),
        WristNetAlgae(wrist)
    );
}