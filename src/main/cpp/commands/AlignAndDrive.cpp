#include "commands/AlignAndDrive.h"

AlignAndDrive::AlignAndDrive(VisSubsystem* vis, subsystems::CommandSwerveDrivetrain* drivetrain) 
    : m_vis(vis), m_drivetrain(drivetrain) {
    AddRequirements({vis, drivetrain});
}

void AlignAndDrive::Initialize() { }

void AlignAndDrive::Execute() {
    m_vis->alignAndDrive(m_drivetrain);
}

void AlignAndDrive::End(bool interrupted) { }

bool AlignAndDrive::IsFinished() {
    return false; 
}
