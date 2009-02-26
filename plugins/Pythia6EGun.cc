
#include <iostream>

#include "Pythia6EGun.h"

#include "FWCore/Utilities/interface/Exception.h"

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "GeneratorInterface/Pythia6Interface/interface/PYR.h"

#include "FWCore/Framework/interface/MakerMacros.h"

using namespace edm;
using namespace gen;

Pythia6EGun::Pythia6EGun( const ParameterSet& pset ) :
   Pythia6Gun(pset)
{
   
   // ParameterSet defpset ;
   ParameterSet pgun_params = 
      pset.getParameter<ParameterSet>("PGunParameters"); // , defpset ) ;
   fMinE       = pgun_params.getParameter<double>("MinE"); // ,  0.);
   fMaxE       = pgun_params.getParameter<double>("MaxE"); // ,  0.);
   fAddAntiParticle = pgun_params.getParameter<bool>("AddAntiParticle"); //, false) ;  

}

Pythia6EGun::~Pythia6EGun()
{
}

void Pythia6EGun::generateEvent()
{
   
   // now actualy, start cooking up the event gun 
   //

   // 1st, primary vertex
   //
   HepMC::GenVertex* Vtx = new HepMC::GenVertex( HepMC::FourVector(0.,0.,0.));

   // here re-create fEvt (memory)
   //
   fEvt = new HepMC::GenEvent() ;
     
   int ip=1;
   for ( size_t i=0; i<fPartIDs.size(); i++ )
   {
	 int particleID = fPartIDs[i]; // this is PDG - need to convert to Py6 !!!
         int dum = 0;
	 double ee=0,the=0,eta=0;
	 double mass = pymass_(particleID);
	 double phi = (fMaxPhi-fMinPhi)*pyr_(&dum)+fMinPhi;
	 ee   = (fMaxE-fMinE)*pyr_(&dum)+fMinE;
	 eta  = (fMaxEta-fMinEta)*pyr_(&dum)+fMinEta;                                                      
	 the  = 2.*atan(exp(-eta));                                                                          
	 
	 py1ent_(ip, particleID, ee, the, phi);
	 
         double mom2   = ee*ee - mass*mass ;
         double mom    = 0. ;
         if (mom2 > 0.) 
         {
            mom = sqrt(mom2) ;
         }
         else
         {
            mom = 0. ;
         }
         double px     = mom*sin(the)*cos(phi) ;
         double py     = mom*sin(the)*sin(phi) ;
         double pz     = mom*cos(the) ;
         
	 HepMC::FourVector p(px,py,pz,ee) ;
         HepMC::GenParticle* Part = 
             new HepMC::GenParticle(p,particleID,1);
         Part->suggest_barcode( ip ) ;
         Vtx->add_particle_out(Part);
	 
	 if(fAddAntiParticle)
	 {
	    ip = ip + 1;
// Check if particle is its own anti-particle.
            int pythiaCode = pycomp_(particleID); // this is py6 internal validity check, it takes Pythia6 pid
	                                          // so actually I'll need to convert
            int has_antipart = pydat2.kchg[3-1][pythiaCode-1];
            int particleID2 = has_antipart ? -1 * particleID : particleID;	    
	    the = 2.*atan(exp(eta));
	    phi  = phi + M_PI;
	    if (phi > 2.* M_PI) {phi = phi - 2.* M_PI;}         
	    py1ent_(ip, particleID2, ee, the, phi);
            HepMC::FourVector ap(-px,-py,-pz,ee) ;
	    HepMC::GenParticle* APart =
	       new HepMC::GenParticle(ap,particleID2,1);
	    APart->suggest_barcode( ip ) ;
	    Vtx->add_particle_out(APart) ;	    
	 }
	 ip++;
   }
   
   fEvt->add_vertex(Vtx);
     
   // run pythia
   pyexec_();
   
   return;
}

DEFINE_FWK_MODULE(Pythia6EGun);