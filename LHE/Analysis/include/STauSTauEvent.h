#ifndef STauStauEvent_H
#define STauStauEvent_H

#include "SLepton.h"

class STauSTauEvent : public TObject {
public:
  virtual ~STauSTauEvent(){};
  STauSTauEvent(){};

  SLepton STauP;
  SLepton STauM;

  double MET();
  double MT2();
  
  ClassDef( STauSTauEvent , 1)
};
#endif