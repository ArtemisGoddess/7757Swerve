#include "commands/AprilTags/RedBargeRotate.h"

RedBargeRotate::RedBargeRotate(VisSubsystem* vis, DriveSubsystem* drive, subsystems::CommandSwerveDrivetrain* drivetrain, int tagID) 
    : m_vis(vis), m_drive(drive), m_drivetrain(drivetrain), m_tagID(tagID) {
    AddRequirements({vis, drive, drivetrain});
}

void RedBargeRotate::Initialize() { }

void RedBargeRotate::Execute() {
    if (m_tagID == 5) {
        m_drive->moveDrivebase(m_drivetrain, 35, units::length::meter_t(m_vis->distanceToTag() - 5), 0_m);
    }

    if (m_tagID == 4) {
        m_drive->moveDrivebase(m_drivetrain, 325, units::length::meter_t(m_vis->distanceToTag() - 5), 0_m);
    }
    
}

void RedBargeRotate::End(bool interrupted) { }

bool RedBargeRotate::IsFinished() {
    return m_drive->isAtPos(m_drivetrain); 
}
