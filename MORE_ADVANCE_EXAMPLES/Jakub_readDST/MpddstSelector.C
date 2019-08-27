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

    hpt = new TH1D("hpt",";#it{p}_T (GeV/#it{c});dN/dp_{T}",200,0.0,2.0);
    hptpion = new TH1D("hptpi","#it{p}_{T} of #pi;#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T}",200,0.0,2.0);
    hptproton = new TH1D("hptp","#it{p}_{T} of p;#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T}",200,0.0,2.0);
    tpcdedxvsp = new TH2D("tpcdedxvsp","TPC signal vs #it{p}_{T};p (GeV/#it{c});dE/dx",200,0.0,2.0,500,5e2,2e4);
    tpcdedxvsppion = new TH2D("tpcdedxvsppion","TPC signal vs #it{p}_{T} for #pi;#it{p}_{T} (GeV/#it{c});dE/dx",200,0.0,2.0,500,5e2,2e4);
    tpcdedxvspproton = new TH2D("tpcdedxvspproton","TPC signal vs #it{p}_{T} for p; #it{p}_{T} (GeV/#it{c});dE/dx",200,0.0,2.0,500,5e2,2e4);
    hptvsnsigp = new TH2D("hptvsnsigp",";p (G  eV/c);N_{#sigma}^{#pi}",200,0.0,2.0,40,0.0,1.00);

    hptmc = new TH1D("hptmc",";#it{p}_{T} (GeV/c);dN/dp_{T}",200,0.0,2.0);
    hptpionmc = new TH1D("hptpimc","#it{p}_{T} of #pi;p_{T} (GeV/#it{c});dN/dp_{T}",200,0.0,2.0);
    hptprotonflag = new TH1D("hptpflag","1: is MC 2: in not MC",2,0.0,2.0);
    hMCpRECO = new TH1D("hMCpRECO","p MC_{RECO};#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T} (reco, MC)",200,0.0,2.0);
    hMCpTRUTH = new TH1D("hMCpTRUTH","p MC_{TRUTH};#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T}",200,0.0,2.0);
    hMCpiRECO = new TH1D("hMCpiRECO","#pi MC_{RECO};#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T} (reco, MC)",200,0.0,2.0);
    hMCpiTRUTH = new TH1D("hMCpiTRUTH","#pi MC_{TRUTH};#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T}",200,0.0,2.0);

    htofmass = new TH2D("htofmass", "TOF mass;#it{p}_{T} (GeV/c];m (GeV/c^{2}); dN/d#it{m^{2}}", 200, 0.0, 2.0, 200, 0.0, 2.0);
    htofmassp = new TH2D("htofmassp", "TOF mass for p;#it{p}_{T} (GeV/c);m (GeV/c^{2}); dN/d#it{m^{2}}", 200, 0.0, 2.0, 200, 0.0, 2.0);

    hpxrespion = new TH1D("hpxrespi","#pi;#it{p}_{x}^{rec}-#it{p}_{x}^{MC} (GeV/#it{c});dN/d#it{p}_{diff}",200,-0.5,0.5);
    hpxresproton = new TH1D("hpxresp","p;#it{p}_{x}^{rec}-#it{p}_{x}^{MC} (GeV/#it{c});dN/d#it{p}_{diff}",200,-0.5,0.5);

    hetap = new TH1D("hetap", ";#eta; dN/d#eta", 200, -2, 2);
    hrapidity = new TH1D("heta", ";#eta; dN/d#eta", 200, -2, 2);

    hpt->Sumw2();
    hptproton->Sumw2();
    hptpion->Sumw2();
    hptmc->Sumw2();
    hptpionmc->Sumw2();
    hMCpRECO->Sumw2();
    hMCpTRUTH->Sumw2();

    GetOutputList()->Add(hpt);
    GetOutputList()->Add(hptpion);
    GetOutputList()->Add(hptproton);
    GetOutputList()->Add(tpcdedxvsp);
    GetOutputList()->Add(tpcdedxvsppion);
    GetOutputList()->Add(tpcdedxvspproton);
    GetOutputList()->Add(hptvsnsigp);

    GetOutputList()->Add(hptmc);
    GetOutputList()->Add(hptpionmc);
    GetOutputList()->Add(hptprotonflag);
    GetOutputList()->Add(hMCpRECO);
    GetOutputList()->Add(hMCpTRUTH);
    GetOutputList()->Add(hMCpiRECO);
    GetOutputList()->Add(hMCpiTRUTH);

    GetOutputList()->Add(htofmass);
    GetOutputList()->Add(htofmassp);
    
    GetOutputList()->Add(hpxrespion);
    GetOutputList()->Add(hpxresproton);

    GetOutputList()->Add(hetap);
    GetOutputList()->Add(hrapidity);
}

Bool_t MpddstSelector::Process(Long64_t entry){

    fReader.SetLocalEntry(entry);
    //cout << " Got entry " << entry << endl;

    Float_t pidpion, pidkaon, pidproton, pidelectron;

    mpdTracks = MPDEvent_->GetGlobalTracks();
    Int_t fNtracks = mpdTracks->GetEntriesFast();

        for (Int_t DSTtrackIndex = 0; DSTtrackIndex < fNtracks; DSTtrackIndex++){
            pDSTtrack = (MpdTrack*) mpdTracks->UncheckedAt(DSTtrackIndex);

            pidpion = pDSTtrack->GetTPCPidProbPion();
	        pidkaon = pDSTtrack->GetTPCPidProbKaon();
	        pidproton = pDSTtrack->GetTPCPidProbProton();
	        pidelectron = pDSTtrack->GetTPCPidProbElectron();
	  
	        hpt->Fill(pDSTtrack->GetPt());
	        tpcdedxvsp->Fill(TMath::Hypot(pDSTtrack->GetPz(), pDSTtrack->GetPt()), pDSTtrack->GetdEdXTPC());
	        hptvsnsigp->Fill(TMath::Hypot(pDSTtrack->GetPz(), pDSTtrack->GetPt()), pidpion);
	        htofmass->Fill(pDSTtrack->GetPt(), pDSTtrack->GetTofMass2());

	        //protons----------------------------->
	            if (pidproton > prob && pidproton > pidkaon && pidproton > pidpion && pDSTtrack->GetTofMass2()>tofMass) {
	                hetap->Fill(pDSTtrack->GetEta());
	                hptproton->Fill(pDSTtrack->GetPt());
	                tpcdedxvspproton->Fill(TMath::Hypot(pDSTtrack->GetPz(), pDSTtrack->GetPt()), pDSTtrack->GetdEdXTPC());
	                htofmassp->Fill(pDSTtrack->GetPt(), pDSTtrack->GetTofMass2());

	                mctrack = 0;
	                mctrack = (FairMCTrack *) MCTrack_->UncheckedAt(pDSTtrack->GetID());

	                if (mctrack) {
	                    TVector3 v1;
	                    mctrack->GetStartVertex(v1);
	                    if(mctrack->GetPdgCode() == 2212 && v1.Mag()<0.1){ // && TMath::Abs(mctrack->GetRapidity())<2 && v1.Perp()<0.06
		                    hptprotonflag->Fill(0.5);
	                    }else{
		                    hptprotonflag->Fill(1.5);
	                    }
	                    hMCpRECO->Fill(mctrack->GetPt());
	                    hpxresproton->Fill(pDSTtrack->GetPx()-mctrack->GetPx());
	                }

	            } //end of protons
	    /* See mpddata/MpdTrack.h for more methods */
	  
	        if (pidpion > 0.3) {
	            hptpion->Fill(pDSTtrack->GetPt());
	            tpcdedxvsppion->Fill(TMath::Hypot(pDSTtrack->GetPz(), pDSTtrack->GetPt()), pDSTtrack->GetdEdXTPC());

	            mctrack = 0;
	            mctrack = (FairMCTrack *) MCTrack_->UncheckedAt(pDSTtrack->GetID());

	        //	    cout<<mctrack;
	            if (mctrack) {
	                hMCpiRECO->Fill(pDSTtrack->GetPt());
	                hpxrespion->Fill(pDSTtrack->GetPx()-mctrack->GetPx());
	            }
            }//end of pions

        }  // track loop

        // MC tracks
        Int_t nmctracks = MCTrack_->GetEntriesFast();
        for (int tMCTrackIndex=0; tMCTrackIndex<nmctracks; tMCTrackIndex++) {
       	    mctrack = (FairMCTrack *) MCTrack_->UncheckedAt(tMCTrackIndex);
	        hptmc->Fill(mctrack->GetPt());

	        TVector3 v1;
	        mctrack->GetStartVertex(v1);
      	    if (mctrack->GetPdgCode() == 2212 && TMath::Abs(mctrack->GetRapidity())<1.3 && v1.Mag()<0.1 ){ 
	            //hptprotonmc->Fill(mctrack->GetPt());
	            hMCpTRUTH->Fill(mctrack->GetPt());
	            /* if(TMath::Abs(mctrack->GetRapidity())<1.5 && v1.Mag()<0.1 && mctrack->GetPt()>0.15){
	            hMCpTRUTH->Fill(mctrack->GetPt());
	            hrapidity->Fill(mctrack->GetRapidity());
	            }*/
       	    }
	
	        if (mctrack->GetPdgCode() == 211){
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
    hptprotonflag->Write();
    hptpionmc->Write();
    hMCpRECO->Write();
    hMCpTRUTH->Write();
    hMCpiRECO->Write();
    hMCpiTRUTH->Write();

    hpxresproton->Write();
    hpxrespion->Write();

    htofmass->Write();
    htofmassp->Write();

    hetap->Write();
    hrapidity->Write();
}