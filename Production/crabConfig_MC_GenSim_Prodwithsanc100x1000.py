from CRABClient.UserUtilities import config 
config = config()

config.General.requestName = 'DYtoTauTautomuhad_ProdwithSANCTest3'
config.General.workArea = 'crab_projects'
config.General.transferLogs=True

#config.JobType.pluginName = 'Analysis'
config.JobType.pluginName = 'PrivateMC'
config.JobType.psetName = 'Production/DYtoTauTautomuhad_cfi_GEN_SIM_VALIDATION.py'
config.JobType.generator = 'lhe'

config.Data.primaryDataset = 'DYtoTauTaumuhad_HadHelicityPlus_TauolappwithSanc'
#config.Data.inputDBS = 'global'
config.Data.splitting =  'EventBased'
config.Data.unitsPerJob = 1000
NJOBS = 100
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.outLFN = '/store/user/inugent/'
config.Data.userInputFiles = open('Production/Tauolapp_sanc.txt').readlines()
config.Data.publication = True
config.Data.publishDataName = 'DYtoTauTautomuhad_ProdwithSANCTest100x1000'
#config.Data.ignoreLocality = True
#config.JobType.outputFiles

config.User.voGroup = 'dcms'

config.Site.storageSite = 'T2_DE_RWTH'
config.Site.whitelist = ["T2_DE_RWTH"]
