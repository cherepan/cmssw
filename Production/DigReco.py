# Auto generated configuration file
# using: 
# Revision: 1.381.2.28 
# Source: /local/reps/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: step1 --filein dbs:/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/Summer12-START53_V7D-v2/GEN-SIM --fileout file:EWK-Summer12DR53X-00160_step1.root --pileup_input dbs:/MinBias_TuneZ2star_8TeV-pythia6/Summer12-START50_V13-v3/GEN-SIM --mc --eventcontent RAWSIM --runsScenarioForMC Run2012_AB_C_D_oneRunPerEra --pileup fromDB --datatier GEN-SIM-RAW --conditions START53_V7N::All --step DIGI,L1,DIGI2RAW,HLT:7E33v2 --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mix_fromDB_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_7E33v2_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring('/store/mc/Summer12/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/GEN-SIM/START53_V7D-v2/00000/0010E51A-41FD-E111-8ECB-0023AEFDE8DC.root', 
        '/store/mc/Summer12/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/GEN-SIM/START53_V7D-v2/00000/00149699-44FD-E111-A485-80000048FE80.root', 
        '/store/mc/Summer12/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/GEN-SIM/START53_V7D-v2/00000/00151FB5-94FD-E111-86F9-0023AEFDE5A0.root', 
        '/store/mc/Summer12/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/GEN-SIM/START53_V7D-v2/00000/003044C0-F6FF-E111-B407-B322ACCC0FEA.root', 
        '/store/mc/Summer12/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/GEN-SIM/START53_V7D-v2/00000/003E2058-36FD-E111-AE5D-60EB69BAC83A.root', 
        '/store/mc/Summer12/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/GEN-SIM/START53_V7D-v2/00000/004E3FDC-5AFD-E111-B38A-001E6878F906.root', 
        '/store/mc/Summer12/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/GEN-SIM/START53_V7D-v2/00000/0092CAC2-40FD-E111-A224-0002C94CD9D0.root', 
        '/store/mc/Summer12/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/GEN-SIM/START53_V7D-v2/00000/00E66CF1-34FD-E111-AA6C-0023AEFDE6C0.root', 
        '/store/mc/Summer12/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/GEN-SIM/START53_V7D-v2/00000/00FF9F2C-85FD-E111-9E6F-60EB69BACBBE.root', 
        '/store/mc/Summer12/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/GEN-SIM/START53_V7D-v2/00000/026BC316-3CFD-E111-9861-20CF3019DEF6.root'),
    setRunNumber = cms.untracked.uint32(200519)
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.381.2.28 $'),
    annotation = cms.untracked.string('step1 nevts:1'),
    name = cms.untracked.string('PyReleaseValidation')
)

# Output definition

process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    fileName = cms.untracked.string('file:JOBNAME_DigiReco.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM-RAW')
    )
)

# Additional output definition

#add random number utility to all MC gen-fragments for generation to ensure random seeds
from IOMC.RandomEngine.RandomServiceHelper import  RandomNumberServiceHelper
randHelper =  RandomNumberServiceHelper(process.RandomNumberGeneratorService)
randHelper.populate()


# Other statements
import SimGeneral.Configuration.ThrowAndSetRandomRun as ThrowAndSetRandomRun
ThrowAndSetRandomRun.throwAndSetRandomRun(process.source,[(194533, 5.2999999999999998), (200519, 7.0), (206859, 7.2999999999999998)])
process.mix.input.fileNames = cms.untracked.vstring(['/store/mc/Summer12/MinBias_TuneZ2star_8TeV-pythia6/GEN-SIM/START50_V13-v3/0000/0005E496-3661-E111-B31E-003048F0E426.root', '/store/mc/Summer12/MinBias_TuneZ2star_8TeV-pythia6/GEN-SIM/START50_V13-v3/0000/003EEBD4-8061-E111-9A23-003048D437F2.root', '/store/mc/Summer12/MinBias_TuneZ2star_8TeV-pythia6/GEN-SIM/START50_V13-v3/0000/005825F1-F260-E111-BD97-003048C692DA.root', '/store/mc/Summer12/MinBias_TuneZ2star_8TeV-pythia6/GEN-SIM/START50_V13-v3/0000/0065594C-B35E-E111-8B8C-003048C693EA.root', '/store/mc/Summer12/MinBias_TuneZ2star_8TeV-pythia6/GEN-SIM/START50_V13-v3/0000/0091FFD0-6B5E-E111-92FE-003048C693DA.root', '/store/mc/Summer12/MinBias_TuneZ2star_8TeV-pythia6/GEN-SIM/START50_V13-v3/0000/00C69AE3-FE60-E111-BC48-0030487D8633.root', '/store/mc/Summer12/MinBias_TuneZ2star_8TeV-pythia6/GEN-SIM/START50_V13-v3/0000/02079692-AC61-E111-97BB-0025901D4D54.root', '/store/mc/Summer12/MinBias_TuneZ2star_8TeV-pythia6/GEN-SIM/START50_V13-v3/0000/021BD915-2D61-E111-8BAD-002481E76052.root', '/store/mc/Summer12/MinBias_TuneZ2star_8TeV-pythia6/GEN-SIM/START50_V13-v3/0000/02386E4D-DC5E-E111-9413-00266CF1074C.root', '/store/mc/Summer12/MinBias_TuneZ2star_8TeV-pythia6/GEN-SIM/START50_V13-v3/0000/02446A08-515E-E111-82C7-00266CF330B8.root'])
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'START53_V7N::All', '')

# Path and EndPath definitions
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.endjob_step,process.RAWSIMoutput_step])

# customisation of the process.

# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC 

#call to customisation function customizeHLTforMC imported from HLTrigger.Configuration.customizeHLTforMC
process = customizeHLTforMC(process)

# End of customisation functions
