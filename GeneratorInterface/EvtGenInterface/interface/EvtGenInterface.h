#ifndef gen_EvtGenInterface_h
#define gen_EvtGenInterface_h

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <memory>
#include <string>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "GeneratorInterface/EvtGenInterface/interface/EvtGenInterfaceBase.h"

class myEvtRandomEngine;

namespace HepMC {
  class GenParticle;
  class GenEvent;
}				

class EvtId; 
class EvtGen;

namespace gen {
   class EvtGenInterface : public EvtGenInterfaceBase {
     public:
    // ctor & dtor
    EvtGenInterface( const edm::ParameterSet& );
    ~EvtGenInterface();
    
    virtual void init();
    virtual const std::vector<int>& operatesOnParticles() { return m_PDGs; }      
    virtual HepMC::GenEvent* decay( HepMC::GenEvent* );
    virtual void setRandomEngine(CLHEP::HepRandomEngine* v);
    static double flat();
    
  private:
    void addToHepMC(HepMC::GenParticle* partHep,const EvtId &idEvt, HepMC::GenEvent* theEvent);
    void update_particles(HepMC::GenParticle* partHep,HepMC::GenEvent* theEvent,HepMC::GenParticle* p);
    void SetDefault_m_PDGs();
    
    EvtGen *m_EvtGen;                // EvtGen main  object

    std::vector<EvtId> forced_id;     // EvtGen Id's of particles  which are to be forced by EvtGen
    std::vector<int> forced_pdgids;    // PDG Id's of particles which are to be forced by EvtGen
    
    std::vector<int> ignore_pdgids;  // HepId's of particles  which are to be ignroed by EvtGen
    
    // Adding parameters for polarization of spin-1/2 particles
    std::vector<int> polarize_ids;
    std::vector<double> polarize_pol;
    std::map<int, float> polarizations;
        
    edm::ParameterSet* fPSet;

    static CLHEP::HepRandomEngine* fRandomEngine;
    myEvtRandomEngine* the_engine;
  };
}
#endif
