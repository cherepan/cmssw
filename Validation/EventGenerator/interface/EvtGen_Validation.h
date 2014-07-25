// -*- C++ -*-
//
// Package:   EvtGen_Validation 
// Class:     EvtGen_Validation
// 
//
// Original Author:  Ian Nugent
//         Created:  Fri July 25, 2014
//
#ifndef EvtGen_Validation_H
#define EvtGen_Validation_H

// system include files
#include <memory>
#include "DQMServices/Core/interface/DQMStore.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DQMServices/Core/interface/MonitorElement.h"
#include "DQMServices/Core/interface/DQMEDAnalyzer.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "TLorentzVector.h"

//
// class declaration
//

class EvtGen_Validation : public DQMEDAnalyzer {
   public:
  enum Lambda_leptons{l=0,nu,nlep};

      explicit EvtGen_Validation(const edm::ParameterSet&);
      ~EvtGen_Validation();

  virtual void bookHistograms(DQMStore::IBooker &i, edm::Run const &, edm::EventSetup const &) override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;


   private:
      // ----------member data ---------------------------
  
  edm::InputTag hepmcCollection_;
  std::vector<int> PDGID;
  
  MonitorElement* nEvt;
  
  MonitorElement* Pt;
  MonitorElement* eta;
  MonitorElement* Mass;
  MonitorElement* Y_l_nu; // polarization variable


};

#endif
