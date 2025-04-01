#include "commands/LiftT2Algae.h"

LiftT2Algae::LiftT2Algae(LiftSubsystem* lift)
    : m_lift(lift) {
    AddRequirements({lift});
}

void LiftT2Algae::Initialize() { }

void LiftT2Algae::Execute() {
    m_lift->t1ReefAlgae();
}

void LiftT2Algae::End(bool interrupted) {
    if (interrupted) {
        m_lift->stop();
    }
}

bool LiftT2Algae::IsFinished() {
    return m_lift->isAtSetpoint();
}
