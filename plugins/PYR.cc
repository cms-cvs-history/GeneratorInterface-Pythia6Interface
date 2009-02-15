#include "GeneratorInterface/Pythia6Interface/interface/PYR.h"
#include "CLHEP/Random/RandomEngine.h"

CLHEP::HepRandomEngine* randomEngine;

extern "C" {
  double pyr_(int* idummy)
  {
    return randomEngine->flat();
  }
}
