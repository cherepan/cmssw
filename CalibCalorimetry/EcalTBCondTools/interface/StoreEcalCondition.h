#ifndef StoreEcalCondition_h
#define StoreEcalCondition_h
//#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "CondCore/DBCommon/interface/DBWriter.h"
#include "CondCore/DBCommon/interface/DBSession.h"
#include "CondCore/DBCommon/interface/Exception.h"
#include "CondCore/DBCommon/interface/ServiceLoader.h"
#include "CondCore/DBCommon/interface/ConnectMode.h"
#include "CondCore/DBCommon/interface/MessageLevel.h"
#include "CondCore/IOVService/interface/IOV.h"

#include "FWCore/Framework/interface/IOVSyncValue.h"

#include "CondCore/MetaDataService/interface/MetaData.h"

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <typeinfo>

#include "CondFormats/EcalObjects/interface/EcalWeightXtalGroups.h"
#include "CondFormats/EcalObjects/interface/EcalXtalGroupId.h"
#include "CondFormats/EcalObjects/interface/EcalTBWeights.h"
#include "CondFormats/EcalObjects/interface/EcalWeightSet.h"
#include "CondFormats/EcalObjects/interface/EcalWeight.h"
#include "CondFormats/EcalObjects/interface/EcalIntercalibConstants.h"
#include "CondFormats/EcalObjects/interface/EcalGainRatios.h"
#include "CondFormats/EcalObjects/interface/EcalMGPAGainRatio.h"
#include "CondFormats/EcalObjects/interface/EcalADCToGeVConstant.h"
#include "CondFormats/EcalObjects/interface/EcalPedestals.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"

namespace edm{
  class ParameterSet;
  class Event;
  class EventSetup;
}
using namespace std;

//
// class decleration
//

class  StoreEcalCondition : public edm::EDAnalyzer {
 public:

  EcalWeightXtalGroups* readEcalWeightXtalGroupsFromFile(const char *);
  EcalTBWeights* readEcalTBWeightsFromFile(const char *);
  EcalADCToGeVConstant* readEcalADCToGeVConstantFromFile(const char *);
  EcalIntercalibConstants* readEcalIntercalibConstantsFromFile(const char *);
  EcalGainRatios* readEcalGainRatiosFromFile(const char *);
  void readSMRunFile() ;
  void writeToLogFile(string , string) ;
  void writeToLogFileResults(char* ) ;

  explicit  StoreEcalCondition(const edm::ParameterSet& iConfig );
  ~StoreEcalCondition();

  virtual void analyze( const edm::Event& evt, const edm::EventSetup& evtSetup);
  virtual void endJob();

 private:
  std::vector< std::string > objectName_ ;
  // it can be of type: EcalWeightXtalGroups, EcalTBWeights, EcalADCToGeVConstant, EcalIntercalibConstants, EcalGainRatios

  std::vector< std::string > inpFileName_ ;
  std::string prog_name_ ;

  int sm_constr_;
  unsigned long firstrun_;
  unsigned long lastrun_;

  std::vector< bool > appendCondition_; // by default append to exisiting tag

  std::string to_string( char value[]) {
    std::ostringstream streamOut;
    streamOut << value;
    return streamOut.str();
  }

};
#endif
