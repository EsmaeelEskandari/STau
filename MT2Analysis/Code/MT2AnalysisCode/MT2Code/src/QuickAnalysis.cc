#include "helper/Utilities.hh"
#include "QuickAnalysis.hh"

using namespace std;

QuickAnalysis::QuickAnalysis(TreeReader *tr) : UserAnalysisBase(tr){
	Util::SetStyle();	
}

QuickAnalysis::~QuickAnalysis(){
}

void QuickAnalysis::Begin(const char* filename){
	// Define the output file of histograms
	fHistFile = new TFile(fOutputDir + TString(filename), "RECREATE");
	
	// Define the histograms
	fHpileup = new TH1D("pileup", "in-time pileup distribution", 51, -0.5, 50.5);
}

void QuickAnalysis::Analyze(){
	// fill histo
	fHpileup->Fill(fTR->PUnumInteractions);
}

void QuickAnalysis::End(){
	fHistFile->cd();	
	fHpileup->Write();
	fHistFile->Close();
}
