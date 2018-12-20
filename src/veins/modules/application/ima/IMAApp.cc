#include "IMAApp.h"

Define_Module(IMAApp);

void IMAApp::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);
    if (stage == 0) {
        EV << "Initializing " << par("appName").stringValue() << std::endl;
        TraCICommandInterface::Junction kingUniJunction = traci->junction(kingUniId);

        simtime_t firstBeacon = simTime();
        simtime_t randomOffset = dblrand() * beaconInterval;
        firstBeacon = simTime() + randomOffset;
        warningsXpos.setName("xPosAtWarning");
        warningsYpos.setName("yPosAtWarning");
        warningsXvel.setName("xVelAtWarning");
        warningsYvel.setName("yVelAtWarning");
        distances.setName("Distances");
        senderAddresses.setName("SenderAdresses");
    }
    else if (stage == 1) {
        //Initializing members that require initialized other modules goes here

    }
}

void IMAApp::finish() {
    BaseWaveApplLayer::finish();
    //statistics recording goes here

}

void IMAApp::onBSM(BasicSafetyMessage* bsm) {
    //Your application has received a beacon message from another car or RSU
    //code for handling the message goes here
    Coord pos2 = bsm->getSenderPos();
    Coord vel2 = bsm->getSenderSpeed();
    double t = alaramTime + (simTime() - bsm->getTimestamp()).dbl();
    double xpredict = pos2.x + vel2.x*(t);
    double ypredict = pos2.y + vel2.y*(t);
    Coord D(xpredict, ypredict);
    //Coord D(pos2.x + vel2.x*alaramTime - (curPosition.x + curSpeed.x*alaramTime), pos2.y + vel2.y*alaramTime - (curPosition.y + curSpeed.y*alaramTime));
    EV_INFO_C("bsm_test") << "Recieved Pos (" << pos2.x << ", " << pos2.y << ")" << std::endl;
    EV_INFO_C("bsm_test") << "Recieved Vel (" << vel2.x << ", " << vel2.y << ")" << std::endl;
    EV_INFO_C("bsm_test") << "D (" << D.x << ", " << D.y << ")" << std::endl;
    if ( curPosition.distance(D) /*sqrt(D.x*D.x + D.y*D.y)*/ < warningDist) {
        warningsXpos.record(curPosition.x);
        warningsYpos.record(curPosition.y);
        warningsXvel.record(curSpeed.x);
        warningsYvel.record(curSpeed.y);
        distances.record(curPosition.distance(D));
        senderAddresses.record(bsm->getSenderAddress());
        EV << "Accident occured!" << std::endl;
    }
}

/*
void IMAApp::onWSM(WaveShortMessage* wsm) {
    //Your application has received a data message from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples

}

void IMAApp::onWSA(WaveServiceAdvertisment* wsa) {
    //Your application has received a service advertisement from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples

}*/

void IMAApp::handleSelfMsg(cMessage* msg) {
    BaseWaveApplLayer::handleSelfMsg(msg);
    //this method is for self messages (mostly timers)
    //it is important to call the BaseWaveApplLayer function for BSM and WSM transmission
    /*if (msg == startAccidentMsg) {
        traciVehicle->setSpeed(50);
        traciVehicle->setSpeedMode(0);
        EV << "Accident Started "  << std::endl;
        simtime_t accidentDuration = mobility->getAccidentDuration();
        scheduleAt(simTime() + accidentDuration, stopAccidentMsg);
        accidentCount--;
    }
    else if (msg == stopAccidentMsg) {
        traciVehicle->setSpeedMode(0xffff);
        traciVehicle->setSpeed(-1);
        if (accidentCount > 0) {
            simtime_t accidentInterval = par("accidentInterval");
            scheduleAt(simTime() + accidentInterval, startAccidentMsg);
        }
    }*/

}

void IMAApp::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);
    //the vehicle has moved. Code that reacts to new positions goes here.
    //member variables such as currentPosition and currentSpeed are updated in the parent class

    EV_INFO_C("pos_test") << "Cur Pos (" << curPosition.x << ", " << curPosition.y << ")" << std::endl;
    EV_INFO_C("vel_test") << "Cur Vel (" << curSpeed.x << ", " << curSpeed.y << ")" << std::endl;


}
