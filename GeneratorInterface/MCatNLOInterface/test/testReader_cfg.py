#!/usr/bin/env cmsRun
import FWCore.ParameterSet.Config as cms

process = cms.Process("LHE")

process.source = cms.Source("MCatNLOSource",
        #fileNames = cms.untracked.vstring('file:Z.events'),
        fileNames = cms.untracked.vstring('file:ttb_3_4_1.events'),
        #fileNames = cms.untracked.vstring('file:ttb_4_1_0.events'),
        #processCode = cms.int32(-11361) # Zevents IPROC
        processCode = cms.int32(-11706) # ttbar Events IPROC                       

)

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.LHE = cms.OutputModule("PoolOutputModule",
	dataset = cms.untracked.PSet(dataTier = cms.untracked.string('LHE')),
	fileName = cms.untracked.string('Zeventslhe.root')
)

process.outpath = cms.EndPath(process.LHE)
