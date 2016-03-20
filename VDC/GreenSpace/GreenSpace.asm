// PC-Engine Green Space Demo by krom (Peter Lemon):
arch pce.cpu
output "GreenSpace.pce", create

macro seek(variable offset) {
  origin (offset - $E000)
  base offset
}

// PRG BANK 0 (8KB)
seek($E000); fill $2000 // Fill Bank 0 With Zero Bytes
include "LIB\PCE.INC"        // Include PC-Engine Definitions
include "LIB\PCE_VECTOR.ASM" // Include Vector Table

seek($E000); Start:
  lda #$FF // A = $FF (Segment To Access I/O Ports)
  tam #MPR6 // MPR6 = A

  // VCE: Set Color Table Address (CTA) To Zero
  stz (6<<13)+VCE_CTA   // MPR6:VCE_CTA   = 0 ($FF:0402) (Lo Byte)
  stz (6<<13)+VCE_CTA+1 // MPR6:VCE_CTA+1 = 0 ($FF:0403) (Hi Byte)

  // VCE: Set Color Table (CTRW) Index 0 To Green (9-Bit GRB333)
  lda #%11000000 // A = %11000000
  sta (6<<13)+VCE_CTRW   // MPR6:VCE_CTRW   = A ($FF:0404) (Lo Byte)
  lda #%00000001 // A = %00000001
  sta (6<<13)+VCE_CTRW+1 // MPR6:VCE_CTRW+1 = A ($FF:0405) (Hi Byte)

  // VDC: Set VRAM Write Address To Zero
  st0 #VDC_MAWR // VDC: Set VDC Address To Set Memory Address Write (VRAM Write Address) (MAWR)
  st1 #0        // VDC: Data = 0 (Lo Byte)
  st2 #0        // VDC: Data = 0 (Hi Byte)

  // VDC: Clear 65536 VRAM Bytes To Zero
  st0 #VDC_VWR // VDC: Set VDC Address To VRAM Data Write To Control Register (VWR)
  ldx #0
  ldy #128
  LoopVRAM:
    st1 #0 // VDC: Data = 0 (Lo Byte)
    st2 #0 // VDC: Data = 0 (Hi Byte)
    dex
    bne LoopVRAM
    dey
    bne LoopVRAM

  // VDC: Turn On BG Screen
  st0 #VDC_CR // VDC: Set VDC Address To Control Register (CR)
  st1 #VDC_BB // VDC: Data = BB Flag (Background Enable/Disable) (Lo Byte)
  st2 #0      // VDC: Data = 0 (Hi Byte)

Loop:
  bra Loop