#ifndef __IMAVEINS_IMAAPP_H_
#define __IMAVEINS_IMAAPP_H_

#include <omnetpp.h>
#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"


using Veins::TraCIMobility;
using Veins::TraCICommandInterface;

using namespace omnetpp;

/**
 * @brief
 * Warns driver's of a potential collision.
 *
 * The speedMode of one car is set, in TraCIMobility class,
 * to 0x07 and speed is set to its last non-zero value. This will cause that car
 * to run a red light. However, since all cars are sending and recieving bsm's that
 * include their speed and coordinates then any vehicle in the vicinity of the junction
 * may deduce that this illegal event may occur and proceed with caution. Note the traffic
 * light state shall be communicated by the IMARSU node.
 *
 * @author Nathaniel Ayalew
 *
 */

class IMAApp : public BaseWaveApplLayer {
    public:
        virtual void initialize(int stage);
        virtual void finish();

    protected:
        virtual void onBSM(BasicSafetyMessage* bsm) override;
        virtual void handleSelfMsg(cMessage* msg);
        virtual void handlePositionUpdate(cObject* obj);
        //TraCICommandInterface::Junction kingUniJunction;
    protected:
        cOutVector warningsXpos;
        cOutVector warningsYpos;
        cOutVector warningsXvel;
        cOutVector warningsYvel;
        cOutVector distances;
        cOutVector senderAddresses;

    private:
        const std::string kingUniId = "15434355";
        const int warningDist = 28;
        //const double alaramTime = 2.016; // hack to speed this up
        const double alaramTime = 1.0;
        Coord kingUniCoord;
        cMessage* startAccidentMsg;
        cMessage* stopAccidentMsg;
        int accidentCount; /**< number of accidents */
        uint32_t lastSpeedMode;
    };

#endif
