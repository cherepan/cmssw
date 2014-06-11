//-------------------------------------------------
//
/** \class L1MuGMTLFMatchQualLUT
 *
 *   LFMatchQual look-up table
 *          
 *   this class was automatically generated by 
 *     L1MuGMTLUT::MakeSubClass()  
*/ 
//
//   Author :
//   H. Sakulin            HEPHY Vienna
//
//   Migrated to CMSSW:
//   I. Mikulec
//
//--------------------------------------------------
#ifndef L1TriggerGlobalMuonTrigger_L1MuGMTLFMatchQualLUT_h
#define L1TriggerGlobalMuonTrigger_L1MuGMTLFMatchQualLUT_h

//---------------
// C++ Headers --
//---------------


//----------------------
// Base Class Headers --
//----------------------
#include "L1Trigger/GlobalMuonTrigger/src/L1MuGMTLUT.h"

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------

//              ---------------------
//              -- Class Interface --
//              ---------------------


class L1MuGMTLFMatchQualLUT : public L1MuGMTLUT {
  
 public:
  enum {DTRPC, CSCRPC, DTCSC, CSCDT, CSCbRPC, DTfRPC};

  /// constuctor using function-lookup
  L1MuGMTLFMatchQualLUT() : L1MuGMTLUT("LFMatchQual", 
				       "DTRPC CSCRPC DTCSC CSCDT CSCbRPC DTfRPC",
				       "delta_eta(4) delta_phi(3)",
				       "mq(6)", 7, true) {
    InitParameters();
  } ;

  /// destructor
  virtual ~L1MuGMTLFMatchQualLUT() {};

  /// specific lookup function for mq
  unsigned SpecificLookup_mq (int idx, unsigned delta_eta, unsigned delta_phi) const {
    std::vector<unsigned> addr(2);
    addr[0] = delta_eta;
    addr[1] = delta_phi;
    return Lookup(idx, addr) [0];
  };

  /// specific lookup function for entire output field
  unsigned SpecificLookup (int idx, unsigned delta_eta, unsigned delta_phi) const {
    std::vector<unsigned> addr(2);
    addr[0] = delta_eta;
    addr[1] = delta_phi;
    return LookupPacked(idx, addr);
  };



  /// access to lookup function with packed input and output

  virtual unsigned LookupFunctionPacked (int idx, unsigned address) const {
    std::vector<unsigned> addr = u2vec(address, m_Inputs);
    return TheLookupFunction(idx ,addr[0] ,addr[1]);

  };

 private:
  /// Initialize scales, configuration parameters, alignment constants, ...
  void InitParameters();

  /// The lookup function - here the functionality of the LUT is implemented
  unsigned TheLookupFunction (int idx, unsigned delta_eta, unsigned delta_phi) const;

  /// Private data members (LUT parameters);
  float m_EtaWeights[6]; 
  float m_PhiWeights[6];
  float m_EtaPhiThresholds[6];
};
#endif



















