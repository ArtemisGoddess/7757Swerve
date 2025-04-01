#include "commands/LiftRestPID.h"

LiftRestPID::LiftRestPID(LiftSubsystem* lift)
    : m_lift(lift) {
    AddRequirements({lift});
}

void LiftRestPID::Initialize() { }

void LiftRestPID::Execute() {
    m_lift->restPID();
    m_inst.GetTable("Debuging")->PutNumber("LiftPID", double(m_lift->getPIDPosition()));
}

void LiftRestPID::End(bool interrupted) {
    if (interrupted) {
        m_lift->stop();
    }
}

bool LiftRestPID::IsFinished() {
    return m_lift->isAtRest();
}
