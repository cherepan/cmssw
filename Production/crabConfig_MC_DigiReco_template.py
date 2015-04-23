from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'GeneratorDQM_JOBNAME'
config.General.workArea = 'crab_projects'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'DigiReco.py'

config.Data.inputDataset = 'GENDATASET'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1000
config.Data.outLFN = '/store/user/inugent/'
config.Data.publication = True
config.Data.publishDataName = 'GeneratorDQM_JOBNAME'

config.User.voGroup = 'dcms'

config.Site.storageSite = 'T2_DE_RWTH'
config.Site.whitelist = ["T2_DE_RWTH"]
