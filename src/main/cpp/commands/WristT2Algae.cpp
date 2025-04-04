#include "commands/WristT2Algae.h"

WristT2Algae::WristT2Algae(WristSubsystem* wrist)
    : m_wrist(wrist) {
    AddRequirements({wrist});
}

void WristT2Algae::Initialize() { }

void WristT2Algae::Execute() {
    m_wrist->t2ReefAlgae();
}

void WristT2Algae::End(bool interrupted) {
    if (interrupted) {
        m_wrist->stop();
    }
}

bool WristT2Algae::IsFinished() {
    return m_wrist->isAtSetpoint();
}
