#include "commands/CommandGroups/ParallelProcessAlgae.h"

ParallelProcessAlgae::ParallelProcessAlgae(LiftSubsystem* lift, WristSubsystem* wrist) {
    AddCommands(
        LiftProcessAlgae(lift),
        WristProcessAlgae(wrist)
    );
}