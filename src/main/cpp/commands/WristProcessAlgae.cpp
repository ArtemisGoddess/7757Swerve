#include "commands/WristProcessAlgae.h"

WristProcessAlgae::WristProcessAlgae(WristSubsystem* wrist)
    : m_wrist(wrist) {
    AddRequirements({wrist});
}

void WristProcessAlgae::Initialize() { }

void WristProcessAlgae::Execute() {
    m_wrist->scoreProcessAlgae();
}

void WristProcessAlgae::End(bool interrupted) {
    if (interrupted) {
        m_wrist->stop();
    }
}

bool WristProcessAlgae::IsFinished() {
    return m_wrist->isAtSetpoint();
}
