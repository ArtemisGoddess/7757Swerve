#include "commands/AlignDrivebase.h"

AlignDrivebase::AlignDrivebase(VisSubsystem* vis, subsystems::CommandSwerveDrivetrain* drivetrain, bool withAprilTag) 
    : m_vis(vis), m_drivetrain(drivetrain), m_withAprilTag(withAprilTag) {
    AddRequirements({vis, drivetrain});
}

void AlignDrivebase::Initialize() { }

void AlignDrivebase::Execute() {
    m_vis->alignDrivebase(m_withAprilTag, m_drivetrain);
}

void AlignDrivebase::End(bool interrupted) { }

bool AlignDrivebase::IsFinished() {
    return false; 
}
