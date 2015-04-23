from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'DQM_DYtoTauTautomuhad_ProdwithSANC'
config.General.workArea = 'crab_projects'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'HARVESTING.py'

config.Data.inputDataset = '/GenericTTbar/HC-CMSSW_5_3_1_START53_V5-v1/GEN-SIM-RECO'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1000
config.Data.outLFN = '/store/user/inugent/'
config.Data.publication = True
config.Data.publishDataName = 'DQM_DYtoTauTautomuhad_ProdwithSANC'

config.User.voGroup = 'dcms'

config.Site.storageSite = 'T2_DE_RWTH'
config.Site.whitelist = ["T2_DE_RWTH"]
