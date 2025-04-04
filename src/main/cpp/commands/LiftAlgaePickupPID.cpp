#include "commands/LiftAlgaePickupPID.h"

LiftAlgaePickupPID::LiftAlgaePickupPID(LiftSubsystem* lift)
    : m_lift(lift) {
    AddRequirements({lift});
}

void LiftAlgaePickupPID::Initialize() { }

void LiftAlgaePickupPID::Execute() {
    m_lift->collectAlgaePID();
    m_inst.GetTable("Debuging")->PutNumber("LiftPID", double(m_lift->getPIDPosition()));
}

void LiftAlgaePickupPID::End(bool interrupted) {
    if (interrupted) {
        m_lift->stop();
    }
}

bool LiftAlgaePickupPID::IsFinished() {
    return m_lift->isAtSetpoint();
}
