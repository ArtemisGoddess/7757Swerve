#include "commands/LiftNetAlgae.h"

LiftNetAlgae::LiftNetAlgae(LiftSubsystem* lift)
    : m_lift(lift) {
    AddRequirements({lift});
}

void LiftNetAlgae::Initialize() { }

void LiftNetAlgae::Execute() {
    m_lift->scoreNetAlgae();
}

void LiftNetAlgae::End(bool interrupted) {
    if (interrupted) {
        m_lift->stop();
    }
}

bool LiftNetAlgae::IsFinished() {
    return m_lift->isAtSetpoint();
}
