from CRABClient.UserUtilities import config 
config = config()

config.General.requestName = 'tutorial_MC_generation_test2'
config.General.workArea = 'crab_projects'

config.JobType.pluginName = 'PrivateMC'
config.JobType.psetName = 'pset_tutorial_MC_generation.py'
#config.JobType.outputFiles = ['']

config.Data.primaryDataset = 'MinBias'
config.Data.splitting = 'EventBased'
config.Data.unitsPerJob = 10
NJOBS = 10  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.outLFN = '/store/user/inugent/' # or '/store/group/<subdir>'
config.Data.publication = True
config.Data.publishDataName = 'inugent_CRAB3_tutorial_MC_generation_test1'

config.User.voGroup = 'dcms'

config.Site.storageSite = 'T2_DE_RWTH'
config.Site.whitelist = ["T2_DE_RWTH"]
