#include "commands/LiftProcessAlgae.h"

LiftProcessAlgae::LiftProcessAlgae(LiftSubsystem* lift)
    : m_lift(lift) {
    AddRequirements({lift});
}

void LiftProcessAlgae::Initialize() { }

void LiftProcessAlgae::Execute() {
    m_lift->scoreProcessAlgae();
}

void LiftProcessAlgae::End(bool interrupted) {
    if (interrupted) {
        m_lift->stop();
    }
}

bool LiftProcessAlgae::IsFinished() {
    return m_lift->isAtSetpoint();
}
