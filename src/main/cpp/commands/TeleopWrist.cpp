#include "commands/TeleopWrist.h"

TeleopWrist::TeleopWrist(WristSubsystem* wrist, units::turn_t speed) 
    : m_wrist(wrist), m_speed(speed) {
    AddRequirements({wrist});
}

void TeleopWrist::Initialize() { }

void TeleopWrist::Execute() {
    m_wrist->manualRaise(m_speed);
}

void TeleopWrist::End(bool interrupted) { 
    m_wrist->stop();
}

bool TeleopWrist::IsFinished() {
    return false; 
}
