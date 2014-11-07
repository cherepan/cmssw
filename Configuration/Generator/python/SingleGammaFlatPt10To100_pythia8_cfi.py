import FWCore.ParameterSet.Config as cms
generator = cms.EDProducer("Pythia8PtGun",
                           PGunParameters = cms.PSet(
        MaxPt = cms.double(100.),
        MinPt = cms.double(10.),
        ParticleID = cms.vint32(22),
        AddAntiParticle = cms.bool(False),
        MaxEta = cms.double(2.5),
        MaxPhi = cms.double(3.14159265359),
        MinEta = cms.double(-2.5),
        MinPhi = cms.double(-3.14159265359) ## in radians
        ),
                           Verbosity = cms.untracked.int32(0), ## set to 1 (or greater)  for printouts
                           psethack = cms.string('single gamma pt 10 to 100'),
                           firstRun = cms.untracked.uint32(1),
                           PythiaParameters = cms.PSet(parameterSets = cms.vstring())
                           )
