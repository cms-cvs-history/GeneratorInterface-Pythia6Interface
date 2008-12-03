import FWCore.ParameterSet.Config as cms

process = cms.Process('GEN')

process.load('Configuration/StandardSequences/Services_cff')
process.load('Configuration/StandardSequences/Generator_cff')


process.maxEvents = cms.untracked.PSet(
    input=cms.untracked.int32(10)
    )
 
from Configuration.Generator.PythiaUESettings_cfi import *
process.source = cms.Source("PythiaSource",
     pythiaPylistVerbosity = cms.untracked.int32(0),
     pythiaHepMCVerbosity = cms.untracked.bool(False),
     comEnergy = cms.untracked.double(10000.0),
     crossSection = cms.untracked.double(127206.0),
     maxEventsToPrint = cms.untracked.int32(0),
     PythiaParameters = cms.PSet(
         pythiaUESettingsBlock,
         processParameters = cms.vstring('MSEL=1          ! Quarkonia',
                                         'CKIN(3)=50.',
             'MSTP(142)=2      ! turns on the PYEVWT Pt re-weighting routine'),
         parameterSets = cms.vstring('pythiaUESettings', 
             'processParameters', 
             'CSAParameters'),
         CSAParameters = cms.vstring('CSAMODE = 7     ! cross-section reweighted quarkonia','PTPOWER = 5 ! pt^6')
     )
 )
 
