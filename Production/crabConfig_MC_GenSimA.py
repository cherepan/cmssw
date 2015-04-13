from CRABClient.UserUtilities import config 
config = config()

config.General.requestName = 'DYtoTauTautomuhad_TestA'
config.General.workArea = 'crab_projects'
config.General.transferLogs=True

#config.JobType.pluginName = 'Analysis'
config.JobType.pluginName = 'PrivateMC'
config.JobType.psetName = 'Production/DYtoTauTautomuhad_cfi_GEN_SIM_VALIDATION.py'
config.JobType.generator = 'lhe'

config.Data.primaryDataset = 'DYtoTauTau'
#config.Data.inputDBS = 'global'
config.Data.splitting =  'EventBased'
config.Data.unitsPerJob = 1000
NJOBS = 5
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.outLFN = '/store/user/inugent/'
#config.Data.userInputFiles = open('Production/lhe5591.txt').readlines()
#process.source = cms.Source("LHESource",
#    fileNames = cms.untracked.vstring(['/store/user/inugent/lhe5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_12497.lhe',
#                                       '/store/user/inugent/lhe5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_12498.lhe',
#                                       '/store/user/inugent/lhe5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_12499.lhe',
#                                       '/store/user/inugent/lhe5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_12500.lhe'])
#                            )

config.Data.publication = True
config.Data.publishDataName = 'DYtoTauTautomuhad_TestA'
#config.Data.ignoreLocality = True

config.User.voGroup = 'dcms'

config.Site.storageSite = 'T2_DE_RWTH'
config.Site.whitelist = ["T2_DE_RWTH"]
