root -b -l<<EOF
TProof::Open("")
TChain* myChain = new TChain("cbmsim")
.L ReadAllRootFiles.C 
ReadAllRootFiles(myChain)
myChain->SetProof()
myChain->Process("MpddstSelector.C")
EOF
