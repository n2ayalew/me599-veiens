#!/bin/bash
python "/home/nathaniel/sumo-0.32.0/tools/randomTrips.py" -n osm.net.xml --seed 42 --fringe-factor 5 -p 27.982247 -r osm.passenger.rou.xml -o osm.passenger.trips.xml -e 3600 --vehicle-class passenger --vclass passenger --prefix veh --min-distance 300 --trip-attributes 'speedDev="0.1" departLane="best"' --validate
