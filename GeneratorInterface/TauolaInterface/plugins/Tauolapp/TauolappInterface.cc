/* this is the code for the new Tauola++ */

#include <iostream>

#include "GeneratorInterface/TauolaInterface/interface/TauolappInterface.h"

#include "Tauola/Tauola.h"
#include "Tauola/TauolaHepMCEvent.h"
#include "Tauola/Log.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "FWCore/Utilities/interface/Exception.h"

#include "CLHEP/Random/RandomEngine.h"

#include "HepMC/GenEvent.h"
#include "HepMC/IO_HEPEVT.h"
#include "HepMC/HEPEVT_Wrapper.h"

#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"

// LHE Run
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "GeneratorInterface/LHEInterface/interface/LHERunInfo.h"

// LHE Event
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "GeneratorInterface/LHEInterface/interface/LHEEvent.h"


using namespace gen;
using namespace edm;
using namespace std;

CLHEP::HepRandomEngine*  TauolappInterface::fRandomEngine = nullptr;

extern "C" {

  void gen::ranmar_( float *rvec, int *lenv )
  {
    for(int i = 0; i < *lenv; i++)
      *rvec++ = TauolappInterface::flat();
    return;
  }
  
  void gen::rmarin_( int*, int*, int* )
  {
    return;
  }
  
}

TauolappInterface::TauolappInterface( const edm::ParameterSet& pset):
  fPolarization(false),
  fPSet(0),
  fIsInitialized(false),
  fMDTAU(-1),
  fSelectDecayByEvent(false),
  lhe(NULL)
{
  if ( fPSet != 0 ) throw cms::Exception("TauolappInterfaceError") << "Attempt to override Tauola an existing ParameterSet\n" << std::endl;
  fPSet = new ParameterSet(pset);
}

TauolappInterface::~TauolappInterface(){if ( fPSet != 0 ) delete fPSet;}

void TauolappInterface::init( const edm::EventSetup& es ){
  if ( fIsInitialized ) return; // do init only once
  if ( fPSet == 0 ) throw cms::Exception("TauolappInterfaceError") << "Attempt to initialize Tauola with an empty ParameterSet\n" << std::endl;   
  
  fIsInitialized = true;
      
   es.getData( fPDGTable ) ;

   Tauolapp::Tauola::setDecayingParticle(15);
   // --> ??? Tauola::setRadiation(false);

   // polarization switch 
   //
   // fPolarization = fPSet->getParameter<bool>("UseTauolaPolarization") ? 1 : 0 ;
   fPolarization = fPSet->getParameter<bool>("UseTauolaPolarization");
   
   // read tau decay mode switches
   //
   ParameterSet cards = fPSet->getParameter< ParameterSet >("InputCards");
   
   fMDTAU = cards.getParameter< int >( "mdtau" );

   if ( fMDTAU == 0 || fMDTAU == 1 )
   {
      Tauolapp::Tauola::setSameParticleDecayMode( cards.getParameter< int >( "pjak1" ) ) ;
      Tauolapp::Tauola::setOppositeParticleDecayMode( cards.getParameter< int >( "pjak2" ) ) ;
   }

   Tauolapp::Tauola::spin_correlation.setAll(fPolarization);

   // some more options, copied over from an example 
   // Default values
   //Tauola::setEtaK0sPi(0,0,0); // switches to decay eta K0_S and pi0 1/0 on/off. 
 
   const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID( abs(Tauolapp::Tauola::getDecayingParticle()) )) ;
   double lifetime = PData->lifetime().value();
   Tauolapp::Tauola::setTauLifetime( lifetime );
   //std::cout << "Setting lifetime: ctau=" << lifetime << "m or tau=" << lifetime/(299792458.0*1000.0) << "s" << std::endl;

   fPDGs.push_back( Tauolapp::Tauola::getDecayingParticle() );

   Tauolapp::Tauola::setRandomGenerator(gen::TauolappInterface::flat);         
   Tauolapp::Tauola::initialize();

   Tauolapp::Tauola::spin_correlation.setAll(fPolarization);// Tauola switches this on during Tauola::initialise(); so we add this here to keep it on/off

   if (fPSet->exists("parameterSets")){
     std::vector<std::string> par = fPSet->getParameter< std::vector<std::string> >("parameterSets");
     for (unsigned int ip=0; ip<par.size(); ++ip ){
       std::string curSet = par[ip];
       
       if(curSet=="setNewCurrents") Tauolapp::Tauola::setNewCurrents(fPSet->getParameter<int>(curSet));
       if(curSet=="spinCorrelationSetAll") Tauolapp::Tauola::spin_correlation.setAll(fPSet->getParameter<bool>(curSet));
       if(curSet=="spinCorrelationGAMMA") Tauolapp::Tauola::spin_correlation.GAMMA=fPSet->getParameter<bool>(curSet);
       if(curSet=="spinCorrelationZ0") Tauolapp::Tauola::spin_correlation.Z0=fPSet->getParameter<bool>(curSet);
       if(curSet=="spinCorrelationHIGGS") Tauolapp::Tauola::spin_correlation.HIGGS=fPSet->getParameter<bool>(curSet);
       if(curSet=="spinCorrelationHIGGSH") Tauolapp::Tauola::spin_correlation.HIGGS_H=fPSet->getParameter<bool>(curSet);
       if(curSet=="spinCorrelationHIGGSA") Tauolapp::Tauola::spin_correlation.HIGGS_A=fPSet->getParameter<bool>(curSet);
       if(curSet=="spinCorrelationHIGGSPLUS") Tauolapp::Tauola::spin_correlation.HIGGS_PLUS=fPSet->getParameter<bool>(curSet);
       if(curSet=="spinCorrelationHIGGSMINUS") Tauolapp::Tauola::spin_correlation.HIGGS_MINUS=fPSet->getParameter<bool>(curSet);
       if(curSet=="spinCorrelationWPLUS") Tauolapp::Tauola::spin_correlation.W_PLUS=fPSet->getParameter<bool>(curSet);
       if(curSet=="spinCorrelationWMINUS") Tauolapp::Tauola::spin_correlation.W_MINUS=fPSet->getParameter<bool>(curSet);
       
       if(curSet=="setHiggsScalarPseudoscalarPDG") Tauolapp::Tauola::setHiggsScalarPseudoscalarPDG(fPSet->getParameter<int>(curSet));
       if(curSet=="setHiggsScalarPseudoscalarMixingAngle") Tauolapp::Tauola::setHiggsScalarPseudoscalarMixingAngle(fPSet->getParameter<double>(curSet));
       
       if(curSet=="setRadiation") Tauolapp::Tauola::setRadiation(fPSet->getParameter<bool>(curSet));
       if(curSet=="setRadiationCutOff") Tauolapp::Tauola::setRadiationCutOff(fPSet->getParameter<double>(curSet));
       
       if(curSet=="setEtaK0sPi"){
	 std::vector<int> vpar = fPSet->getParameter<std::vector<int> >(curSet);
	 if(vpar.size()==3) Tauolapp::Tauola::setEtaK0sPi(vpar[0],vpar[1],vpar[2]);
	 else {std::cout << "WARNING invalid size for setEtaK0sPi: " << vpar.size() << " Require 3 elements " << std::endl;}
       }
       
       if(curSet=="setTaukle"){
	 std::vector<double> vpar = fPSet->getParameter<std::vector<double> >(curSet);
	 if(vpar.size()==4) Tauolapp::Tauola::setTaukle(vpar[0], vpar[1], vpar[2], vpar[3]);
	 else {std::cout << "WARNING invalid size for setTaukle: " << vpar.size() << " Require 4 elements " << std::endl;}
       }
       
       if(curSet=="setTauBr"){
	 edm::ParameterSet cfg = fPSet->getParameter<edm::ParameterSet>(curSet);
	 std::vector<int> vJAK = cfg.getParameter<std::vector<int> >("JAK");
	 std::vector<double> vBR = cfg.getParameter<std::vector<double> >("BR");
	 if(vJAK.size() == vBR.size()){
	   for(unsigned int i=0;i<vJAK.size();i++) Tauolapp::Tauola::setTauBr(vJAK[i],vBR[i]);
	 }
	 else {std::cout << "WARNING invalid size for setTauBr - JAK: " << vJAK.size() << " BR: " << vBR.size() << std::endl;}
       }
     }
   }

   // override decay modes if needs be
   //
   // we have to do it AFTER init because otherwises branching ratios are NOT filled in
   //
   if ( fMDTAU != 0 && fMDTAU != 1 )
   {
      decodeMDTAU( fMDTAU );
   }

   Tauolapp::Log::LogWarning(false);
   
   return;
}

double TauolappInterface::flat()
{
   if ( !fRandomEngine ) {
     throw cms::Exception("LogicError")
       << "TauolaInterface::flat: Attempt to generate random number when engine pointer is null\n"
       << "This might mean that the code was modified to generate a random number outside the\n"
       << "event and beginLuminosityBlock methods, which is not allowed.\n";
   }
   return fRandomEngine->flat();
}

HepMC::GenEvent* TauolappInterface::decay( HepMC::GenEvent* evt ){
   if ( !fIsInitialized ) return evt;
   Tauolapp::Tauola::setRandomGenerator(gen::TauolappInterface::flat);   // rest tauola++ random number incase other modules use tauola++
   int NPartBefore = evt->particles_size();
   int NVtxBefore  = evt->vertices_size();
   
   // what do we do if Hep::GenEvent size is larger than 10K ???
   // Tauola (& Photos, BTW) can only handle up to 10K via HEPEVT,
   // and in case of CMS, it's only up to 4K !!!
   //
   // if ( NPartBefore > 10000 ) return evt;
   //
   
   // override decay mode if needs be
   if ( fSelectDecayByEvent )
   {
      selectDecayByMDTAU();
   }
   
   bool dolhe=true;
   if(dolhe){
     if(lhe!=NULL){
     std::vector<HepMC::GenParticle*> particles;
     std::vector<double> TauSPINUP;
     std::vector<double> spinup=lhe->getHEPEUP()->SPINUP;
     std::vector<int> pdg =lhe->getHEPEUP()->IDUP;
     for(unsigned int i=0;i<spinup.size();i++){
       if(abs(pdg.at(i))==15){
	 particles.push_back(new HepMC::GenParticle(HepMC::FourVector(lhe->getHEPEUP()->PUP.at(i)[0],lhe->getHEPEUP()->PUP.at(i)[1],lhe->getHEPEUP()->PUP.at(i)[2],lhe->getHEPEUP()->PUP.at(i)[3]),lhe->getHEPEUP()->IDUP.at(i)));
	 int status = lhe->getHEPEUP()->ISTUP.at(i);
	 particles.at(particles.size()-1)->set_generated_mass(lhe->getHEPEUP()->PUP.at(i)[4]);
	 particles.at(particles.size()-1)->set_status(status > 0 ? (status == 2 ? 3 : status) : 3);
	 TauSPINUP.push_back(spinup.at(i));
	 particles.at(particles.size()-1)->print();
	 std::cout << "Spinup: " << TauSPINUP.at(TauSPINUP.size()-1) << " " << pdg.at(i) << std::endl;
       }
     }
     }
     //TauolaParticle *tp = new TauolaHepMCParticle(p);
     //Tauola::decayOne(tp,true,0,0,Polarz);

   }
   //else{
     //construct tmp TAUOLA event
     auto * t_event = new Tauolapp::TauolaHepMCEvent(evt);
     // another option: if one lets Pythia or another master gen to decay taus, 
     //                 we have to undecay them first
     // t_event->undecayTaus();
     
     // run Tauola on the tmp event - HepMC::GenEvernt will be MODIFIED !!!
     //
     t_event->decayTaus();
     delete t_event; 
     // do we also need to apply the lifetime and vtx position shift ??? 
     // (see TauolappInterface, for example)
     //
     // NOTE: the procedure ASSYMES that vertex barcoding is COUNTIUOUS/SEQUENTIAL,
     // and that the abs(barcode) corresponds to vertex "plain indexing"
     //
     for ( int iv=NVtxBefore+1; iv<=evt->vertices_size(); iv++ ){
       HepMC::GenVertex* GenVtx = evt->barcode_to_vertex(-iv);
       //
       // now find decay products with funky barcode, weed out and replace with clones of sensible barcode
       // we can NOT change the barcode while iterating, because iterators do depend on the barcoding
       // thus we have to take a 2-step procedure
       //
       std::vector<int> BCodes;
       BCodes.clear();
       for (HepMC::GenVertex::particle_iterator pitr= GenVtx->particles_begin(HepMC::children);
	    pitr != GenVtx->particles_end(HepMC::children); ++pitr){
	 if ( (*pitr)->barcode() > 10000 ){
	   BCodes.push_back( (*pitr)->barcode() );
	 }
       }
       if ( BCodes.size() > 0 ){
	 for ( size_t ibc=0; ibc<BCodes.size(); ibc++ ){
	   HepMC::GenParticle* p1 = evt->barcode_to_particle( BCodes[ibc] );
	   int nbc = p1->barcode() - 10000 + NPartBefore;
	   p1->suggest_barcode( nbc );
	 }
       }             
     }
     //}
   return evt;
}

void TauolappInterface::statistics()
{
   return;
}

void TauolappInterface::decodeMDTAU( int mdtau )
{

   // Note-1:
   // I have to hack the common block directly because set<...>DecayMode(...)
   // only changes it in the Tauola++ instance but does NOT passes it over
   // to the Fortran core - this it does only one, via initialize() stuff...
   //
   // So I'll do both ways of settings, just for consistency...
   // but I probably need to communicate it to the Tauola(++) team...
   //
   
   // Note-2: 
   // originally, the 1xx settings are meant for tau's from hard event,
   // and the 2xx settings are for any tau in the event record;
   //
   // later one, we'll have to take this into account...
   // but first I'll have to sort out what happens in the 1xx case
   // to tau's coming outside of hard event (if any in the record)   
   //
   
   if ( mdtau == 101 || mdtau == 201 )
   {
      // override with electron mode for both tau's
      //
      Tauolapp::jaki_.jak1 = 1;
      Tauolapp::jaki_.jak2 = 1;
      Tauolapp::Tauola::setSameParticleDecayMode( 1 ) ;
      Tauolapp::Tauola::setOppositeParticleDecayMode( 1 ) ;
      return;
   }
   
   if ( mdtau == 102 || mdtau == 202 )
   {
      // override with muon mode for both tau's
      //
      Tauolapp::jaki_.jak1 = 2;
      Tauolapp::jaki_.jak2 = 2;
      Tauolapp::Tauola::setSameParticleDecayMode( 2 ) ;
      Tauolapp::Tauola::setOppositeParticleDecayMode( 2 ) ;
      return;
   }

   if ( mdtau == 111 || mdtau == 211 )
   {
      // override with electron mode for 1st tau 
      // and any mode for 2nd tau
      //
      Tauolapp::jaki_.jak1 = 1;
      Tauolapp::jaki_.jak2 = 0;
      Tauolapp::Tauola::setSameParticleDecayMode( 1 ) ;
      Tauolapp::Tauola::setOppositeParticleDecayMode( 0 ) ;
      return;
   }

   if ( mdtau == 112 || mdtau == 212 )
   {
      // override with muon mode for the 1st tau 
      // and any mode for the 2nd tau
      //
      Tauolapp::jaki_.jak1 = 2;
      Tauolapp::jaki_.jak2 = 0;
      Tauolapp::Tauola::setSameParticleDecayMode( 2 ) ;
      Tauolapp::Tauola::setOppositeParticleDecayMode( 0 ) ;
      return;
   }
   
   if ( mdtau == 121 || mdtau == 221 )
   {
      // override with any mode for the 1st tau 
      // and electron mode for the 2nd tau
      //
      Tauolapp::jaki_.jak1 = 0;
      Tauolapp::jaki_.jak2 = 1;
      Tauolapp::Tauola::setSameParticleDecayMode( 0 ) ;
      Tauolapp::Tauola::setOppositeParticleDecayMode( 1 ) ;
      return;
   }
   
   if ( mdtau == 122 || mdtau == 222 )
   {
      // override with any mode for the 1st tau 
      // and muon mode for the 2nd tau
      //
      Tauolapp::jaki_.jak1 = 0;
      Tauolapp::jaki_.jak2 = 2;
      Tauolapp::Tauola::setSameParticleDecayMode( 0 ) ;
      Tauolapp::Tauola::setOppositeParticleDecayMode( 2 ) ;
      return;
   }

   if ( mdtau == 140 || mdtau == 240 )
   {
      // override with pi+/- nutau mode for both tau's 
      //
      Tauolapp::jaki_.jak1 = 3;
      Tauolapp::jaki_.jak2 = 3;
      Tauolapp::Tauola::setSameParticleDecayMode( 3 ) ;
      Tauolapp::Tauola::setOppositeParticleDecayMode( 3 ) ;
      return;
   }

   if ( mdtau == 141 || mdtau == 241 )
   {
      // override with pi+/- nutau mode for the 1st tau 
      // and any mode for the 2nd tau
      //
      Tauolapp::jaki_.jak1 = 3;
      Tauolapp::jaki_.jak2 = 0;
      Tauolapp::Tauola::setSameParticleDecayMode( 3 ) ;
      Tauolapp::Tauola::setOppositeParticleDecayMode( 0 ) ;
      return;
   }

   if ( mdtau == 142 || mdtau == 242 )
   {
      // override with any mode for the 1st tau 
      // and pi+/- nutau mode for 2nd tau
      //
      Tauolapp::jaki_.jak1 = 0;
      Tauolapp::jaki_.jak2 = 3;
      Tauolapp::Tauola::setSameParticleDecayMode( 0 ) ;
      Tauolapp::Tauola::setOppositeParticleDecayMode( 3 ) ;
      return;
   }
   
   // OK, we come here for semi-inclusive modes
   //
   
   // First of all, leptons and hadron modes sums
   //
   // re-scale branching ratios, just in case...
   //
   double sumBra = 0;
   
   // the number of decay modes is hardcoded at 22 because that's what it is right now in Tauola
   // in the future, perhaps an asscess method would be useful - communicate to Tauola team...
   //
   
   for ( int i=0; i<22; i++ )
   {
      sumBra += Tauolapp::taubra_.gamprt[i];
   }
   if ( sumBra == 0. ) return ; // perhaps need to throw ?
   for ( int i=0; i<22; i++ )
   {
      double newBra = Tauolapp::taubra_.gamprt[i] / sumBra;
      Tauolapp::Tauola::setTauBr( i+1, newBra ); 
   }
   sumBra = 1.0;
   
   double sumLeptonBra = Tauolapp::taubra_.gamprt[0] + Tauolapp::taubra_.gamprt[1];
   double sumHadronBra = sumBra - sumLeptonBra;
   
   for ( int i=0; i<2; i++ )
   {
      fLeptonModes.push_back( i+1 );
      fScaledLeptonBrRatios.push_back( (Tauolapp::taubra_.gamprt[i]/sumLeptonBra) );  
   }
   for ( int i=2; i<22; i++ )
   {
      fHadronModes.push_back( i+1 );
      fScaledHadronBrRatios.push_back( (Tauolapp::taubra_.gamprt[i]/sumHadronBra) ); 
   }

   fSelectDecayByEvent = true;
   return;
      
}

void TauolappInterface::selectDecayByMDTAU()
{

   
   if ( fMDTAU == 100 || fMDTAU == 200 )
   {
      int mode = selectLeptonic();
      Tauolapp::jaki_.jak1 = mode;
      Tauolapp::Tauola::setSameParticleDecayMode( mode );
      mode = selectLeptonic();
      Tauolapp::jaki_.jak2 = mode;
      Tauolapp::Tauola::setOppositeParticleDecayMode( mode );
      return ;
   }
   
   int modeL = selectLeptonic();
   int modeH = selectHadronic();
   
   if ( fMDTAU == 110 || fMDTAU == 210 )
   {
      Tauolapp::jaki_.jak1 = modeL;
      Tauolapp::jaki_.jak2 = 0;
      Tauolapp::Tauola::setSameParticleDecayMode( modeL );
      Tauolapp::Tauola::setOppositeParticleDecayMode( 0 );
      return ;
   }
   
   if ( fMDTAU == 120 || fMDTAU == 22 )
   {
      Tauolapp::jaki_.jak1 = 0;
      Tauolapp::jaki_.jak2 = modeL;
      Tauolapp::Tauola::setSameParticleDecayMode( 0 );
      Tauolapp::Tauola::setOppositeParticleDecayMode( modeL );
      return;      
   }
   
   if ( fMDTAU == 114 || fMDTAU == 214 )
   {
      Tauolapp::jaki_.jak1 = modeL;
      Tauolapp::jaki_.jak2 = modeH;
      Tauolapp::Tauola::setSameParticleDecayMode( modeL );
      Tauolapp::Tauola::setOppositeParticleDecayMode( modeH );
      return;      
   }

   if ( fMDTAU == 124 || fMDTAU == 224 )
   {
      Tauolapp::jaki_.jak1 = modeH;
      Tauolapp::jaki_.jak2 = modeL;
      Tauolapp::Tauola::setSameParticleDecayMode( modeH );
      Tauolapp::Tauola::setOppositeParticleDecayMode( modeL );
      return;      
   }

   if ( fMDTAU == 115 || fMDTAU == 215 )
   {
      Tauolapp::jaki_.jak1 = 1;
      Tauolapp::jaki_.jak2 = modeH;
      Tauolapp::Tauola::setSameParticleDecayMode( 1 );
      Tauolapp::Tauola::setOppositeParticleDecayMode( modeH );
      return;      
   }

   if ( fMDTAU == 125 || fMDTAU == 225 )
   {
      Tauolapp::jaki_.jak1 = modeH;
      Tauolapp::jaki_.jak2 = 1;
      Tauolapp::Tauola::setSameParticleDecayMode( modeH );
      Tauolapp::Tauola::setOppositeParticleDecayMode( 1 );
      return;      
   }

   if ( fMDTAU == 116 || fMDTAU == 216 )
   {
      Tauolapp::jaki_.jak1 = 2;
      Tauolapp::jaki_.jak2 = modeH;
      Tauolapp::Tauola::setSameParticleDecayMode( 2 );
      Tauolapp::Tauola::setOppositeParticleDecayMode( modeH );
      return;      
   }

   if ( fMDTAU == 126 || fMDTAU == 226 )
   {
      Tauolapp::jaki_.jak1 = modeH;
      Tauolapp::jaki_.jak2 = 2;
      Tauolapp::Tauola::setSameParticleDecayMode( modeH );
      Tauolapp::Tauola::setOppositeParticleDecayMode( 2 );
      return;      
   }

   if ( fMDTAU == 130 || fMDTAU == 230 )
   {
      Tauolapp::jaki_.jak1 = modeH;
      Tauolapp::jaki_.jak2 = selectHadronic();
      Tauolapp::Tauola::setSameParticleDecayMode( modeH );
      Tauolapp::Tauola::setOppositeParticleDecayMode( Tauolapp::jaki_.jak2 );
      return;      
   }

   if ( fMDTAU == 131 || fMDTAU == 231 )
   {
      Tauolapp::jaki_.jak1 = modeH;
      Tauolapp::jaki_.jak2 = 0;
      Tauolapp::Tauola::setSameParticleDecayMode( modeH );
      Tauolapp::Tauola::setOppositeParticleDecayMode( 0 );
      return;      
   }

   if ( fMDTAU == 132 || fMDTAU == 232 )
   {
      Tauolapp::jaki_.jak1 = 0;
      Tauolapp::jaki_.jak2 = modeH;
      Tauolapp::Tauola::setSameParticleDecayMode( 0 );
      Tauolapp::Tauola::setOppositeParticleDecayMode( modeH );
      return;      
   }
   
   // unlikely that we get here on unknown mdtau 
   // - there's a protection earlier
   // but if we do, just set defaults
   // probably need to spit a warning...
   //
   Tauolapp::Tauola::setSameParticleDecayMode( 0 );
   Tauolapp::Tauola::setOppositeParticleDecayMode( 0 );
      
   return;
   

}

int TauolappInterface::selectLeptonic()
{
   
   float prob = flat();
   
   if ( prob > 0. && prob <= fScaledLeptonBrRatios[0] ) 
   {
      return 1;
   }
   else if ( prob > fScaledLeptonBrRatios[1] && prob <=1. )
   {
      return 2;
   }
      
   return 0;
}

int TauolappInterface::selectHadronic()
{

   float prob = 0.;
   int len = 1;
   ranmar_(&prob,&len);
   
   double sumBra = fScaledHadronBrRatios[0];
   if ( prob > 0. && prob <= sumBra ) 
   {
      return fHadronModes[0];
   }
   else
   {
      int NN = fScaledHadronBrRatios.size();
      for ( int i=1; i<NN; i++ )
      {
         if ( prob > sumBra && prob <= (sumBra+fScaledHadronBrRatios[i]) ) 
	 {
	    return fHadronModes[i];
	 }
	 sumBra += fScaledHadronBrRatios[i];
      }
   }
   
   return 0;

}


