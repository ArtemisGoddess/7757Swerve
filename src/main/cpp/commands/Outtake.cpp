#include "commands/Outtake.h"

Outtake::Outtake(IntakeSubsystem* intake, double speed)
    : m_intake(intake), m_speed(speed) {
    AddRequirements({intake});
}

void Outtake::Initialize() { }

void Outtake::Execute() {
    m_intake->outtake(m_speed);
}

void Outtake::End(bool interrupted) {
    if (interrupted) {
        m_intake->stop();
    }
}

bool Outtake::IsFinished() {
    return false;
}

//0.816895