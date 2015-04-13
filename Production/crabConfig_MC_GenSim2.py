from WMCore.Configuration import Configuration
import os

config = Configuration()

## General options for the client
config.section_("General")
config.General.requestName   = 'test1'
config.General.transferLogs=True
#config.General.instance = 'preprod'

## Specific option of the job type
## these options are directly readable from the job type plugin
config.section_("JobType")
config.JobType.pluginName  = 'PrivateMC'
config.JobType.psetName = 'Production/DYtoTauTautomuhad_cfi_GEN_SIM_VALIDATION.py'

## Specific data options
config.section_("Data")
config.Data.primaryDataset = 'Minbias'
config.Data.inputDataset = ''
config.Data.splitting = 'EventBased'
config.Data.unitsPerJob = 1000
config.Data.totalUnits = 2

## User options
#config.section_("User")
#config.User.email = 'nugent@physik.rwth-aachen.de'

config.section_("Site")
config.Site.storageSite = 'T2_DE_RWTH'
config.Site.whitelist = ["T2_DE_RWTH"]
