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

    hpt = new TH1D("hpt",";#it{p}_T (GeV/#it{c});dN/dp_{T}",200,0.0,2.0);
    hptpion = new TH1D("hptpi","#it{p}_{T} of #pi;#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T}",200,0.0,2.0);
    hptkaon = new TH1D("hptka","#it{p}_{T} of K;#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T}",200,0.0,2.0 );
    hptelectron = new TH1D("hptelec","#it{p}_{T} of e;#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T}",200,0.0,2.0 );
    hptproton = new TH1D("hptprot","#it{p}_{T} of p;#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T}",200,0.0,2.0 );

    tpcdedxvsp = new TH2D("tpcdedxvsp",";p (GeV/c);dE/dx",200,0.0,2.0,500,5e2,2e4);
    tpcdedxvsppion = new TH2D("tpcdedxvsppion",";p (GeV/c);dE/dx",200,0.0,2.0,500,5e2,2e4);
    tpcdedxvspkaon = new TH2D("tpcdedxvspkaon",";p (GeV/c);dE/dx",200,0.0,2.0,500,5e2,2e4);
    tpcdedxvspelectron = new TH2D("tpcdedxvspelectron",";p (GeV/c);dE/dx",200,0.0,2.0,500,5e2,2e4);
    tpcdedxvspproton = new TH2D("tpcdedxvspproton",";p (GeV/c);dE/dx",200,0.0,2.0,500,5e2,2e4);
    hptvsnsigp = new TH2D("hptvsnsigp",";p (G  eV/c);N_{#sigma}^{#pi}",200,0.0,2.0,40,0.0,1.00);

    //Monte Carlo plots
    hptmc = new TH1D("hptmc",";#it{p}_T (GeV/#it{c});dN/dp_{T}",200,0.0,1.0);
    hptpionmc = new TH1D("hptpimc","#it{p}_{T} of #pi;#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T}",200,0.0,2.0);
    hptkaonmc = new TH1D("hptkamc","#it{p}_{T} of K;#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T}",200,0.0,2.0);
    hptelectronmc = new TH1D("hptelecmc","#it{p}_{T} of e;#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T}",200,0.0,1.0);
    hptprotonmc = new TH1D("hptprotmc","#it{p}_{T} of p;#it{p}_{T} (GeV/#it{c});dN/d#it{p}_{T}",200,0.0,1.0);

    hpxres = new TH1D("hpxres",";#it{p}_{x}^{rec}-#it{p}_{x}^{MC} (GeV/#it{c});dN/d#it{p}_{diff}",200,-0.5,0.5);

    hpt->Sumw2();
    hptpion->Sumw2();
    hptkaon->Sumw2();
    hptelectron->Sumw2();
    hptproton->Sumw2();

    hptmc->Sumw2();
    hptpionmc->Sumw2();
    hptkaonmc->Sumw2();
    hptelectronmc->Sumw2();
    hptprotonmc->Sumw2();

    hpxres->Sumw2();

    GetOutputList()->Add(hpt);
    GetOutputList()->Add(hptpion);
    GetOutputList()->Add(hptkaon);
    GetOutputList()->Add(hptelectron);
    GetOutputList()->Add(hptproton);

    GetOutputList()->Add(tpcdedxvsp);
    GetOutputList()->Add(tpcdedxvsppion);
    GetOutputList()->Add(tpcdedxvspkaon);
    GetOutputList()->Add(tpcdedxvspelectron);
    GetOutputList()->Add(tpcdedxvspproton);
    GetOutputList()->Add(hptvsnsigp);

    GetOutputList()->Add(hptmc);
    GetOutputList()->Add(hptpionmc);
    GetOutputList()->Add(hptkaonmc);
    GetOutputList()->Add(hptelectronmc);
    GetOutputList()->Add(hptprotonmc);

    GetOutputList()->Add(hpxres);
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
            pidelectron = pDSTtrack->GetTPCPidProbElectron();
            pidproton = pDSTtrack->GetTPCPidProbProton();

            hpt->Fill(pDSTtrack->GetPt());
            tpcdedxvsp->Fill(TMath::Hypot(pDSTtrack->GetPz(), pDSTtrack->GetPt()), pDSTtrack->GetdEdXTPC());
            hptvsnsigp->Fill(TMath::Hypot(pDSTtrack->GetPz(), pDSTtrack->GetPt()), pidpion);
            
            if (pidpion > 0.35)  {
	            hptpion->Fill(pDSTtrack->GetPt());
	            tpcdedxvsppion->Fill(TMath::Hypot(pDSTtrack->GetPz(), pDSTtrack->GetPt()), pDSTtrack->GetdEdXTPC());
	        }
            if(pidkaon > 0.35 && (pDSTtrack->GetTofMass2() < 0.7)) {
                hptkaon->Fill(pDSTtrack->GetPt());
                tpcdedxvspkaon->Fill(TMath::Hypot(pDSTtrack->GetPz(), pDSTtrack->GetPt()), pDSTtrack->GetdEdXTPC());
            }
            if(pidelectron > 0.35){
                hptelectron->Fill(pDSTtrack->GetPt());
                tpcdedxvspelectron->Fill(TMath::Hypot(pDSTtrack->GetPz(), pDSTtrack->GetPt()), pDSTtrack->GetdEdXTPC());
            }
            if (pidproton > 0.35 && (pDSTtrack->GetTofMass2() > 0.6 )){
                hptproton->Fill(pDSTtrack->GetPt());
                tpcdedxvspproton->Fill(TMath::Hypot(pDSTtrack->GetPz(), pDSTtrack->GetPt()), pDSTtrack->GetdEdXTPC());
            }
        }

    Int_t nmctracks = MCTrack_->GetEntriesFast();
    //cout << "Number of MC Tracks: " << nmctracks << endl;

        for (int tMCTrackIndex=0; tMCTrackIndex<nmctracks; tMCTrackIndex++) {
            mctrack = (FairMCTrack *) MCTrack_->UncheckedAt(tMCTrackIndex);

            hptmc->Fill(mctrack->GetPt());

            if(TMath::Abs(mctrack->GetPdgCode()) == 211){
                hptpionmc->Fill(mctrack->GetPt());
            }
            if (TMath::Abs(mctrack->GetPdgCode()) == 321){
                hptkaonmc->Fill(mctrack->GetPt());
            }
            if (mctrack->GetPdgCode() == -11){
                hptelectronmc->Fill(mctrack->GetPt());
            }
            if (TMath::Abs(mctrack->GetPdgCode()) == 2212){
                hptprotonmc->Fill(mctrack->GetPt());
            }
        }

    return kTRUE;
}

void MpddstSelector::Terminate(){

    opfile->cd();

    hpt->Write();
    hptpion->Write();
    hptkaon->Write();
    hptelectron->Write();
    hptproton->Write();

    tpcdedxvsp->Write();
    hptvsnsigp->Write();
    tpcdedxvsppion->Write();
    tpcdedxvspkaon->Write();
    tpcdedxvspelectron->Write();
    tpcdedxvspproton->Write();

    hptmc->Write();
    hptpionmc->Write();
    hptkaonmc->Write();
    hptelectronmc->Write();
    hptprotonmc->Write();



    hpxres->Write();
}