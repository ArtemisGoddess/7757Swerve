#pragma once

#include <frc2/command/SubsystemBase.h> //Subsystem things
#include <generated/TunerConstants.h>

#include "Telemetry.h" //You need this for the motors!
#include "Config.h"


class LiftSubsystem : public frc2::SubsystemBase {
    public:
        LiftSubsystem();

        void raise();
        void lower();
        void stop();

        void restPID(); //Rest position
        void maxPID(); //Max position

        void t1Coral(); //Unused and theoretical
        void t2Coral();
        void t3Coral();
        void t4Coral();

        void collectAlgaePID(); 

        void t1ReefAlgae();
        void t2ReefAlgae();

        void scoreNetAlgae();
        void scoreProcessAlgae();

        units::turn_t getPIDPosition();
        bool isAtSetpoint();
        bool isAtRest();
    
    private:
        //Main lift
        ctre::phoenix6::hardware::TalonFX m_lift{LiftConstants::mainLiftID, CAN};
        //Lift follower 1
        ctre::phoenix6::hardware::TalonFX l_follower1{LiftConstants::followerLiftID1, CAN};
        //Lift follower 1
        ctre::phoenix6::hardware::TalonFX l_follower2{LiftConstants::followerLiftID2, CAN};
        //Current setpoint for PID
        units::turn_t m_setpoint = 0_tr;
};