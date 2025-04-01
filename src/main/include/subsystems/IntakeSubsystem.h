#pragma once

#include <frc2/command/SubsystemBase.h> //Subsystem things
#include <generated/TunerConstants.h>

#include "Telemetry.h" //You need this for the motors!
#include "Config.h"


class IntakeSubsystem : public frc2::SubsystemBase {
    public:
        IntakeSubsystem();

        void intake(double speed);

        void outtake(double speed);

        void stop();

        bool isIntaking();

        int intakeDirection();

    private:
        //Main Intake
        ctre::phoenix6::hardware::TalonFX m_intake{IntakeConstants::mainIntakeID, CAN}; //This is the higher motor
        //Intake follower
        ctre::phoenix6::hardware::TalonFX i_follower{IntakeConstants::followerIntakeID, CAN}; //This is the lower motor
        //Holds if the intake is currently active or not
        bool intakeActive;
        /*Holds what direction the intake is going.
        * - 0 is not moving
        * - 1 is intaking
        * - 2 is outtaking
        */
       int intakeDirectionVal;
};