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

    pt_pions =  new TH1F("pt_pions", "pions::p_{T}", 300, 0., 7.) ;
	pt_kaons =  new TH1F("pt_kaons", "kaons::p_{T}", 300, 0., 7.) ;
	pt_protons =  new TH1F("pt_protons", "protons::p_{T}", 300, 0., 7.) ;
	pt_electrons =  new TH1F("pt_electrons", "electrons::p_{T}", 300, 0., 3.) ;

	//pseudorapidity
	eta_pions =  new TH1F("eta_pions", "pions::pseudorapidity", 300, -2.5, 2.5) ;
	eta_kaons =  new TH1F("eta_kaons", "kaons::pseudorapidity", 300, -2.5, 2.5) ;
	eta_protons =  new TH1F("eta_protons", "protons::pseudorapidity", 300, -2.5, 2.5) ;
	eta_electrons =  new TH1F("eta_electrons", "electrons::pseudorapidity", 300, -2.5, 2.5) ;

	//theta
	theta_pions =  new TH1F("theta_pions", "pions::theta", 300, 0., 3.) ;
	theta_kaons =  new TH1F("theta_kaons", "kaons::theta", 300, 0., 3.) ;
	theta_protons =  new TH1F("theta_protons", "protons::theta", 300, 0., 3.) ;
	theta_electrons =  new TH1F("theta_electrons", "electrons::theta", 300, 0., 3.) ;
	
	//theta pseudorapidity
	theta_eta_pions =  new TH2F("theta_eta_pions", "pions::theta_eta", 300, 0., 3.,300 , -3., 3.) ;
	theta_eta_kaons =  new TH2F("theta_eta_kaons", "kaons::theta_eta", 300, 0., 3.,300 , -3., 3.) ;
	theta_eta_protons =  new TH2F("theta_eta_protons", "protons::theta_eta", 300, 0., 3., 300, -3., 3.) ;
	theta_eta_electrons =  new TH2F("theta_eta_electrons", "electrons::theta_eta", 300, 0., 3.,300 , -3., 3.) ;

	//mult
	mult_pions =  new TH1I("tmult_pions", "pions::mult",300, -0.5, 1000.5) ;
	mult_kaons =  new TH1I("mult_kaons", "kaons::mult", 300, -0.5, 229.5) ;
	mult_protons =  new TH1I("mult_protons", "protons::mult", 300, -0.5, 229.5) ;
	mult_electrons =  new TH1I("mult_electrons", "electrons::mult", 300, -0.5, 50.5) ;

    GetOutputList()->Add(pt_pions);
    GetOutputList()->Add(pt_kaons);
    GetOutputList()->Add(pt_protons);
    GetOutputList()->Add(pt_electrons);

    GetOutputList()->Add(eta_pions);
    GetOutputList()->Add(eta_kaons);
    GetOutputList()->Add(eta_protons);
    GetOutputList()->Add(eta_electrons);

    GetOutputList()->Add(theta_pions);
    GetOutputList()->Add(theta_kaons);
    GetOutputList()->Add(theta_protons);
    GetOutputList()->Add(theta_electrons);

    GetOutputList()->Add(theta_eta_pions);
    GetOutputList()->Add(theta_eta_kaons);
    GetOutputList()->Add(theta_eta_protons);
    GetOutputList()->Add(theta_eta_electrons);

    GetOutputList()->Add(mult_pions);
    GetOutputList()->Add(mult_kaons);
    GetOutputList()->Add(mult_protons);
    GetOutputList()->Add(mult_electrons);
}

Bool_t MpddstSelector::Process(Long64_t entry){

    fReader.SetLocalEntry(entry);

    Int_t nPip=0, nK=0, nPro=0, nE=0;

        for (Int_t iTrack = 0; iTrack < MPDEvent_->GetGlobalTracks()->GetEntriesFast(); iTrack++) {
            MpdTrack* track = (MpdTrack*) MPDEvent_->GetGlobalTracks()->UncheckedAt(iTrack);
            auto mctrack = (FairMCTrack*) MCTrack_->UncheckedAt(track->GetID());	  

            auto pdgID =  mctrack->GetPdgCode();
	        if( abs(pdgID) == 211 ){
			    ++nPip;
          	    pt_pions->Fill( abs(track->GetPt()) );	// absolute value, becouse pT sign does not matter
          	
          	    eta_pions->Fill(track->GetEta() );
          	
          	    theta_pions->Fill( track->GetTheta() );
          	
          	    theta_eta_pions->Fill(track->GetTheta(),track->GetEta());
		    }
          	if( abs(pdgID) == 321 ){
				++nK;
                pt_kaons->Fill( abs(track->GetPt()) );
                
                eta_kaons->Fill( track->GetEta() );
                
                theta_kaons->Fill( track->GetTheta() );
                
                theta_eta_kaons->Fill(track->GetTheta(),track->GetEta());
		    }
            if( pdgID == 2212 ){
				++nPro;
				
                pt_protons->Fill( abs(track->GetPt()) );      
                
                eta_protons->Fill( track->GetEta());    
                
                theta_protons->Fill( track->GetTheta() );  
                
                theta_eta_protons->Fill(track->GetTheta(),track->GetEta());
            }
            if( pdgID == -2212){
			    ++nE;
			
			    pt_electrons->Fill( abs(track->GetPt()) );      
                
                eta_electrons->Fill( track->GetEta() );    
                
			    theta_electrons->Fill( track->GetTheta() );  
			
			    theta_eta_electrons->Fill(track->GetTheta(),track->GetEta());
            }
  
		}

    mult_pions->Fill(nPip);
    mult_kaons->Fill(nK);
    mult_protons->Fill(nPro);
    mult_electrons->Fill(nE);

    return kTRUE;
}

void MpddstSelector::Terminate(){

    opfile->cd();

    pt_pions->Write();
	pt_kaons->Write();
	pt_protons->Write();
	pt_electrons->Write();
	
	eta_pions->Write();
	eta_kaons->Write();
	eta_protons->Write();
	eta_electrons->Write();
	
	theta_pions->Write();
	theta_kaons->Write();
	theta_protons->Write();
	theta_electrons->Write();
	
    mult_pions->Write();
    mult_kaons->Write();
    mult_protons->Write();
    mult_electrons->Write();

	theta_eta_pions->Write();
	theta_eta_kaons->Write();
	theta_eta_protons->Write();
	theta_eta_electrons->Write();
}