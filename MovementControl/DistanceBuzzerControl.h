/*
  DistanceBuzzerControl

  DistanceBuzzerControl will either constantly buzz a buzzer, intermittenly buzz a buzzer, or not buzz a buzzer depending on internal state

  Pass in a distance to start intermittent Buzzing and a distance for constant buzzing and pass
  a distance from a object, then the update method will handle the states for you

  Written By: Levi Butcher
 */

#pragma once


class DistanceBuzzerControl {

  private:
      int buzzerPin;
      int intermittentDistance;
      int constantDistance;
      enum DB_STATES {START, INTERMITTENT, CONSTANT, OFF};
      DB_STATES DB_STATE;

  public:
    DistanceBuzzerControl(int buzzerPin, int intermittentDistance, int constantDistance);
    void update(int distance);
};
