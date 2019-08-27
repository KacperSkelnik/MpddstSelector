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

    //Declare your histograms here:
    
    //pt:

	TH1F *pt_pions;
	TH1F *pt_kaons;
	TH1F *pt_protons;
	TH1F *pt_electrons;
	
	//pseudorapidity
	TH1F *eta_pions;
	TH1F *eta_kaons;
	TH1F *eta_protons;
	TH1F *eta_electrons;
	
	//theta
	TH1F *theta_pions;
	TH1F *theta_kaons;
	TH1F *theta_protons;
	TH1F *theta_electrons;
	
	//theta pseudorapidity
	TH2F *theta_eta_pions;
	TH2F *theta_eta_kaons;
	TH2F *theta_eta_protons;
	TH2F *theta_eta_electrons;
	
	//mult
	TH1I *mult_pions;
	TH1I *mult_kaons;
	TH1I *mult_protons;
	TH1I *mult_electrons;

    Int_t       events;

    TTreeReaderValue<MpdEvent> MPDEvent_;
    TTreeReaderValue<TClonesArray> MCTrack_;

    MpdTrack *pDSTtrack=0;     
    FairMCTrack *mctrack=0;
    TClonesArray *mpdTracks=0;

    TFile *opfile = new TFile("basicHistograms.root","RECREATE");

    MpddstSelector(TTree * = 0) : MPDEvent_(fReader, "MPDEvent."), MCTrack_(fReader, "MCTrack"),
    pt_pions(0), pt_kaons(0), pt_protons(0), pt_electrons(0), eta_pions(0), eta_kaons(0), eta_protons(0),
    eta_electrons(0), theta_pions(0), theta_kaons(0), theta_protons(0), theta_electrons(0), 
    theta_eta_pions(0), theta_eta_kaons(0), theta_eta_protons(0), theta_eta_electrons(0),
    mult_pions(0), mult_kaons(0), mult_protons(0), mult_electrons(0) {}
    
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
