#ifndef _READ_PARTICLES_FROM_HEPMC_H_
#define _READ_PARTICLES_FROM_HEPMC_H_

// HepMC headers
#include "HepMC/GenEvent.h"
#include "HepMC/GenParticle.h"
#include "HepMC/IO_GenEvent.h"

#include "TauSpinner/SimpleParticle.h"
#include <vector>
 
/** Read HepMC::GenEvent.

  Read HepMC event from data file
  and return particles needed for tau spin weight calculation.
  
  This routine is prepared for use with files generated by Pythia8.
  Fills:
  
  'X'              - Heavy particle (W+/-, H+/-, H, Z)
  'tau'            - first tau
  
  'tau_daughters'  - daughters of 'tau'
  'tau2_daughters' - daughters of 'tau2' or empty list, if 'tau2' is nu_tau.
  
  Returns:
  0 - event processed correctly 
  1 - empty event or no decay found in the event
*/
int readParticlesFromHepMC(const HepMC::GenEvent *event, 
                           TauSpinner::SimpleParticle &X,
                           TauSpinner::SimpleParticle &tau, 
                           TauSpinner::SimpleParticle &tau2, 
                           std::vector<TauSpinner::SimpleParticle> &tau_daughters, 
                           std::vector<TauSpinner::SimpleParticle> &tau2_daughters);

/** Get daughters of HepMC::GenParticle

  Recursively searches for final-state daughters of 'x' */
std::vector<TauSpinner::SimpleParticle> *getDaughters(HepMC::GenParticle *x);

/** Find last self

  Recursively finds the last particle with the same PDG ID
  on the list of its decay products */
HepMC::GenParticle *findLastSelf(HepMC::GenParticle *x);
bool isFirst(HepMC::GenParticle *x);
#endif
