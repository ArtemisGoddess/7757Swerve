#include "commands/WristT1Algae.h"

WristT1Algae::WristT1Algae(WristSubsystem* wrist)
    : m_wrist(wrist) {
    AddRequirements({wrist});
}

void WristT1Algae::Initialize() { }

void WristT1Algae::Execute() {
    m_wrist->t1ReefAlgae();
}

void WristT1Algae::End(bool interrupted) {
    if (interrupted) {
        m_wrist->stop();
    }
}

bool WristT1Algae::IsFinished() {
    return m_wrist->isAtSetpoint();
}
