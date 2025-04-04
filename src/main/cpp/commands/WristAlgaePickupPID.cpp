#include "commands/WristAlgaePickupPID.h"

WristAlgaePickupPID::WristAlgaePickupPID(WristSubsystem* wrist)
    : m_wrist(wrist) {
    AddRequirements({wrist});
}

void WristAlgaePickupPID::Initialize() { }

void WristAlgaePickupPID::Execute() {
    m_wrist->collectAlgaePID();
}

void WristAlgaePickupPID::End(bool interrupted) {
    if (interrupted) {
        m_wrist->stop();
    }
}

bool WristAlgaePickupPID::IsFinished() {
    return m_wrist->isAtSetpoint();
}
