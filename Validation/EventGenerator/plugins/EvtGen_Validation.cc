#include "Validation/EventGenerator/interface/EvtGen_Validation.h"
#include "DQMServices/Core/interface/DQMStore.h"
#include "Validation/EventGenerator/interface/PdtPdgMini.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"


using namespace edm;
EvtGen_Validation::EvtGen_Validation(const edm::ParameterSet& iConfig) :
  hepmcCollection_(iConfig.getParameter<edm::InputTag>("hepmcCollection"))
{
  hepmcCollectionToken_=consumes<HepMCProduct>(hepmcCollection_);
}


EvtGen_Validation::~EvtGen_Validation(){}

// ------------ method called for each event  ------------
void EvtGen_Validation::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  ///Gathering the HepMCProduct information
  edm::Handle<HepMCProduct> evt;
  iEvent.getByToken(hepmcCollectionToken_, evt);

  //Get EVENT
  const HepMC::GenEvent *myGenEvent = evt->GetEvent();

  nEvt->Fill(0.5,1);
  for(HepMC::GenEvent::particle_const_iterator iter = myGenEvent->particles_begin(); iter != myGenEvent->particles_end(); iter++) {
    // Lambda_b polarization from Phys.Lett. B365 (1996) 437-447 
    // Do both full and transverse: - since transverse is the important one for LHC 
    if(abs((*iter)->pdg_id())==5122){
      Lambda_b_eta->Fill((*iter)->momentum().eta(),1);
      Lambda_b_Mass->Fill((*iter)->momentum().m(),1);
      Lambda_b_Pt->Fill((*iter)->momentum().perp(),1);
      std::vector<HepMC::GenParticle*> dau=FindLambdaLeptonDaughters(*iter);  
      if(dau.size()==nlep){
	Lambda_b_Y_l_nu->Fill(dau.at(l)->momentum().rho()/dau.at(nu)->momentum().rho(),1);
	Lambda_b_YT_l_nu->Fill(dau.at(l)->momentum().perp()/dau.at(nu)->momentum().perp(),1);
      }
    }    
  }
}


// ------------ method called once each job just before starting event loop  ------------
void EvtGen_Validation::bookHistograms(DQMStore::IBooker &i, edm::Run const &r, edm::EventSetup const &e){
  i.setCurrentFolder("Generator/EvtGen");

  nEvt = i.book1D("nEvt", "n analyzed Events", 1, 0., 1.);

  Lambda_b_Y_l_nu = i.book1D("Lambda_b_Y_l_nu","Y=<l>/<nu>=(7-P)/(6+2P) for Lambda_ b",25,-1.0,1.0);  
  Lambda_b_Y_l_nu->setAxisTitle("Y=<l>/<nu>");

  Lambda_b_YT_l_nu = i.book1D("Lambda_b_YT_l_nu","Transverse Y=<l>/<nu>=(7-P)/(6+2P) for Lambda_ b",25,-1.0,1.0);  
  Lambda_b_YT_l_nu->setAxisTitle("YT=<lT>/<nuT>");
  
  Lambda_b_eta    = i.book1D("TTbar_TopY","Lambda_b #eta",200,-5.,5.);                
  Lambda_b_eta->setAxisTitle("Lambda_b #eta");
  
  Lambda_b_Mass   = i.book1D("TTbar_TopMass","Lambda_b Mass",500,0.,500.);                
  Lambda_b_Mass->setAxisTitle("Lambda_b M (GeV)");
  
  Lambda_b_Pt     = i.book1D("TTbar_TTbarPt","Lambda_b P_{t}",100,0.,100.); 
  Lambda_b_Pt->setAxisTitle("Lambda_b P_{t} (GeV)");

}

std::vector<HepMC::GenParticle*> EvtGen_Validation::FindLambdaLeptonDaughters(HepMC::GenParticle* lambda_b){
  bool has_l(false), has_nu(false);
  std::vector<HepMC::GenParticle*> leptons(nlep,NULL);
    if (lambda_b->end_vertex()){
      for (HepMC::GenVertex::particle_iterator  dau = lambda_b->end_vertex()->particles_begin(HepMC::children); dau!= lambda_b->end_vertex()->particles_end(HepMC::children); dau++ ) {
	int dau_pid = abs((*dau)->pdg_id());
	if((dau_pid==PdtPdgMini::e_minus && dau_pid==PdtPdgMini::mu_minus && dau_pid==PdtPdgMini::tau_minus) || !has_l){
	  has_l=true;
	  leptons.at(l)(*dau);
	}
        if((dau_pid==PdtPdgMini::nu_e && dau_pid==PdtPdgMini::nu_mu && dau_pid==PdtPdgMini::nu_tau) || !has_nu){
          has_l=true;
          leptons.at(nu)(*dau);
        }

nu_e
      }
    }
    return true;
  }
  
}
