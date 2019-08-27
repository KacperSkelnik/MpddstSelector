// MpddstSelector.h
#ifndef MpddstSelector_h
#define MpddstSelector_h

R__ADD_INCLUDE_PATH($VMCWORKDIR)
#include "macro/mpd/mpdloadlibs.C"

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include "TH1.h"

// Headers needed by this particular selector
#include "TClonesArray.h"

class MpddstSelector : public TSelector{
    public:

    TTreeReader     fReader;
    TTree           *fChain = 0;

    TH1D *hpt;
    TH1D *hptpion;
    TH1D *hptproton;
    TH2D *tpcdedxvsp;
    TH2D *tpcdedxvsppion;
    TH2D *tpcdedxvspproton;
    TH2D *hptvsnsigp;

    TH1D *hptmc;
    TH1D *hptpionmc;
    TH1D *hptprotonflag;
    TH1D *hMCpRECO;
    TH1D *hMCpTRUTH;
    TH1D *hMCpiRECO;
    TH1D *hMCpiTRUTH;

    TH2D *htofmass;
    TH2D *htofmassp;


    TH1D *hpxrespion;
    TH1D *hpxresproton;

    TH1D *hetap;
    TH1D *hrapidity;

    Int_t       events;

    TTreeReaderValue<MpdEvent> MPDEvent_;
    TTreeReaderValue<TClonesArray> MCTrack_;

    MpdTrack *pDSTtrack=0;     
    FairMCTrack *mctrack=0;
    TClonesArray *mpdTracks=0;

    TFile *opfile;

    Float_t prob = 0.3;
    Float_t tofMass = 0.1;

    MpddstSelector(TTree * = 0) : MPDEvent_(fReader, "MPDEvent."), MCTrack_(fReader, "MCTrack"),
    hpt(0), hptpion(0), hptproton(0), tpcdedxvsp(0), tpcdedxvsppion(0), tpcdedxvspproton(0), hptvsnsigp(0), hptmc(0), 
    hptpionmc(0), hptprotonflag(0), hMCpRECO(0), hMCpTRUTH(0), hMCpiRECO(0), hMCpiTRUTH(0), htofmass(0), htofmassp(0),
    hpxrespion(0), hpxresproton(0), hetap(0), hrapidity(0) {}
    
    virtual ~MpddstSelector() { }
    virtual Int_t   Version() const { return 2; }
    virtual void    Begin(TTree *tree);
    virtual void    SlaveBegin(TTree *tree);
    virtual void    Init(TTree *tree);
    virtual Bool_t  Notify();
    virtual Bool_t  Process(Long64_t entry);
    virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
    virtual void    SetOption(const char *option) { fOption = option; }
    virtual void    SetObject(TObject *obj) { fObject = obj; }
    virtual void    SetInputList(TList *input) { fInput = input; }
    virtual TList  *GetOutputList() const { return fOutput; }
    virtual void    Terminate();

    ClassDef(MpddstSelector,0);
};

#endif

#ifdef MpddstSelector_cxx

    void MpddstSelector::Init(TTree *tree){
        mpdloadlibs();

        if (!tree) return;
        fChain = tree;

        fReader.SetTree(tree);

        events = tree->GetEntries();
        cout << " Number of events in DST file = " << events << endl;
    }

    Bool_t MpddstSelector::Notify(){
        return kTRUE;
    }

#endif