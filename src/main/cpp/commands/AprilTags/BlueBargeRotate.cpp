#include "commands/AprilTags/BlueBargeRotate.h"

BlueBargeRotate::BlueBargeRotate(VisSubsystem* vis, DriveSubsystem* drive, subsystems::CommandSwerveDrivetrain* drivetrain, int tagID) 
    : m_vis(vis), m_drive(drive), m_drivetrain(drivetrain), m_tagID(tagID) {
    AddRequirements({vis, drive, drivetrain});
}

void BlueBargeRotate::Initialize() { }

void BlueBargeRotate::Execute() {
    if (m_tagID == 14) {
        m_drive->moveDrivebase(m_drivetrain, 35, units::length::meter_t(m_vis->distanceToTag() - 5), 0_m);
    }

    if (m_tagID == 15) {
        m_drive->moveDrivebase(m_drivetrain, 325, units::length::meter_t(m_vis->distanceToTag() - 5), 0_m);
    }
    
}

void BlueBargeRotate::End(bool interrupted) { }

bool BlueBargeRotate::IsFinished() {
    return m_drive->isAtPos(m_drivetrain); 
}
