// MpddstSelector.C
#define MpddstSelector_cxx

#include "MpddstSelector.h"
#include <TH1.h>
#include <TStyle.h>

void MpddstSelector::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void MpddstSelector::SlaveBegin(TTree * /*tree*/)
{
    TString option = GetOption();

    //pt:
	pt_pions =  new TH1F("pt_pions", "pions::p_{T}", 300, 0., 7.) ;
	pt_antipions =  new TH1F("pt_antipions", "antipions::p_{T}", 300, 0., 7.) ;
	pt_kaons =  new TH1F("pt_kaons", "kaons::p_{T}", 300, 0., 7.) ;
	pt_antikaons =  new TH1F("pt_antikaons", "antikaons::p_{T}", 300, 0., 7.) ;
	pt_protons =  new TH1F("pt_protons", "protons::p_{T}", 300, 0., 7.) ;
	pt_antiprotons =  new TH1F("pt_antiprotons", "antiprotons::p_{T}", 300, 0., 7.) ;
	
	//pseudorapidity
	eta_pions =  new TH1F("eta_pions", "pions::pseudorapidity", 300, -2.5, 2.5) ;
	eta_antipions =  new TH1F("eta_antipions", "antipions::pseudorapidity", 300, -2.5, 2.5) ;
	eta_kaons =  new TH1F("eta_kaons", "kaons::pseudorapidity", 300, -2.5, 2.5) ;
	eta_antikaons =  new TH1F("eta_antikaons", "antikaons::pseudorapidity", 300, -2.5, 2.5) ;
	eta_protons =  new TH1F("eta_protons", "protons::pseudorapidity", 300, -2.5, 2.5) ;
	eta_antiprotons =  new TH1F("eta_antiprotons", "antiprotons::pseudorapidity", 300, -2.5, 2.5) ;

	//theta
	theta_pions =  new TH1F("theta_pions", "pions::theta", 300, 0., 3.) ;
	theta_antipions =  new TH1F("theta_antipions", "antipions::theta", 300, 0., 3.) ;
	theta_kaons =  new TH1F("theta_kaons", "kaons::theta", 300, 0., 3.) ;
	theta_antikaons =  new TH1F("theta_antikaons", "antikaons::theta", 300, 0., 3.) ;
	theta_protons =  new TH1F("theta_protons", "protons::theta", 300, 0., 3.) ;
	theta_antiprotons =  new TH1F("theta_antiprotons", "antiprotons::theta", 300, 0., 3.) ;
	
	//theta pseudorapidity
	theta_eta_pions =  new TH2F("theta_eta_pions", "pions::theta_eta", 300, 0., 3.,300 , -3., 3.) ;
	theta_eta_antipions =  new TH2F("theta_eta_antipions", "antipions::theta_eta", 300, 0., 3.,300 , -3., 3.) ;
	theta_eta_kaons =  new TH2F("theta_eta_kaons", "kaons::theta_eta", 300, 0., 3.,300 , -3., 3.) ;
	theta_eta_antikaons =  new TH2F("theta_eta_antikaons", "antikaons::theta_eta", 300, 0., 3.,300 , -3., 3.) ;
	theta_eta_protons =  new TH2F("theta_eta_protons", "protons::theta_eta", 300, 0., 3., 300, -3., 3.) ;
	theta_eta_antiprotons =  new TH2F("theta_eta_antiprotons", "antiprotons::theta_eta", 300, 0., 3., 300, -3., 3.) ;
	
	//mult
	mult_pions =  new TH1I("mult_pions", "pions::mult",300, -0.5, 1000.5) ;
	mult_antipions =  new TH1I("mult_antipions", "antipions::mult",300, -0.5, 1000.5) ;
	mult_kaons =  new TH1I("mult_kaons", "kaons::mult", 300, -0.5, 229.5) ;
	mult_antikaons =  new TH1I("mult_antikaons", "antikaons::mult", 300, -0.5, 229.5) ;
	mult_protons =  new TH1I("mult_protons", "protons::mult", 300, -0.5, 229.5) ;
	mult_antiprotons =  new TH1I("mult_antiprotons", "antiprotons::mult", 300, -0.5, 229.5) ;

    GetOutputList()->Add(pt_pions);
	GetOutputList()->Add(pt_antipions);
    GetOutputList()->Add(pt_kaons);
	GetOutputList()->Add(pt_antikaons);
    GetOutputList()->Add(pt_protons);
    GetOutputList()->Add(pt_antiprotons);

    GetOutputList()->Add(eta_pions);
    GetOutputList()->Add(eta_antipions);
    GetOutputList()->Add(eta_kaons);
    GetOutputList()->Add(eta_antikaons);
    GetOutputList()->Add(eta_protons);
    GetOutputList()->Add(eta_antiprotons);

    GetOutputList()->Add(theta_pions);
    GetOutputList()->Add(theta_antipions);
    GetOutputList()->Add(theta_kaons);
    GetOutputList()->Add(theta_antikaons);
    GetOutputList()->Add(theta_protons);
    GetOutputList()->Add(theta_antiprotons);

    GetOutputList()->Add(theta_eta_pions);
    GetOutputList()->Add(theta_eta_antipions);
    GetOutputList()->Add(theta_eta_kaons);
    GetOutputList()->Add(theta_eta_antikaons);
    GetOutputList()->Add(theta_eta_protons);
    GetOutputList()->Add(theta_eta_antiprotons);

    GetOutputList()->Add(mult_pions);
    GetOutputList()->Add(mult_antipions);
    GetOutputList()->Add(mult_kaons);
    GetOutputList()->Add(mult_antikaons);
    GetOutputList()->Add(mult_protons);
    GetOutputList()->Add(mult_antiprotons);
}

Bool_t MpddstSelector::Process(Long64_t entry){

    fReader.SetLocalEntry(entry);

    Int_t nPi=0, nAPi=0, nK=0, nAK=0, nPro=0, nAPro=0;

	for (Int_t iTrack = 0; iTrack < MPDEvent_->GetGlobalTracks()->GetEntriesFast(); iTrack++) {

    MpdTrack* track = (MpdTrack*) MPDEvent_->GetGlobalTracks()->UncheckedAt(iTrack);
    auto mctrack = (FairMCTrack*) MCTrack_->UncheckedAt(track->GetID());

	auto pdgID =  mctrack->GetPdgCode();

        if( pdgID == 211 )
	    {
			++nPi;
          	pt_pions->Fill( abs(track->GetPt()) );	// absolute value, becouse pT sign does not matter
          	
          	eta_pions->Fill(track->GetEta() );
          	
          	theta_pions->Fill( track->GetTheta() );
          	
          	theta_eta_pions->Fill(track->GetTheta(),track->GetEta());
		}		
		if( pdgID == -211 )
	    {
			++nAPi;
          	pt_antipions->Fill( abs(track->GetPt()) );	// absolute value, becouse pT sign does not matter
          	
          	eta_antipions->Fill(track->GetEta() );
          	
          	theta_antipions->Fill( track->GetTheta() );
          	
          	theta_eta_antipions->Fill(track->GetTheta(),track->GetEta());
		}				         	
	    if( pdgID == 321 )
	    {
				++nK;
                pt_kaons->Fill( abs(track->GetPt()) );
                
                eta_kaons->Fill( track->GetEta() );
                
                theta_kaons->Fill( track->GetTheta() );
                
                theta_eta_kaons->Fill(track->GetTheta(),track->GetEta());
		}		
		if( pdgID == -321 )
	    {
				++nAK;
                pt_antikaons->Fill( abs(track->GetPt()) );
                
                eta_antikaons->Fill( track->GetEta() );
                
                theta_antikaons->Fill( track->GetTheta() );
                
                theta_eta_antikaons->Fill(track->GetTheta(),track->GetEta());
		}         
	    if( pdgID == 2212 )
	    {
				++nPro;
				
                pt_protons->Fill( abs(track->GetPt()) );      
                
                eta_protons->Fill( track->GetEta());    
                
                theta_protons->Fill( track->GetTheta() );  
                
                theta_eta_protons->Fill(track->GetTheta(),track->GetEta());

		}
		if( pdgID == 2212 )
	    {
				++nAPro;
				
                pt_antiprotons->Fill( abs(track->GetPt()) );      
                
                eta_antiprotons->Fill( track->GetEta());    
                
                theta_antiprotons->Fill( track->GetTheta() );  
                
                theta_eta_antiprotons->Fill(track->GetTheta(),track->GetEta());

		}
	}
/* See mpddata/MpdTrack.h for more methods */
      
        mult_pions->Fill(nPi);
        mult_antipions->Fill(nAPi);
        mult_kaons->Fill(nK);
        mult_antikaons->Fill(nAK);
        mult_protons->Fill(nPro);
        mult_antiprotons->Fill(nAPro);

    return kTRUE;
}

void MpddstSelector::Terminate(){

    opfile->cd();

    pt_pions->Write();
	pt_kaons->Write();
	pt_protons->Write();
	pt_antipions->Write();
	pt_antikaons->Write();
	pt_antiprotons->Write();

	
	eta_pions->Write();
	eta_kaons->Write();
	eta_protons->Write();
	eta_antipions->Write();
	eta_antikaons->Write();
	eta_antiprotons->Write();

	
	theta_pions->Write();
	theta_kaons->Write();
	theta_protons->Write();
	theta_antipions->Write();
	theta_antikaons->Write();
	theta_antiprotons->Write();
	
	
	 mult_pions->Write();
     mult_kaons->Write();
     mult_protons->Write();
     mult_antipions->Write();
     mult_antikaons->Write();
     mult_antiprotons->Write();


	theta_eta_pions->Write();
	theta_eta_kaons->Write();
	theta_eta_protons->Write();
	theta_eta_antipions->Write();
	theta_eta_antikaons->Write();
	theta_eta_antiprotons->Write();
}