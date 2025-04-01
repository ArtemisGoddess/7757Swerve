#include "commands/WristRestPID.h"

WristRestPID::WristRestPID(WristSubsystem* wrist)
    : m_wrist(wrist) {
    AddRequirements({wrist});
}

void WristRestPID::Initialize() { }

void WristRestPID::Execute() {
    m_wrist->restPID();
}

void WristRestPID::End(bool interrupted) {
    if (interrupted) {
        m_wrist->stop();
    }
}

bool WristRestPID::IsFinished() {
    return m_wrist->isAtRest();
}
