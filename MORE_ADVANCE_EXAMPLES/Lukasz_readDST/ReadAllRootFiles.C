void ReadAllRootFiles(TChain *dstTree){
    
    //first way to load root files

	//Add all exsisting mpddst.root files to chain
	TString fileName;
	//for( Int_t iter=260819; iter<=260820; ++iter){ 
		//fileName = "/eos/nica/mpd/data/Urqmd.11GeV/" + to_string(iter) + "/TestEvUrqmd/mpddst.root";
		fileName = "/home/kacper/work/MpddstSelectorCluster/mpddst.root";
		dstTree->Add(fileName.Data());
		//}





    //secound way to load root files

  /*char fname[500];

  TString ffname;
  int namegot = 0;

  ifstream *istr = new ifstream("./urqmd34-11gev.list.txt");
  cout<<"opened list file"<<endl;
  int i=0;
  int filesIn = 0;
  while (!istr->eof())
    {
      //      cout<<"Inside file no "<<i<<endl;
      i++;
      istr->getline(fname, 500);
      cout<<i<<"["<<fname<<"] "<<endl;
      TString fn(fname);
      if (fn.Contains(".root"))
  	{
  	  dstTree->Add(fname);
  	  cout << "Added " << fname << endl;
	  filesIn++;
  	  if (!namegot) {
  	    ffname = fname;
  	  }
  	}
    }*/
}
