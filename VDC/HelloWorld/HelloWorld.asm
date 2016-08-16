// PC-Engine "Hello, World!" Text Printing Demo by krom (Peter Lemon):
arch pce.cpu
output "HelloWorld.pce", create

macro seek(variable offset) {
  origin (offset - $E000)
  base offset
}

// PRG BANK 0 (8KB)
seek($E000); fill $2000 // Fill Bank 0 With Zero Bytes
include "LIB/PCE.INC"        // Include PC-Engine Definitions
include "LIB/PCE_VECTOR.ASM" // Include Vector Table

seek($E000); Start:
  PCE_INIT() // Run PC-Engine Initialisation Routine

  lda #$FF // A = $FF (Segment To Access I/O Ports)
  tam #MPR6 // MPR6 = A

  // VCE: Set Color Table Address (CTA) To Zero
  stz (6<<13)+VCE_CTA   // MPR6:VCE_CTA   = 0 ($FF:0402) (Lo Byte)
  stz (6<<13)+VCE_CTA+1 // MPR6:VCE_CTA+1 = 0 ($FF:0403) (Hi Byte)

  // VCE: Set Color Table (CTRW) Index 0 To Black (9-Bit GRB333)
  lda #%00000000 // A = %00000000
  sta (6<<13)+VCE_CTRW   // MPR6:VCE_CTRW   = A ($FF:0404) (Lo Byte)
  lda #%00000000 // A = %00000000
  sta (6<<13)+VCE_CTRW+1 // MPR6:VCE_CTRW+1 = A ($FF:0405) (Hi Byte)

  // VCE: Set Color Table (CTRW) Index 1 To White (9-Bit GRB333)
  lda #%11111111 // A = %11111111
  sta (6<<13)+VCE_CTRW   // MPR6:VCE_CTRW   = A ($FF:0404) (Lo Byte)
  lda #%00000001 // A = %00000001
  sta (6<<13)+VCE_CTRW+1 // MPR6:VCE_CTRW+1 = A ($FF:0405) (Hi Byte)

  // VDC: Set BG Screen X-Offset To Zero
  st0 #VDC_BXR // VDC: Set VDC Address To Background X-Scroll Register (BXR)
  st1 #0       // VDC: Data = 0 (Lo Byte)
  st2 #0       // VDC: Data = 0 (Hi Byte)

  // VDC: Set BG Screen Y-Offset To Zero
  st0 #VDC_BYR // VDC: Set VDC Address To Background Y-Scroll Register (BYR)
  st1 #0       // VDC: Data = 0 (Lo Byte)
  st2 #0       // VDC: Data = 0 (Hi Byte)

  // VDC: Set BG Virtual Screen Width & Height To 32x32 Tiles
  st0 #VDC_MWR               // VDC: Set VDC Address To Memory Width Register (MWR)
  st1 #VDC_SCRW32+VDC_SCRH32 // VDC: Data = 0 (Lo Byte)
  st2 #0                     // VDC: Data = 0 (Hi Byte)

  // Write Tile Data To VRAM
  // VDC: Set VRAM Write Address To $0400
  st0 #VDC_MAWR // VDC: Set VDC Address To Memory Address Write Register (VRAM Write Address) (MAWR)
  st1 #$00      // VDC: Data = $00 (Lo Byte)
  st2 #$04      // VDC: Data = $04 (Hi Byte)

  st0 #VDC_VWR // VDC: Set VDC Address To VRAM Data Write Register (VWR)
  tia BGCHR,(6<<13)+VDC_DATAL,3040 // MPR6:VDC_DATAL = SOURCE ($FF:0002) (Lo Byte)

  // Write Tile Map (BAT) To VRAM
  // VDC: Set VRAM Write Address To $012C
  st0 #VDC_MAWR // VDC: Set VDC Address To Memory Address Write Register (VRAM Write Address) (MAWR)
  st1 #$2C      // VDC: Data = $2C (Lo Byte)
  st2 #$01      // VDC: Data = $01 (Hi Byte)

  st0 #VDC_VWR // VDC: Set VDC Address To VRAM Data Write Register (VWR)
  tia HELLOWORLD,(6<<13)+VDC_DATAL,26 // MPR6:VDC_DATAL = SOURCE ($FF:0002) (Lo Byte)

  // VDC: Turn On BG Screen
  st0 #VDC_CR // VDC: Set VDC Address To Control Register (CR)
  st1 #VDC_BB // VDC: Data = BB Flag (Background Enable/Disable) (Lo Byte)
  st2 #0      // VDC: Data = 0 (Hi Byte)

Loop:
  bra Loop

// Map Char Table
map ' ', $0040, $5F

HELLOWORLD:
  dw "Hello, World!" // Hello World Text (26 Bytes)

BGCHR:
  include "Font8x8.asm" // Include BG 1BPP 8x8 Tile Font Character Data (3040 Bytes)