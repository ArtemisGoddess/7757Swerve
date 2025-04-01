#include "commands/LiftT1Algae.h"

LiftT1Algae::LiftT1Algae(LiftSubsystem* lift)
    : m_lift(lift) {
    AddRequirements({lift});
}

void LiftT1Algae::Initialize() { }

void LiftT1Algae::Execute() {
    m_lift->t1ReefAlgae();
}

void LiftT1Algae::End(bool interrupted) {
    if (interrupted) {
        m_lift->stop();
    }
}

bool LiftT1Algae::IsFinished() {
    return m_lift->isAtSetpoint();
}
