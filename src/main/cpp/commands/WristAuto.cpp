#include "commands/WristAuto.h"

WristAuto::WristAuto(WristSubsystem* wrist)
    : m_wrist(wrist) {
    AddRequirements({wrist});
}

void WristAuto::Initialize() { }

void WristAuto::Execute() {
    m_wrist->t1Coral();
}

void WristAuto::End(bool interrupted) {
    if (interrupted) {
        m_wrist->stop();
    }
}

bool WristAuto::IsFinished() {
    return m_wrist->isAtSetpoint(); //Could also return false. Needs testing.
}
