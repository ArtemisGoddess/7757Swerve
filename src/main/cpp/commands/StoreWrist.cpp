#include "commands/StoreWrist.h"

StoreWrist::StoreWrist(WristSubsystem* wrist)
    : m_wrist(wrist) {
    AddRequirements({wrist});
}

void StoreWrist::Initialize() { }

void StoreWrist::Execute() {
    m_wrist->storePID();
}

void StoreWrist::End(bool interrupted) {
    if (interrupted) {
        m_wrist->stop();
    }
}

bool StoreWrist::IsFinished() {
    return m_wrist->isPutAway(); //Could also return false. Needs testing.
}
