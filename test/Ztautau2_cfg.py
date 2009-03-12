import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

process.load("Configuration/Generator/PythiaUESettings_cfi")
# process.load("GeneratorInterface/Pythia6Interface/TauolaSettings_cff")
from GeneratorInterface.Pythia6Interface.TauolaSettings_cff import *

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5)
)
process.source = cms.Source("EmptySource")

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.1 $'),
    name = cms.untracked.string('$Source: /cvs_server/repositories/CMSSW/CMSSW/GeneratorInterface/Pythia6Interface/test/Ztautau2_cfg.py,v $'),
    annotation = cms.untracked.string('Z to tau tau')
)
process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
    pyth = cms.PSet(
        initialSeed = cms.untracked.uint32(123456789),
        engineName = cms.untracked.string('HepJamesRandom')
    )
)

process.pyth = cms.EDProducer("PythiaProducer",
    UseExternalGenerators = cms.untracked.bool(True),
    pythiaPylistVerbosity = cms.untracked.int32(1),
    ExternalGenerators = cms.PSet(
        Tauola = cms.untracked.PSet(
            TauolaPolar,
            TauolaDefaultInputForSource
        ),
        parameterSets = cms.vstring('Tauola')
    ),
    filterEfficiency = cms.untracked.double(1.0),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    pythiaFrame = cms.string('CMS'),
    comEnergy = cms.double(10000.0),
    maxEventsToPrint = cms.untracked.int32(5),
    PythiaParameters = cms.PSet(
        process.pythiaUESettingsBlock,
        processParameters = cms.vstring('MSEL         = 11 ', 
            'MDME( 174,1) = 0    !Z decay into d dbar', 
            'MDME( 175,1) = 0    !Z decay into u ubar', 
            'MDME( 176,1) = 0    !Z decay into s sbar', 
            'MDME( 177,1) = 0    !Z decay into c cbar', 
            'MDME( 178,1) = 0    !Z decay into b bbar', 
            'MDME( 179,1) = 0    !Z decay into t tbar', 
            'MDME( 182,1) = 0    !Z decay into e- e+', 
            'MDME( 183,1) = 0    !Z decay into nu_e nu_ebar', 
            'MDME( 184,1) = 0    !Z decay into mu- mu+', 
            'MDME( 185,1) = 0    !Z decay into nu_mu nu_mubar', 
            'MDME( 186,1) = 1    !Z decay into tau- tau+', 
            'MDME( 187,1) = 0    !Z decay into nu_tau nu_taubar', 
            'CKIN( 1)     = 40.  !(D=2. GeV)', 
            'CKIN( 2)     = -1.  !(D=-1. GeV)'),
        parameterSets = cms.vstring('pythiaUESettings', 
            'processParameters')
    )
)

process.GenInfoStorageLocal = cms.PSet(
    outputCommands = cms.untracked.vstring('drop *', 
        'keep *_pyth_*_*')
)
process.GEN = cms.OutputModule("PoolOutputModule",
    process.GenInfoStorageLocal,
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN')
    ),
    fileName = cms.untracked.string('Ztautau2.root')
)

process.p1 = cms.Path(process.pyth)
process.outpath = cms.EndPath(process.GEN)
process.schedule = cms.Schedule(process.p1,process.outpath)



