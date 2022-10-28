#include "../pdfparams/Fantomas/fantomas.h"

extern "C" void xfitter_();

int main() {
  xfitter_();
  writefantosteer();
  return 0;
}
