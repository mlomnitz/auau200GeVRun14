#include <TSystem>

class StMaker;
class StChain;
class StPicoDstMaker;


StChain *chain;
void runPicoD0EventMaker(const Char_t *inputFile="test.list", const Char_t *outputFile="test.root")
{ 
  //Check STAR Library. Please set SL_version to the original star library used in the production from http://www.star.bnl.gov/devcgi/dbProdOptionRetrv.pl
  string SL_version = "SL15c";
  string env_SL = getenv ("STAR");
  if(env_SL.find(SL_version)==string::npos)
  {
      cout<<"Environment Star Library does not match the requested library in runPicoD0EventMaker.C. Exiting..."<<endl;
      exit(1);
  }

  Int_t nEvents = 10000000;
	
  gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
	loadSharedLibraries();

	gSystem->Load("StPicoDstMaker");
  gSystem->Load("StPicoD0Maker");

	chain = new StChain();

	StPicoDstMaker* picoMaker = new StPicoDstMaker(0,inputFile,"picoDst");
  StPicoD0EventMaker = new StPicoD0EventMaker("ana",picoMaker,outputFile);

	chain->Init();
	cout<<"chain->Init();"<<endl;
	int total = picoMaker->chain()->GetEntries();
  cout << " Total entries = " << total << endl;
  if(nEvents>total) nEvents = total;

	for (Int_t i=0; i<nEvents; i++)
  {
	  if(i%10000==0)
		cout << "Working on eventNumber " << i << endl;
		
	  chain->Clear();
	  int iret = chain->Make(i);
		
	  if (iret) { cout << "Bad return code!" << iret << endl; break;}

	  total++;
	}
	
	cout << "****************************************** " << endl;
	cout << "Work done... now its time to close up shop!"<< endl;
	cout << "****************************************** " << endl;
	chain->Finish();
	cout << "****************************************** " << endl;
	cout << "total number of events  " << nEvents << endl;
	cout << "****************************************** " << endl;
	
	delete chain;
}