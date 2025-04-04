#include "commands/WristNetAlgae.h"

WristNetAlgae::WristNetAlgae(WristSubsystem* wrist)
    : m_wrist(wrist) {
    AddRequirements({wrist});
}

void WristNetAlgae::Initialize() { }

void WristNetAlgae::Execute() {
    m_wrist->scoreNetAlgae();
}

void WristNetAlgae::End(bool interrupted) {
    if (interrupted) {
        m_wrist->stop();
    }
}

bool WristNetAlgae::IsFinished() {
    return m_wrist->isAtSetpoint();
}
