#include "commands/AlignDrivebase.h"

AlignDrivebase::AlignDrivebase(VisSubsystem* vis, subsystems::CommandSwerveDrivetrain* drivetrain) //This is for color detection and automatic alignmnet
    : m_vis(vis), m_drivetrain(drivetrain) {
    AddRequirements({vis, drivetrain});
}

void AlignDrivebase::Initialize() { }

void AlignDrivebase::Execute() {
    m_vis->alignDrivebase(m_drivetrain);
}

void AlignDrivebase::End(bool interrupted) { }

bool AlignDrivebase::IsFinished() {
    return false; //On button release, kill the command.
}
