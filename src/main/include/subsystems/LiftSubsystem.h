#pragma once

#include "Telemetry.h" //You need this for the motors!
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h> //Subsystem things
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/DigitalInput.h>

#include <generated/TunerConstants.h>
#include "Config.h"


class LiftSubsystem : public frc2::SubsystemBase {
    public:
        LiftSubsystem();

        void raise();
        void lower();
        void stop();

        void manualRaise(units::turn_t speed);

        void setPID(units::turn_t position); //For manual control. Do not use this, use the other functions.

        void collectAlgaePID(); 
        void restPID(); //Rest position

        void t1Coral();
        void t2Coral();
        void t3Coral();
        void t4Coral();

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