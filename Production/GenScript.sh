#GEN-SIM commands
cmsDriver.py Configuration/GenProduction/python/EightTeV/Hadronizer_ZeeMgmMatchTuneZ2star_8TeV_madgraph_tauola_cff.py --filein "dbs:/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/Summer12-START50_V13-v1/GEN" --fileout file:EWK-Summer12GSEMShowerImproved-00001.root --mc --eventcontent RAWSIM --pileup NoPileUp --customise Configuration/GenProduction/QGSP_FTFP_BERT_EML95msc93_cff.customiseGeant4 --datatier GEN-SIM --conditions START53_V7D::All --beamspot Realistic8TeV2012Collision --step GEN,SIM,VALIDATION:genvalid_all --datamix NODATAMIXER --no_exec -n 1000

#Digi commands
cmsDriver.py step1 --filein "dbs:/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/Summer12-START53_V7D-v2/GEN-SIM" --fileout file:EWK-Summer12DR53X-00160_step1.root --pileup_input "dbs:/MinBias_TuneZ2star_8TeV-pythia6/Summer12-START50_V13-v3/GEN-SIM" --mc --eventcontent RAWSIM --runsScenarioForMC Run2012_AB_C_D_oneRunPerEra --pileup fromDB --datatier GEN-SIM-RAW --conditions START53_V7N::All --step DIGI,L1,DIGI2RAW,HLT:7E33v2

#AOD commands
cmsDriver.py step2 --filein file:EWK-Summer12DR53X-00160_step1.root --fileout file:EWK-Summer12DR53X-00160.root --mc --eventcontent AODSIM,DQM --datatier AODSIM,DQM --conditions START53_V7N::All --step RAW2DIGI,L1Reco,RECO,VALIDATION:validation_prod,DQM:DQMOfflinePOGMC


