// PC-Engine Play Sample Demo by krom (Peter Lemon):
arch pce.cpu
output "PlaySample.pce", create

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

  // PSG: Write Sample Data To Channel 0 Waveform RAM
  tin Sample,(6<<13)+PSG_R6,32 // MPR6:PSG_R6 = SOURCE ($FF:0806)

  // PSG: Reset LFO Trigger
  lda #PSG_LFO // A = $80 (LFO Trigger Disable)
  sta (6<<13)+PSG_R9 // MPR6:PSG_R9 = $80 ($FF:0809)

  // PSG: Set Global Sound Balance (Overall Sound Volume For Mixed Channels)
  lda #$FF // A = $FF (Left/Right 100% Volume)
  sta (6<<13)+PSG_R1 // MPR6:PSG_R1 = $FF ($FF:0801)

  // PSG: Set Channel 0 Balance (Volume Balance Of An Individual Channel)
  lda #$FF // A = $FF (Left/Right 100% Volume)
  sta (6<<13)+PSG_R5 // MPR6:PSG_R5 = $FF ($FF:0805)

  // PSG: Set 12-Bit Waveform Frequency For Channel 0
  lda #$FE // A = $FE (440 Hz)
  sta (6<<13)+PSG_R2 // MPR6:PSG_R2 = $FE ($FF:0802) (Lo Byte)
  lda #$00 // A = $00
  sta (6<<13)+PSG_R3 // MPR6:PSG_R3 = $04 ($FF:0803) (Hi Byte)

  // PSG: Set Channel 0 Volume & Enable Output
  lda #PSG_CHAN+$F // A = $8F (Enable Channel, 100% Volume)
  sta (6<<13)+PSG_R4 // MPR6:PSG_R4 = $8F ($FF:0804)

Loop:
  bra Loop

Sample: // 5-Bit Unsigned Linear Sample Data (32 Bytes)
//  db $0F, $12, $15, $17, $19, $1B, $1D, $1E // Sine Wave
//  db $1E, $1E, $1D, $1B, $19, $17, $15, $12
//  db $0F, $0C, $09, $07, $05, $03, $01, $00
//  db $00, $00, $01, $03, $05, $07, $09, $0C

  db $1F, $1F, $1F, $1F, $1F, $1F, $1F, $1F // Square Wave
  db $1F, $1F, $1F, $1F, $1F, $1F, $1F, $1F
  db $00, $00, $00, $00, $00, $00, $00, $00
  db $00, $00, $00, $00, $00, $00, $00, $00