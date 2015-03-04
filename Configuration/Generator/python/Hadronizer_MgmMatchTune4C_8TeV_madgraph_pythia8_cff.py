import FWCore.ParameterSet.Config as cms

generator = cms.EDFilter("Pythia8HadronizerFilter",
                         maxEventsToPrint = cms.untracked.int32(1),
                         pythiaPylistVerbosity = cms.untracked.int32(1),
                         filterEfficiency = cms.untracked.double(1.0),
                         pythiaHepMCVerbosity = cms.untracked.bool(False),
                         comEnergy = cms.double(8000.),
                         ExternalDecays = cms.PSet(
        Tauolapp114 = cms.untracked.PSet(
            UseTauolaPolarization = cms.bool(True),
            InputCards = cms.PSet(
                pjak1 = cms.int32(0),
                pjak2 = cms.int32(0),
                mdtau = cms.int32(216)
                ),
            parameterSets = cms.vstring("setTauBr"),
            setTauBr = cms.PSet(
                # Update BR to PDG 2014 BR Ian M. Nugent 10/27/2014
                # GX is the \Gamma_{X} from the PDG labelling
                #(http://pdg8.lbl.gov/rpp2014v1/pdgLive/Particle.action?node=S035#decayclump_C)
                # Note: Total BR is 0.995575 not 1.0 due to missing modes - Tauola automatically
                #       rescales to 1.0.
                JAK = cms.vint32(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22),
                BR  = cms.vdouble(0.0,#0.1783,         # G3      JAKID 1 tau->enunu
                                  0.1741,         # G5      JAKID 2 tau->mununu
                                  0.0,
                                  0.0,
                                  0.1832,         # G20+G62 JAKID 5 tau->pipipinu/pipi0pi0nu
                                  0.0,
                                  0.0,
                                  0.0448,         # G71     JAKID 8 tau->3pipi0nu
                                  0.0105,         # G27     JAKID 9 tau->pi3pi0nu
                                  0.0,
                                  0.0,
                                  0.0,
                                  0.0,
                                  0.00144,        # G98     JAKID 14 tau->KpiKnu
                                  0.0,
                                  0.0,
                                  0.0,
                                  0.00294,        # G90     JAKID 18 tau->K2pinu
                                  0.0,
                                  0.0,
                                  0.0,
                                  0.0
                                  )
                )
            ),
        parameterSets = cms.vstring('Tauolapp114')
        ),
                         jetMatching = cms.untracked.PSet(
        scheme = cms.string("Madgraph"),
        mode = cms.string("auto"),# soup, or "inclusive" / "exclusive"
        MEMAIN_etaclmax = cms.double(-1),
        MEMAIN_qcut = cms.double(-1),
        MEMAIN_minjets = cms.int32(-1),
        MEMAIN_maxjets = cms.int32(-1),
        MEMAIN_showerkt = cms.double(0), # use 1=yes only for pt-ordered showers !
        MEMAIN_nqmatch = cms.int32(5),   #PID of the flavor until which the QCD radiation are kept in the matching procedure;
        # if nqmatch=4, then all showered partons from b's are NOT taken into account
        # Note (JY): I think the default should be 5 (b); anyway, don't try -1  as it'll result in a throw...
        MEMAIN_excres = cms.string(""),
        outTree_flag = cms.int32(0)      # 1=yes, write out the tree for future sanity check
        ),
                         PythiaParameters = cms.PSet(
        processParameters = cms.vstring(
	    'Main:timesAllowErrors    = 10000', 
            'ParticleDecays:limitTau0 = on',
	    'ParticleDecays:tauMax = 10',
            'Tune:ee 3',
            'Tune:pp 5'),
        parameterSets = cms.vstring('processParameters')
        )
                         )



tautaufilter = cms.EDFilter("MCParticlePairFilter",
                            Status = cms.untracked.vint32(2, 2),
                            MinPt = cms.untracked.vdouble(17.0, 15.0),
                            MaxEta = cms.untracked.vdouble(2.5, 2.5),
                            MinEta = cms.untracked.vdouble(-2.5, -2.5),
                            ParticleCharge = cms.untracked.int32(-1),
                            # MaxInvMass = cms.untracked.double(4.0),
                            # MinInvMass = cms.untracked.double(2.0),
                            ParticleID1 = cms.untracked.vint32(15),
                            ParticleID2 = cms.untracked.vint32(15)
                            )



MuFilter = cms.EDFilter("PythiaFilter",
    Status = cms.untracked.int32(1),
    MotherID = cms.untracked.int32(15),
    MinPt = cms.untracked.double(18.0),
    ParticleID = cms.untracked.int32(13),
    MaxEta = cms.untracked.double(2.3),
    MinEta = cms.untracked.double(-2.3)
)


ProductionFilterSequence = cms.Sequence(generator*MuFilter*tautaufilter)
#ProductionFilterSequence = cms.Sequence(generator*mufilter)
