import FWCore.ParameterSet.Config as cms

generator = cms.EDProducer("FlatRandomPtGunProducer",
                           PGunParameters = cms.PSet(
        MaxPt = cms.double(1000.01),
        MinPt = cms.double(999.99),
        PartID = cms.vint32(22),
        MaxEta = cms.double(2.5),
        MaxPhi = cms.double(3.14159265359),
        MinEta = cms.double(-2.5),
        MinPhi = cms.double(-3.14159265359) ## in radians
        ),
                           Verbosity = cms.untracked.int32(0), ## set to 1 (or greater)  for printouts
                           psethack = cms.string('single gamma pt 1000'),
                           AddAntiParticle = cms.bool(True),
                           firstRun = cms.untracked.uint32(1),
                           PythiaParameters = cms.PSet(parameterSets = cms.vstring())
                           )
