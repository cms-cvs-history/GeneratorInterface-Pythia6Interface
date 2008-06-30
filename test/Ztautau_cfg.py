import FWCore.ParameterSet.Config as cms

process = cms.Process("Rec")
process.load("Configuration.StandardSequences.SimulationRandomNumberGeneratorSeeds_cff")

process.load("GeneratorInterface.Pythia6Interface.Ztautau_cff")

process.load("Configuration.EventContent.EventContent_cff")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5)
)
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.2 $'),
    name = cms.untracked.string('$Source: /cvs_server/repositories/CMSSW/CMSSW/GeneratorInterface/Pythia6Interface/test/Ztautau.cfg,v $'),
    annotation = cms.untracked.string('Z to tau tau')
)
process.GEN = cms.OutputModule("PoolOutputModule",
    process.FEVTSIMEventContent,
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN')
    ),
    fileName = cms.untracked.string('Ztautau.root')
)

process.outpath = cms.EndPath(process.GEN)
process.schedule = cms.Schedule(process.outpath)



