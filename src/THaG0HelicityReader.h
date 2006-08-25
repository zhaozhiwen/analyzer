#ifndef ROOT_THaG0HelicityReader
#define ROOT_THaG0HelicityReader

//////////////////////////////////////////////////////////////////////////
//
// THaG0HelicityReader
//
// Support for decoding G0 helicity hardware
//
//////////////////////////////////////////////////////////////////////////

#include "Rtypes.h"

class THaEvData;

class THaG0HelicityReader {
  
public:
  THaG0HelicityReader();
  virtual ~THaG0HelicityReader();
  
  enum EROC { kHel = 0, kTime, kROC2, kROC3 };
  Int_t SetROCinfo( Int_t which, Int_t roc, Int_t header, Int_t index );

  void     ClearG0();

  Bool_t   GetValidTime() const { return fValidTime; }

  // Get ROC helicity information (for debugging)
  Int_t    GetQrt() const { return fQrt; }
  Int_t    GetGate() const { return fGate; }
  Int_t    GetReading() const { return fPresentReading; }

protected:

  virtual Int_t ReadData( const THaEvData& evdata );

  Int_t fPresentReading;       // Current helicity reading
  Int_t fQrt, fGate;           // Current QRT and Gate

  Double_t fTimestamp;         // Event time from 105 kHz clock
  Double_t fOldT1, fOldT2, fOldT3;  // Last event's timestamps
  Bool_t   fValidTime;         // fTimestamp valid

//FIXME: Vince's kludge - move elsewhere
  //FIXME: move out
//   Int_t    GetNumRead() const { return fNumread; } // Latest valid reading
//   Int_t    GetBadRead() const { return fBadread; } // Latest problematic reading
//   // Get methods for Ring Buffer scalers
//   Int_t GetRingClk()      const { return fRing_clock; }
//   Int_t GetRingQrt()      const { return fRing_qrt; }
//   Int_t GetRingHelicity() const { return fRing_helicity; }
//   Int_t GetRingTrig()     const { return fRing_trig; }
//   Int_t GetRingBCM()      const { return fRing_bcm; }
//   Int_t GetRingl1a()      const { return fRing_l1a; }
//   Int_t GetRingV2fh()     const { return fRing_v2fh; }

  // ring buffer scalers
//   Int_t fRing_clock, fRing_qrt, fRing_helicity;
//   Int_t fRing_trig, fRing_bcm, fRing_l1a, fRing_v2fh;

  // ROC information
  // If a header is zero the index is taken to be from the start of
  // the ROC (0 = first word of ROC), otherwise it's from the header
  // (0 = first word after header).
  struct ROCinfo {
    Int_t roc;            // ROC to read out
    Int_t header;         // Headers to search for (0 = ignore)
    Int_t index;          // Index into buffer
  };
  ROCinfo fROCinfo[kROC3+1]; // Primary readouts and two redundant clocks

  Bool_t fHaveROCs;       // Required ROCs are defined
  Int_t  fG0Debug;        // Debug level

private:

  static Int_t FindWord( const THaEvData& evdata, const ROCinfo& info );

  ClassDef(THaG0HelicityReader,1) // Helper class for reading G0 helicity data

};

#endif
