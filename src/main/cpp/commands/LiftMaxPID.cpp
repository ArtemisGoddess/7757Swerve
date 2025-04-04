#include "commands/LiftMaxPID.h"

LiftMaxPID::LiftMaxPID(LiftSubsystem* lift)
    : m_lift(lift) {
    AddRequirements({lift});
}

void LiftMaxPID::Initialize() { }

void LiftMaxPID::Execute() {
    m_lift->maxPID();
    m_inst.GetTable("Debuging")->PutNumber("LiftPID", double(m_lift->getPIDPosition()));
}

void LiftMaxPID::End(bool interrupted) {
    if (interrupted) {
        m_lift->stop();
    }
}

bool LiftMaxPID::IsFinished() {
    return m_lift->isAtSetpoint(); //Could also return false. Needs testing.
}
