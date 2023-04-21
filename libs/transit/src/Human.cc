#define _USE_MATH_DEFINES
#include "Human.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"

Human::Human(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];

    // notification: human creation
    std::string notif = details["name"].ToString()
                        + " was created at {"
                            + std::to_string(position.x).substr(0, std::to_string(position.x).size()-4)
                            + ", " + std::to_string(position.x).substr(0, std::to_string(position.y).size()-4)
                            + ", " + std::to_string(position.x).substr(0, std::to_string(position.z).size()-4)
                            +"}";
    Notify(notif);
}

Human::~Human() {
  // Delete dynamically allocated variables
  delete graph;
}

void Human::CreateNewDestination() {
    destination = {Random(-1400, 1500), position.y, Random(-800, 800)};
    toDestination = new AstarStrategy(position, destination, graph);

    // notification: heading to destination
    std::string notif = details["name"].ToString()
                        + " is on the way to {"
                        + std::to_string(destination.x).substr(0, std::to_string(destination.x).size()-4)
                        + ", " + std::to_string(destination.x).substr(0, std::to_string(destination.y).size()-4)
                        + ", " + std::to_string(destination.x).substr(0, std::to_string(destination.z).size()-4)
                        +"}";
    Notify(notif);
}

void Human::Update(double dt, std::vector<IEntity*> scheduler) {
    if (toDestination) {
        if (toDestination->IsCompleted()) {
            CreateNewDestination();
        } else {
            toDestination->Move(this, dt);
        }
    } else {
        CreateNewDestination();
    }
}
