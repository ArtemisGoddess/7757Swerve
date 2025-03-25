#include "commands/TeleopWrist.h"

TeleopWrist::TeleopWrist(WristSubsystem* wrist, double speed) 
    : m_wrist(wrist), m_speed(speed) {
    AddRequirements({wrist});
}

void TeleopWrist::Initialize() { }

void TeleopWrist::Execute() {
    if (m_wrist->getPIDPosition() >= WristConstants::groundIntakePID || m_wrist->getPIDPosition() <= WristConstants::putAwayPID) {
        m_wrist->manualRaise(m_speed);
    }
}

void TeleopWrist::End(bool interrupted) { }

bool TeleopWrist::IsFinished() {
    return false;
}
