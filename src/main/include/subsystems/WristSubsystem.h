#pragma once

#include "Telemetry.h" //You need this for the motors!
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h> //Subsystem things
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/DigitalInput.h>
#include "Config.h"

#include <generated/TunerConstants.h>


class WristSubsystem : public frc2::SubsystemBase {
    public:
        WristSubsystem();

        void raise();
        void lower();
        void stop();

        void manualRaise(units::turn_t speed);

        void setPID(units::turn_t position); //For manual control. Do not use this, use the other functions.

        void collectAlgaePID();
        void restPID(); //Rest position.

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
        //Main wrist
        ctre::phoenix6::hardware::TalonFX m_wrist{15, CAN};
        //Wrist follower
        ctre::phoenix6::hardware::TalonFX w_follower{16, CAN};
        //Current setpoint for PID
        units::turn_t m_setpoint = 0_tr;
};