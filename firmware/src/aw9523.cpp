#include "aw9523.h"

void AW9523::wr(uint8_t r, uint8_t v){ _w->beginTransmission(_a); _w->write(r); _w->write(v); _w->endTransmission(); }
uint8_t AW9523::rd(uint8_t r){ _w->beginTransmission(_a); _w->write(r); _w->endTransmission(false);
  _w->requestFrom((int)_a,1); return _w->available()? _w->read():0xFF; }

bool AW9523::begin(TwoWire &w, uint8_t addr){
  _w=&w; _a=addr;
  if (rd(0x10)==0xFF) return false;          // ID reg readback sanity
  reset();
  return true;
}
void AW9523::reset(){ wr(SOFT_RESET,0x00); delay(2); wr(GCR,0x10); /*P0 push-pull, max ISEL*/ }
void AW9523::configP0(uint8_t dirMask){ wr(CFG_P0,dirMask); }
void AW9523::p0PushPull(bool en){ uint8_t g=rd(GCR); g = en? (g|0x10):(g&~0x10); wr(GCR,g); }
uint8_t AW9523::readP0(){ return rd(IN_P0); }
void AW9523::writeP0Bit(uint8_t bit, bool high){
  _outShadow = high? (_outShadow|(1<<bit)) : (_outShadow&~(1<<bit)); wr(OUT_P0,_outShadow);
}
void AW9523::ledMode(uint8_t bit, bool ledCurrent){
  uint8_t m=rd(LEDMODE_P0); m = ledCurrent? (m&~(1<<bit)) : (m|(1<<bit)); wr(LEDMODE_P0,m);
}
void AW9523::ledLevel(uint8_t p0bit, uint8_t val){
  // DIM map: P0_0..P0_7 → 0x20..0x27 on AW9523B
  wr(DIM_BASE + p0bit, val);
}

// ---- encoder: standard 2-bit Gray state machine, 4 transitions per detent ---
int Encoder::update(bool a, bool b){
  static const int8_t tab[16] = {0,-1,1,0, 1,0,0,-1, -1,0,0,1, 0,1,-1,0};
  uint8_t cur = (a<<1)|b;
  int8_t d = tab[(_prev<<2)|cur];
  _prev = cur; _accum += d;
  if (_accum>=4){ _accum=0; return +1; }
  if (_accum<=-4){ _accum=0; return -1; }
  return 0;
}
