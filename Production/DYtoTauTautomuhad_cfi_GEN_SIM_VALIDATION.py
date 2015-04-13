# Auto generated configuration file
# using: 
# Revision: 1.381.2.28 
# Source: /local/reps/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: DYtoTauTautomuhad_cfi --filein dbs:/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/Summer12-START50_V13-v1/GEN --fileout file:EWK-Summer12GSEMShowerImproved-00001.root --mc --eventcontent RAWSIM --pileup NoPileUp --customise Configuration/GenProduction/QGSP_FTFP_BERT_EML95msc93_cff.customiseGeant4 --datatier GEN-SIM --conditions START53_V7D::All --beamspot Realistic8TeV2012Collision --step GEN,SIM,VALIDATION:genvalid_all --datamix NODATAMIXER --no_exec -n 10
import FWCore.ParameterSet.Config as cms

process = cms.Process('VALIDATION')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic8TeV2012Collision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Validation_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

# Input source
process.source = cms.Source("LHESource",
			    fileNames=cms.untracked.vstring(['/store/user/inugent/lhe5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_12497.lhe',
							     '/store/user/inugent/lhe5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_12498.lhe',
							     '/store/user/inugent/lhe5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_12499.lhe',
							     '/store/user/inugent/lhe5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_12500.lhe']))

#process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring('file:../../../LHE/00FE4EC4-8463-E111-A496-003048F11C58.root'))

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.381.2.28 $'),
    annotation = cms.untracked.string('DYtoTauTautomuhad_cfi nevts:10'),
    name = cms.untracked.string('PyReleaseValidation')
)

# Output definition

process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    fileName = cms.untracked.string('file:EWK-Summer12GSEMShowerImproved-00001.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Additional output definition

# Other statements
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
process.mix.playback = True
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'START53_V7D::All', '')

process.tautaufilter = cms.EDFilter("MCParticlePairFilter",
    Status = cms.untracked.vint32(2, 2),
    MinPt = cms.untracked.vdouble(17.0, 15.0),
    MaxEta = cms.untracked.vdouble(2.5, 2.5),
    MinEta = cms.untracked.vdouble(-2.5, -2.5),
    ParticleCharge = cms.untracked.int32(-1),
    ParticleID1 = cms.untracked.vint32(15),
    ParticleID2 = cms.untracked.vint32(15)
)


process.MuFilter = cms.EDFilter("PythiaFilter",
    Status = cms.untracked.int32(1),
    MotherID = cms.untracked.int32(15),
    MinPt = cms.untracked.double(18.0),
    ParticleID = cms.untracked.int32(13),
    MaxEta = cms.untracked.double(2.3),
    MinEta = cms.untracked.double(-2.3)
)


process.generator = cms.EDFilter("Pythia8HadronizerFilter",
    ExternalDecays = cms.PSet(
        parameterSets = cms.vstring('Tauolapp114'),
        Tauolapp114 = cms.untracked.PSet(
            UseTauolaPolarization = cms.bool(True),
            parameterSets = cms.vstring('setTauBr'),
            InputCards = cms.PSet(
                mdtau = cms.int32(216),
                pjak2 = cms.int32(0),
                pjak1 = cms.int32(0)
            ),
            setTauBr = cms.PSet(
                JAK = cms.vint32(1, 2, 3, 4, 5, 
                    6, 7, 8, 9, 10, 
                    11, 12, 13, 14, 15, 
                    16, 17, 18, 19, 20, 
                    21, 22),
                BR = cms.vdouble(0.0, 0.1741, 0.0, 0.0, 0.1832, 
                    0.0, 0.0, 0.0448, 0.0105, 0.0, 
                    0.0, 0.0, 0.0, 0.00144, 0.0, 
                    0.0, 0.0, 0.00294, 0.0, 0.0, 
                    0.0, 0.0)
            )
        )
    ),
    maxEventsToPrint = cms.untracked.int32(1),
    pythiaPylistVerbosity = cms.untracked.int32(1),
    filterEfficiency = cms.untracked.double(1.0),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    comEnergy = cms.double(8000.0),
    jetMatching = cms.untracked.PSet(
        MEMAIN_nqmatch = cms.int32(5),
        MEMAIN_showerkt = cms.double(0),
        MEMAIN_minjets = cms.int32(-1),
        MEMAIN_qcut = cms.double(-1),
        MEMAIN_excres = cms.string(''),
        MEMAIN_etaclmax = cms.double(-1),
        outTree_flag = cms.int32(0),
        scheme = cms.string('Madgraph'),
        MEMAIN_maxjets = cms.int32(-1),
        mode = cms.string('auto')
    ),
    PythiaParameters = cms.PSet(
        processParameters = cms.vstring('Main:timesAllowErrors    = 10000', 
            'ParticleDecays:limitTau0 = on', 
            'ParticleDecays:tauMax = 10', 
            'Tune:ee 3', 
            'Tune:pp 5'),
        parameterSets = cms.vstring('processParameters')
    )
)


process.ProductionFilterSequence = cms.Sequence(process.generator+process.MuFilter+process.tautaufilter)

#add random number utility
from IOMC.RandomEngine.RandomServiceHelper import  RandomNumberServiceHelper
randHelper =  RandomNumberServiceHelper(process.RandomNumberGeneratorService)
randHelper.populate()


# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.validation_step = cms.EndPath(process.genstepfilter+process.genvalid_all)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.validation_step,process.endjob_step,process.RAWSIMoutput_step)
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.ProductionFilterSequence * getattr(process,path)._seq 

# customisation of the process.

# Automatic addition of the customisation function from Configuration.GenProduction.QGSP_FTFP_BERT_EML95msc93_cff
from Configuration.GenProduction.QGSP_FTFP_BERT_EML95msc93_cff import customiseGeant4 

#call to customisation function customiseGeant4 imported from Configuration.GenProduction.QGSP_FTFP_BERT_EML95msc93_cff
process = customiseGeant4(process)

# End of customisation functions
