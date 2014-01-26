#include "MT2tree.hh"

std::pair<int,int> MT2tree::EleTauParing(std::vector<int> GoodTau0, std::vector<int> GoodEle0){
	std::pair<int,int> ret = make_pair(-1,-1);
	std::vector<std::pair <double, std::pair<int,int> > > allPairs;
  	for(unsigned int i0 = 0; i0 < GoodTau0.size(); i0++){
		int index0 = GoodTau0[i0];
		for(unsigned int i1 = 0; i1 < GoodEle0.size(); i1++){
			int index1 = GoodEle0[i1];
			allPairs.push_back(make_pair((tau[index0].lv.Pt()+ ele[index1].lv.Pt()), make_pair(index0,index1)));
		}
	}	
	PtSumSort mySort;
  	std::sort(allPairs.begin(),allPairs.end(),mySort);
	if(allPairs.size() != 0)  
		ret = allPairs[0].second;
	return ret;
}

std::pair<int,int> MT2tree::GetTauEG(){
  std::vector<int> GoodTau0;
  std::vector<int> GoodEle0;

  for(int i=0; i<NTaus; ++i){ 
	if(tau[i].PassTau_ElTau)
		GoodTau0.push_back(i);
  }
  for(int i=0; i<NEles; ++i){
        if(ele[i].IDSelETau)
                GoodEle0.push_back(i);
  }
  return (EleTauParing(GoodTau0,GoodEle0));  	
}


bool MT2tree::HasNoVetoElecForEleTau(){
	bool ret = true;
	for(int i = 0; i < NEles; i++){
		if(ele[i].IDVetoETau){
			ret = false;
			break;
		}
	}
	return ret;
}

bool MT2tree::HasNoVetoMuForEleTau(){
        bool ret = true;
        for(int i = 0; i < NMuons; i++){ //Don't we need rjection against muons here?
                /*if(muo[i].RejMu1_TauMu){
                        ret = false;
                        break;
                }*/
        }
        return ret;
}

void MT2tree::FillEleTau(){
	eleTau.Reset();	
	std::pair<int,int> indecies = this->GetTauEG();

	if(indecies.first != -1 && indecies.second != -1){
		eleTau.SetTauIndex0(indecies.first);
		eleTau.SetEleIndex0(indecies.second);
		eleTau.SetSumCharge(tau[indecies.first].Charge + ele[indecies.second].Charge);
		eleTau.SetMT2(this->CalcMT2(0, false, tau[indecies.first].lv, ele[indecies.second].lv, pfmet[0]));
		TLorentzVector met = -(tau[indecies.first].lv + ele[indecies.second].lv);
		eleTau.SetMT2Imbalanced(this->CalcMT2(0, false, tau[indecies.first].lv, ele[indecies.second].lv, met));
		eleTau.SetElecVeto(this->HasNoVetoElecForEleTau());
		eleTau.SetMuVeto(this->HasNoVetoMuForEleTau());
	}
}
