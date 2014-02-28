#include <iostream>
#include "GeneratorInterface/PhotosInterface/interface/PhotosppInterface.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "GeneratorInterface/PhotosInterface/interface/PhotosFactory.h"

#include "FWCore/ServiceRegistry/interface/Service.h"

#include "HepMC/GenEvent.h"
#include "HepMC/IO_HEPEVT.h"
#include "HepMC/HEPEVT_Wrapper.h"

using namespace gen;
using namespace edm;
using namespace std;

#include "Photos/Photos.h"
#include "Photos/PhotosHepMCEvent.h"

CLHEP::HepRandomEngine* PhotosppInterface::fRandomEngine = nullptr;

PhotosppInterface::PhotosppInterface( const edm::ParameterSet& pset)
  : fOnlyPDG(-1),
    fAvoidTauLeptonicDecays(false),
    fIsInitialized(false),
    fPSet(0)
{
   fSpecialSettings.push_back("QED-brem-off:all");
   fPSet = new ParameterSet(pset);
}

void PhotosppInterface::setRandomEngine(CLHEP::HepRandomEngine* decayRandomEngine){fRandomEngine=decayRandomEngine;}

void PhotosppInterface::configureOnlyFor( int ipdg ){
   fOnlyPDG = ipdg;
   fSpecialSettings.clear();
   return;
}

void PhotosppInterface::init(){
  if ( fIsInitialized ) return; // do init only once
  Photospp::Photos::initialize();

  std::vector<std::string> par = fPSet->getParameter< std::vector<std::string> >("parameterSets");
  for (unsigned int ip=0; ip<par.size(); ++ip ){
    std::string curSet = par[ip];
    edm::ParameterSet cfgAlgorithm = fPSet->getParameter<edm::ParameterSet>(curSet);   
    
    // Physics settings
    if(curSet=="maxWtInterference")                Photospp::Photos::maxWtInterference(cfgAlgorithm.getParameter<double>(curSet));
    if(curSet=="setInfraredCutOff")                Photospp::Photos::setInfraredCutOff(cfgAlgorithm.getParameter<double>(curSet));
    if(curSet=="setAlphaQED")                      Photospp::Photos::setAlphaQED(cfgAlgorithm.getParameter<double>(curSet));
    if(curSet=="setInterference")                  Photospp::Photos::setInterference(cfgAlgorithm.getParameter<bool>(curSet));
    if(curSet=="setDoubleBrem")                    Photospp::Photos::setDoubleBrem(cfgAlgorithm.getParameter<bool>(curSet));
    if(curSet=="setQuatroBrem")                    Photospp::Photos::setQuatroBrem(cfgAlgorithm.getParameter<bool>(curSet));
    if(curSet=="setExponentiation")                Photospp::Photos::setExponentiation(cfgAlgorithm.getParameter<bool>(curSet));
    if(curSet=="setCorrectionWtForW")              Photospp::Photos::setCorrectionWtForW(cfgAlgorithm.getParameter<bool>(curSet));
    if(curSet=="setMeCorrectionWtForScalar")       Photospp::Photos::setMeCorrectionWtForScalar(cfgAlgorithm.getParameter<bool>(curSet));
    if(curSet=="setMeCorrectionWtForW")            Photospp::Photos::setMeCorrectionWtForW(cfgAlgorithm.getParameter<bool>(curSet));
    if(curSet=="setMeCorrectionWtForZ")            Photospp::Photos::setMeCorrectionWtForZ(cfgAlgorithm.getParameter<bool>(curSet));
    if(curSet=="initializeKinematicCorrections")   Photospp::Photos::initializeKinematicCorrections(cfgAlgorithm.getParameter<int>(curSet));
    if(curSet=="forceMassFrom4Vector")             Photospp::Photos::forceMassFrom4Vector(cfgAlgorithm.getParameter<bool>(curSet));
    if(curSet=="forceMassFromEventRecord")         Photospp::Photos::forceMassFromEventRecord(cfgAlgorithm.getParameter<int>(curSet));
    if(curSet=="ignoreParticlesOfStatus")          Photospp::Photos::ignoreParticlesOfStatus(cfgAlgorithm.getParameter<int>(curSet));
    if(curSet=="deIgnoreParticlesOfStatus")        Photospp::Photos::deIgnoreParticlesOfStatus(cfgAlgorithm.getParameter<int>(curSet));
    if(curSet=="setMomentumConservationThreshold") Photospp::Photos::setMomentumConservationThreshold(cfgAlgorithm.getParameter<double>(curSet));
    if(curSet=="suppressAll") if(cfgAlgorithm.getParameter<bool>(curSet)==true)Photospp::Photos::suppressAll();
  
  // Now setup more complicated radiation/mass supression and forcing.
    if(curSet=="suppressBremForBranch"){
      std::vector<std::string> v = cfgAlgorithm.getParameter<std::vector<std::string> >(curSet);
      for(unsigned int i=0;i<v.size();i++){
	std::string vs = v[i];
	edm::ParameterSet cfg = cfgAlgorithm.getParameter<edm::ParameterSet>(vs);
	std::vector<int> vpar = cfg.getParameter<std::vector<int> >(vs);
	if(vpar.size()==1)  Photospp::Photos::suppressBremForBranch(0,vpar[0]);
	if(vpar.size()==2)  Photospp::Photos::suppressBremForBranch(0/*vpar[0]*/,vpar[1]);
	if(vpar.size()==3)  Photospp::Photos::suppressBremForBranch(vpar[0],vpar[1],vpar[2]);
	if(vpar.size()==4)  Photospp::Photos::suppressBremForBranch(vpar[0],vpar[1],vpar[2],vpar[3]);
	if(vpar.size()==5)  Photospp::Photos::suppressBremForBranch(vpar[0],vpar[1],vpar[2],vpar[3],vpar[4]);
	if(vpar.size()==6)  Photospp::Photos::suppressBremForBranch(vpar[0],vpar[1],vpar[2],vpar[3],vpar[4],vpar[5]);
	if(vpar.size()==7)  Photospp::Photos::suppressBremForBranch(vpar[0],vpar[1],vpar[2],vpar[3],vpar[4],vpar[5],vpar[6]);
	if(vpar.size()==8)  Photospp::Photos::suppressBremForBranch(vpar[0],vpar[1],vpar[2],vpar[3],vpar[4],vpar[5],vpar[6],vpar[7]);
	if(vpar.size()==9)  Photospp::Photos::suppressBremForBranch(vpar[0],vpar[1],vpar[2],vpar[3],vpar[4],vpar[5],vpar[6],vpar[7],vpar[8]);
	if(vpar.size()==10) Photospp::Photos::suppressBremForBranch(vpar[0],vpar[1],vpar[2],vpar[3],vpar[4],vpar[5],vpar[6],vpar[7],vpar[8],vpar[9]);
      }
    }
    if(curSet=="forceBremForDecay"){
      std::vector<std::string> v = cfgAlgorithm.getParameter<std::vector<std::string> >(curSet);
      for(unsigned int i=0;i<v.size();i++){
	std::string vs = v[i];
	edm::ParameterSet cfg = cfgAlgorithm.getParameter<edm::ParameterSet>(vs);
	std::vector<int> vpar = cfg.getParameter<std::vector<int> >(vs);
	if(vpar.size()==1)  Photospp::Photos::forceBremForDecay(0,vpar[0]);
	if(vpar.size()==2)  Photospp::Photos::forceBremForDecay(0/*vpar[0]*/,vpar[1]);
	if(vpar.size()==3)  Photospp::Photos::forceBremForDecay(vpar[0],vpar[1],vpar[2]);
	if(vpar.size()==4)  Photospp::Photos::forceBremForDecay(vpar[0],vpar[1],vpar[2],vpar[3]);
	if(vpar.size()==5)  Photospp::Photos::forceBremForDecay(vpar[0],vpar[1],vpar[2],vpar[3],vpar[4]);
	if(vpar.size()==6)  Photospp::Photos::forceBremForDecay(vpar[0],vpar[1],vpar[2],vpar[3],vpar[4],vpar[5]);
	if(vpar.size()==7)  Photospp::Photos::forceBremForDecay(vpar[0],vpar[1],vpar[2],vpar[3],vpar[4],vpar[5],vpar[6]);
	if(vpar.size()==8)  Photospp::Photos::forceBremForDecay(vpar[0],vpar[1],vpar[2],vpar[3],vpar[4],vpar[5],vpar[6],vpar[7]);
	if(vpar.size()==9)  Photospp::Photos::forceBremForDecay(vpar[0],vpar[1],vpar[2],vpar[3],vpar[4],vpar[5],vpar[6],vpar[7],vpar[8]);
	if(vpar.size()==10) Photospp::Photos::forceBremForDecay(vpar[0],vpar[1],vpar[2],vpar[3],vpar[4],vpar[5],vpar[6],vpar[7],vpar[8],vpar[9]);
      }
    }
    if(curSet=="forceMass"){
      std::vector<std::string> v = cfgAlgorithm.getParameter<std::vector<std::string> >(curSet);
      for(unsigned int i=0;i<v.size();i++){
	std::string vs = v[i];
	edm::ParameterSet cfg = cfgAlgorithm.getParameter<edm::ParameterSet>(vs);
	std::vector<double> vpar = cfg.getParameter<std::vector<double> >(vs);
	if(vpar.size()==2) Photospp::Photos::forceMass((int)vpar[0], vpar[1]);
      }
    }
  }
  // implement options set via c++ 
  if(fOnlyPDG>=0){
    Photospp::Photos::suppressAll();
    Photospp::Photos::forceBremForDecay(0,fOnlyPDG);
    Photospp::Photos::forceBremForDecay(0,-1*fOnlyPDG);
  }
  if(fAvoidTauLeptonicDecays){
    Photospp::Photos::suppressBremForDecay(3, 15, 16, 11, -12);
    Photospp::Photos::suppressBremForDecay(3, -15, -16, -11, 12);
    Photospp::Photos::suppressBremForDecay(3, 15, 16, 13, -14);
    Photospp::Photos::suppressBremForDecay(3, -15, -16, -13, -14);
  }
  fIsInitialized = true; 
  return;
}

HepMC::GenEvent* PhotosppInterface::apply( HepMC::GenEvent* evt){
  Photospp::Photos::setRandomGenerator(PhotosppInterface::flat);
  if ( !fIsInitialized ) return evt; // conv.read_next_event();
  Photospp::PhotosHepMCEvent PhotosEvt(evt);
  PhotosEvt.process();
  return evt;
}

double PhotosppInterface::flat(){
  if ( !fRandomEngine ) {
    throw cms::Exception("LogicError")
      << "PhotosppInterface::flat: Attempt to generate random number when engine pointer is null\n"
      << "This might mean that the code was modified to generate a random number outside the\n"
      << "event and beginLuminosityBlock methods, which is not allowed.\n";
  }
  return fRandomEngine->flat();
}

void PhotosppInterface::statistics(){Photospp::Photos::iniInfo();}

DEFINE_EDM_PLUGIN(PhotosFactory, gen::PhotosppInterface, "Photospp354");
