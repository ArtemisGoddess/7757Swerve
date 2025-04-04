#include "commands/WristMaxPID.h"

WristMaxPID::WristMaxPID(WristSubsystem* wrist)
    : m_wrist(wrist) {
    AddRequirements({wrist});
}

void WristMaxPID::Initialize() { }

void WristMaxPID::Execute() {
    m_wrist->maxPID();
    m_inst.GetTable("Debuging")->PutNumber("LiftPID", double(m_wrist->getPIDPosition()));
}

void WristMaxPID::End(bool interrupted) {
    if (interrupted) {
        m_wrist->stop();
    }
}

bool WristMaxPID::IsFinished() {
    return m_wrist->isAtSetpoint(); //Could also return false. Needs testing.
}
