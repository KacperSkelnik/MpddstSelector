// MpddstSelector.C
#define MpddstSelector_cxx

#include "MpddstSelector.h"
#include <TH1.h>
#include <TStyle.h>

void MpddstSelector::Begin(TTree * /*tree*/)
{
    TString option = GetOption();

    TString infile = "./urqmd34-11gev.list.txt";

    Int_t leng = infile.Length(), i1 = 0, i2 = 0;
    TString numb, prefix, suffix, symb, symb0;
    for (Int_t i = leng-1; i > -1; --i) {
    symb = TString(infile(i,1));
        if (symb == "_" || symb == "-") {
            prefix = infile(0,i+1);
            i1 = i + 1;
            break;
        } else if (symb == "g") {
            suffix = infile(i,leng-i);
            i2 = i - 1;
        }
    }
    numb = TString(infile(i1,i2-i1+1));
    opfile = new TFile(prefix+numb+Form("gev.ev%d.prob%d.tof-%d.root", events, (Int_t)(100*prob), (Int_t)(100*tofMass)), "RECREATE");
}

void MpddstSelector::SlaveBegin(TTree * /*tree*/)
{
    TString option = GetOption();

    Int_t pdgCodePr = 2212; //proton
    Int_t pdgCodePi = 211; //pi
    Int_t pdgCodeK = 321; //Kaon
  
    hpt = new TH1D("hpt",";#it{p}_T (GeV/#it{c});dN/dp_{T}",200,0.0,2.0);
    hptpion = new TH1D("hptpi","#it{p}_{T} of #pi;#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T}",200,0.0,2.0);
    hptproton = new TH1D("hptp","#it{p}_{T} of p;#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T}",200,0.0,2.0);
    tpcdedxvsp = new TH2D("tpcdedxvsp","TPC signal vs #it{p}_{T};p (GeV/#it{c});dE/dx",200,0.0,2.0,500,5e2,2e4);
    tpcdedxvsppion = new TH2D("tpcdedxvsppion","TPC signal vs #it{p} for #pi;#it{p} (GeV/#it{c});dE/dx",200,0.0,2.0,500,5e2,2e4);
    tpcdedxvspproton = new TH2D("tpcdedxvspproton","TPC signal vs #it{p} for p; #it{p} (GeV/#it{c});dE/dx",200,0.0,2.0,500,5e2,2e4);
    hptvsnsigp = new TH2D("hptvsnsigp",";p (G  eV/c);N_{#sigma}^{#pi}",200,0.0,2.0,40,0.0,1.00);

    tpcdedxvspprotonMC = new TH2D("tpcdedxvspprotonMC","TPC signal vs #it{p} for p; #it{p} (GeV/#it{c});dE/dx",200,0.0,2.0,500,5e2,2e4);

    hptmc = new TH1D("hptmc",";#it{p}_{T} (GeV/c);dN/dp_{T}",200,0.0,2.0);
    hptpionmc = new TH1D("hptpimc","#it{p}_{T} of #pi;p_{T} (GeV/#it{c});dN/dp_{T}",200,0.0,2.0);
    hptprotonmc = new TH1D("hptprotonmc","#it{p}_{T} of p;p_{T} (GeV/#it{c});dN/dp_{T}",200,0.0,2.0);
    hptprotonflag = new TH1D("hptpflag","1: is MC 2: in not MC",2,0.0,2.0);
    hMCpRECO = new TH1D("hMCpRECO","p MC_{RECO};#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T} (reco, MC)",200,0.0,2.0);
    hMCpTRUTH = new TH1D("hMCpTRUTH","p MC_{TRUTH};#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T}",200,0.0,2.0);
    hMCpiRECO = new TH1D("hMCpiRECO","#pi MC_{RECO};#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T} (reco, MC)",200,0.0,2.0);
    hMCpiTRUTH = new TH1D("hMCpiTRUTH","#pi MC_{TRUTH};#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T}",200,0.0,2.0);

    hProbProton = new TH2D("hProbProton", "Prob of protons; protons; pions", 100, 0.0, 1.0, 100, 0.0, 1.0);
    hProbProtonKaon = new TH2D("hProbProtonKaon", "Prob of protons; protons; kaons", 100, 0.0, 1.0, 100, 0.0, 1.0);
    hProbProtonElectron = new TH2D("hProbProtonElectron", "Prob of protons; protons; electrons", 100, 0.0, 1.0, 100, 0.0, 1.0);
    hProbPion = new TH2D("hPobPion", "Pob of pions; protons; pions", 100, 0.0, 1.0, 100, 0.0, 1.0);

    hPIDproton = new TH1D("hPIDproton", "PID of P_{RECO}", 5, 0.0, 5.0);
    hPIDpion = new TH1D("hPIDpion", "PID of #pi_{RECO}", 5, 0.0, 5.0);
  
    htofmass = new TH2D("htofmass", "TOF mass;#it{p}_{T} (GeV/c];m (GeV/c^{2}); dN/d#it{m^{2}}", 200, 0.0, 2.0, 200, 0.0, 2.0);
    htofmassp = new TH2D("htofmassp", "TOF mass for p;#it{p}_{T} (GeV/c);m (GeV/c^{2}); dN/d#it{m^{2}}", 200, 0.0, 2.0, 200, 0.0, 2.0);
    htofmasspMC = new TH2D("htofmasspMC", "TOF mass for p;#it{p}_{T} (GeV/c);m (GeV/c^{2}); dN/d#it{m^{2}}", 200, 0.0, 2.0, 200, 0.0, 2.0);

    hpxrespion = new TH1D("hpxrespi","#pi;#it{p}_{x}^{rec}-#it{p}_{x}^{MC} (GeV/#it{c});dN/d#it{p}_{diff}",200,-0.5,0.5);
    hpxresproton = new TH1D("hpxresp","p;#it{p}_{x}^{rec}-#it{p}_{x}^{MC} (GeV/#it{c});dN/d#it{p}_{diff}",200,-0.5,0.5);

    hetap = new TH1D("hetap", ";#eta; dN/d#eta", 200, -2, 2);
    hetapmc = new TH1D("hetapmc", ";#eta; dN/d#eta", 200, -2, 2);
    hrapidity = new TH1D("hrapidity", ";y;dN/dy", 200, -2.0, 2.0);
  
    hpt->Sumw2();
    hptproton->Sumw2();
    hptpion->Sumw2();
    hptmc->Sumw2();
    hptpionmc->Sumw2();
    hMCpRECO->Sumw2();
    hMCpTRUTH->Sumw2();

    GetOutputList()->Add(hpt);
    GetOutputList()->Add(hptproton);
    GetOutputList()->Add(hptpion);
    GetOutputList()->Add(tpcdedxvsp);
    GetOutputList()->Add(hptvsnsigp);
    GetOutputList()->Add(tpcdedxvsppion);
    GetOutputList()->Add(tpcdedxvspproton);
    GetOutputList()->Add(tpcdedxvspprotonMC);
    GetOutputList()->Add(hptprotonflag);
    GetOutputList()->Add(hProbProton);
    GetOutputList()->Add(hProbProtonKaon);
    GetOutputList()->Add(hProbProtonElectron);
    GetOutputList()->Add(hProbPion);
    GetOutputList()->Add(hPIDproton);
    GetOutputList()->Add(hPIDpion);

    GetOutputList()->Add(hptprotonmc);
    GetOutputList()->Add(hptpionmc);
    GetOutputList()->Add(hMCpRECO);
    GetOutputList()->Add(hMCpTRUTH);
    GetOutputList()->Add(hMCpiRECO);
    GetOutputList()->Add(hMCpiTRUTH);

    GetOutputList()->Add(hpxresproton);
    GetOutputList()->Add(hpxrespion);

    GetOutputList()->Add(htofmass);
    GetOutputList()->Add(htofmassp);
    GetOutputList()->Add(htofmasspMC);

    GetOutputList()->Add(hetap);
    GetOutputList()->Add(hetapmc);
    GetOutputList()->Add(hrapidity);
}

Bool_t MpddstSelector::Process(Long64_t entry){

    fReader.SetLocalEntry(entry);
    //cout << " Got entry " << entry << endl;

    Float_t pidpion, pidkaon, pidproton, pidelectron, pidTPCpion, pidTPCproton, pidTPCkaon, pidTPCelectron;
    pdgCodePr = 2212; //proton
    pdgCodePi = 211; //pi
    pdgCodeK = 321;

    mpdTracks = MPDEvent_->GetGlobalTracks();
    Int_t fNtracks = mpdTracks->GetEntriesFast();

    for (Int_t DSTtrackIndex = 0; DSTtrackIndex < fNtracks; DSTtrackIndex++){
        pDSTtrack = (MpdTrack*) mpdTracks->UncheckedAt(DSTtrackIndex);

        pidpion = pDSTtrack->GetPidProbPion();
        pidkaon = pDSTtrack->GetPidProbKaon();
        pidproton = pDSTtrack->GetPidProbProton();
        pidelectron = pDSTtrack->GetPidProbElectron();

        pidTPCpion = pDSTtrack->GetTPCPidProbPion();
        pidTPCkaon = pDSTtrack->GetTPCPidProbKaon();
        pidTPCproton = pDSTtrack->GetTPCPidProbProton();
        pidTPCelectron = pDSTtrack->GetTPCPidProbElectron();
	  
	    hpt->Fill(pDSTtrack->GetPt());
	    tpcdedxvsp->Fill(TMath::Hypot(pDSTtrack->GetPz(), pDSTtrack->GetPt()), pDSTtrack->GetdEdXTPC());
	    hptvsnsigp->Fill(TMath::Hypot(pDSTtrack->GetPz(), pDSTtrack->GetPt()), pidpion);
	    htofmass->Fill(pDSTtrack->GetPt(), pDSTtrack->GetTofMass2());
	    Double_t pMass = pDSTtrack->GetTofMass2();
	    Double_t pEta = pDSTtrack->GetEta();

	    //protons----------------------------->
	  
	    if ( pidproton > prob && pidproton > pidpion && pMass>tofMass && pMass<1.4) {
	        if(pDSTtrack->GetCharge() != 1) continue;
	    
	        hptproton->Fill(TMath::Abs(pDSTtrack->GetPt()));
	        htofmassp->Fill(TMath::Abs(pDSTtrack->GetPt()), pDSTtrack->GetTofMass2());
	      
	        hProbProton->Fill(pidproton, pidpion);
	        hProbProtonElectron->Fill(pidproton, pidelectron);
	        hProbProtonKaon->Fill(pidproton, pidkaon);
	    
	        tpcdedxvspproton->Fill(TMath::Hypot(pDSTtrack->GetPz(), pDSTtrack->GetPt()), pDSTtrack->GetdEdXTPC());
	        hetap->Fill(pDSTtrack->GetEta());

	        mctrack = 0;
	        mctrack = (FairMCTrack *) MCTrack_->UncheckedAt(pDSTtrack->GetID());

	        if (mctrack) {
	            //cout<<"Particle ["<<mctrack->GetPdgCode() <<"] charge ["<<pDSTtrack->GetCharge()<<"] pProb ["<<pidproton<<"]"<< "pT [" << pDSTtrack->GetPt()<<endl;
	            TVector3 v1;
	            mctrack->GetStartVertex(v1);
	      
	      
	        if(mctrack->GetPdgCode() == 2212 && v1.Mag()<0.3){ 
		        hptprotonflag->Fill(0.5);
	        }else{
		        hptprotonflag->Fill(1.5);
	        }

	            if(TMath::Abs(mctrack->GetPdgCode()) == pdgCodePr) hPIDproton->Fill(1);
	            else if(TMath::Abs(mctrack->GetPdgCode()) == pdgCodePi) hPIDproton->Fill(2);
	            else if(TMath::Abs(mctrack->GetPdgCode()) == pdgCodeK) hPIDproton->Fill(3);
	            else hPIDproton->Fill(4);

	            hetapmc->Fill(mctrack->GetRapidity());
	            hMCpRECO->Fill(mctrack->GetPt());
	            hpxresproton->Fill(pDSTtrack->GetPx()-mctrack->GetPx());
	        }
	    } //end of protons
	    /* See mpddata/MpdTrack.h for more methods */
	  
	    if (pDSTtrack->GetCharge() == -1 && pidTPCpion > 0.3 ) {
	        hptpion->Fill(pDSTtrack->GetPt());
	    
	        hProbPion->Fill(pidproton, pidpion);
	        tpcdedxvsppion->Fill(TMath::Hypot(pDSTtrack->GetPz(), pDSTtrack->GetPt()), pDSTtrack->GetdEdXTPC());
	      
	        mctrack = 0;
	        mctrack = (FairMCTrack *) MCTrack_->UncheckedAt(pDSTtrack->GetID());

	    if (mctrack) {
		
	      if(TMath::Abs(mctrack->GetPdgCode()) == pdgCodePr) hPIDpion->Fill(1);
	      else if(TMath::Abs(mctrack->GetPdgCode()) == pdgCodePi) hPIDpion->Fill(2);
	      else if(TMath::Abs(mctrack->GetPdgCode()) == pdgCodeK) hPIDpion->Fill(3);
	      else hPIDpion->Fill(4);
	      
	      hMCpiRECO->Fill(mctrack->GetPt());
	      hpxrespion->Fill(pDSTtrack->GetPx()-mctrack->GetPx());
	    }
	    }//end of pions

	    mctrack = 0;
	    mctrack = (FairMCTrack *) MCTrack_->UncheckedAt(pDSTtrack->GetID());
	  
	    if(mctrack){
	        TVector3 pos;
	        mctrack->GetStartVertex(pos);
	        if(mctrack->GetPdgCode() == pdgCodePr && pos.Mag() < 0.5  && mctrack->GetRapidity() < 1.3){
	            tpcdedxvspprotonMC->Fill(TMath::Hypot(pDSTtrack->GetPz(), pDSTtrack->GetPt()), pDSTtrack->GetdEdXTPC());
	            htofmasspMC->Fill(pDSTtrack->GetPt(), pDSTtrack->GetTofMass2());
	        }
	    }
	  //	  }// |eta|<1.0

    } // track loop

    // MC tracks
    Int_t nmctracks = MCTrack_->GetEntriesFast();
    for (int tMCTrackIndex=0; tMCTrackIndex<nmctracks; tMCTrackIndex++) {
        mctrack = (FairMCTrack *) MCTrack_->UncheckedAt(tMCTrackIndex);

	    hptmc->Fill(mctrack->GetPt());
	
	    TVector3 v1;
	    mctrack->GetStartVertex(v1);
	    if(TMath::Abs(mctrack->GetPdgCode()) == pdgCodePr && TMath::Abs(mctrack->GetRapidity())<1.0 && mctrack->GetPt()>0.1 && v1.Mag()<0.1){
	    hrapidity->Fill(mctrack->GetRapidity());
	    hptprotonmc->Fill(mctrack->GetPt());
	    hMCpTRUTH->Fill(mctrack->GetPt());
	    }

	    if(TMath::Abs(mctrack->GetPdgCode()) == pdgCodePi){
	        hptpionmc->Fill(mctrack->GetPt());
	        hMCpiTRUTH->Fill(mctrack->GetPt());
	    }	
	
    }

    return kTRUE;
}

void MpddstSelector::Terminate(){

    opfile->cd();

    hpt->Write();
    hptproton->Write();
    hptpion->Write();
    tpcdedxvsp->Write();
    hptvsnsigp->Write();
    tpcdedxvsppion->Write();
    tpcdedxvspproton->Write();
    tpcdedxvspprotonMC->Write();
    hptprotonflag->Write();
    hProbProton->Write();
    hProbProtonKaon->Write();
    hProbProtonElectron->Write();
    hProbPion->Write();
    hPIDproton->Write();
    hPIDpion->Write();

    hptprotonmc->Write();
    hptpionmc->Write();
    hMCpRECO->Write();
    hMCpTRUTH->Write();
    hMCpiRECO->Write();
    hMCpiTRUTH->Write();

    hpxresproton->Write();
    hpxrespion->Write();

    htofmass->Write();
    htofmassp->Write();
    htofmasspMC->Write();

    hetap->Write();
    hetapmc->Write();
    hrapidity->Write();

}