#ifndef Pythia_Source_h
#define Pythia_Source_h

/** \class PythiaSource
 *
 * Generates Pythia HepMC events
 *
 * Hector Naves                                  
 *   for the Generator Interface. 26/10/05 
 * Patrick Janot
 *   read all possible cards for Pythia Setup. 26/02/06
 *   ( port from FAMOS )
 ***************************************/

#define PYCOMP pycomp_

#include "FWCore/Framework/interface/GeneratedInputSource.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <map>
#include <string>
#include "HepMC/GenEvent.h"

#include "GeneratorInterface/CommonInterface/interface/TauolaInterface.h"
#include "GeneratorInterface/Pythia6Interface/interface/PtYDistributor.h"

class Run;
namespace CLHEP {
class HepRandomEngine;
class RandFlat;
}

namespace edm
{
  class PythiaSource : public GeneratedInputSource {
  public:

    /// Constructor
    PythiaSource(const ParameterSet &, const InputSourceDescription &);
    /// Destructor
    virtual ~PythiaSource();

    void endRun( Run& r);


  private:

    /// Interface to the PYGIVE pythia routine, with add'l protections
    bool call_pygive(const std::string& iParm );
    bool call_txgive(const std::string& iParm );
    bool call_txgive_init();
    bool call_slhagive(const std::string& iParm );
    bool call_slha_init();
  
  private:
    
    virtual bool produce(Event & e);
    void clear();
    
    HepMC::GenEvent  *evt;
    
    /// Pythia PYLIST Verbosity flag
    unsigned int pythiaPylistVerbosity_;
    /// HepMC verbosity flag
    bool pythiaHepMCVerbosity_;
    /// Impose proper times for pions/kaons at generator level
    bool imposeProperTimes_;
    /// Events to print if verbosity
    unsigned int maxEventsToPrint_;    
   
    // external cross section and filter efficiency
    double extCrossSect;
    double extFilterEff;    
 
    // for single particle generation in pythia
    int    particleID;
    std::vector<int> particleIDs;
    bool   doubleParticle;
    std::string kinedata;
    double ptmin, ptmax;
    double etamin, etamax;
    double phimin, phimax;
    double comenergy;
    double emin, emax;
    double ymin, ymax;  
    bool flatEnergy;
    
    // external generators (tauola,...)
    bool useExternalGenerators_ ;
    bool useTauola_ ;
    bool useTauolaPolarization_ ;
    TauolaInterface tauola_ ;
    
    bool stopHadronsEnabled;
    bool gluinoHadronsEnabled;
        
    CLHEP::HepRandomEngine& fRandomEngine;
    CLHEP::RandFlat*        fRandomGenerator; 
    PtYDistributor*         fPtYGenerator;
  };
} 

#endif
