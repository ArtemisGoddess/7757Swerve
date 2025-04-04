#pragma once

#include <frc2/command/SubsystemBase.h> //Subsystem things
#include <generated/TunerConstants.h>

#include "Telemetry.h" //You need this for the motors!
#include "Config.h"


class WristSubsystem : public frc2::SubsystemBase {
    public:
        WristSubsystem();

        void raise();
        void lower();
        void stop();

        void manualRaise(units::turn_t speed);

        void restPID(); //Rest position.
        void maxPID();

        void collectCoral();

        void t1Coral();
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
        //Main wrist
        ctre::phoenix6::hardware::TalonFX m_wrist{20, CAN};
        //Wrist follower left (maybe)
        ctre::phoenix6::hardware::TalonFX w_follower1{21, CAN};
        //Wrist follower right (maybe)
        ctre::phoenix6::hardware::TalonFX w_follower2{22, CAN};
        //Current setpoint for PID
        units::turn_t m_setpoint = 0_tr;
};