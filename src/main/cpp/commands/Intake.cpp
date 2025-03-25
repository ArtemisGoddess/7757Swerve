#include "commands/Intake.h"

Intake::Intake(IntakeSubsystem* intake, double speed)
    : m_intake(intake), m_speed(speed) {
    AddRequirements({intake});
}

void Intake::Initialize() { }

void Intake::Execute() {
    m_intake->intake(m_speed);
}

void Intake::End(bool interrupted) {
    if (interrupted) {
        m_intake->stop();
    }
}

bool Intake::IsFinished() {
    return false;
}
