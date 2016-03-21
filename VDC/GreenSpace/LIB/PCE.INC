//=================== (Key: R=Read, W=Write) 
// PC-Engine Include
//===================
// Memory Map                         
// Physical Address | Segment : Address
// $000000..$0FFFFF | $00:0000..$7F:1FFF - HuCard/TurboChip ROM                                                1MB/R
// $1F0000..$1F7FFF | $F8:0000..$FB:1FFF - Work RAM (8KB, Mirrored Four Times)                                32KB/RW 
// $1FE000..$1FE3FF | $FF:0000..$FF:03FF - VDC Registers (HuC6270)                                             1KB/RW
// $1FE400..$1FE7FF | $FF:0400..$FF:07FF - VCE Registers (HuC6260)                                             1KB/RW
// $1FE800..$1FEBFF | $FF:0800..$FF:0BFF - PSG Registers                                                       1KB/RW
// $1FF000..$1FF3FF | $FF:1000..$FF:13FF - 8-Bit I/O Port                                                      1KB/RW
// $1FF400..$1FF7FF | $FF:1400..$FF:17FF - Interrupt Controller                                                1KB/RW

// Segment Registers (Use TMA/TAM To Read/Write Segment Registers, Can Write To Multiple Registers At Once)
constant MPR0($01) // MPR0 - 8-Bit Segment Register Concated With Lower 13-Bit Address (Hi 3-Bit Address = MPR)
constant MPR1($02) // MPR1 - 8-Bit Segment Register Concated With Lower 13-Bit Address (Hi 3-Bit Address = MPR)
constant MPR2($04) // MPR2 - 8-Bit Segment Register Concated With Lower 13-Bit Address (Hi 3-Bit Address = MPR)
constant MPR3($08) // MPR3 - 8-Bit Segment Register Concated With Lower 13-Bit Address (Hi 3-Bit Address = MPR)
constant MPR4($10) // MPR4 - 8-Bit Segment Register Concated With Lower 13-Bit Address (Hi 3-Bit Address = MPR)
constant MPR5($20) // MPR5 - 8-Bit Segment Register Concated With Lower 13-Bit Address (Hi 3-Bit Address = MPR)
constant MPR6($40) // MPR6 - 8-Bit Segment Register Concated With Lower 13-Bit Address (Hi 3-Bit Address = MPR)
constant MPR7($80) // MPR7 - 8-Bit Segment Register Concated With Lower 13-Bit Address (Hi 3-Bit Address = MPR)

// VDC Registers (HuC6270) (Mapped To Segment $FF:XXXX)
constant VDC_STATUS($0000) // VDC Status Register                                                               2B/R
constant VDC_CR_FLAG($01)  // VDC Status Read: Bit 0 -  CR Flag (Set On Sprite #0 Collision)                  1Bit/R
constant VDC_OR_FLAG($02)  // VDC Status Read: Bit 1 -  OR Flag (Set On Sprite Overflow)                      1Bit/R
constant VDC_PR_FLAG($04)  // VDC Status Read: Bit 2 -  PR Flag (Set On Scanline Interrupt)                   1Bit/R
constant VDC_DS_FLAG($08)  // VDC Status Read: Bit 3 -  DS Flag (Set On VRAM -> SATB Transfer Complete)       1Bit/R
constant VDC_DV_FLAG($10)  // VDC Status Read: Bit 4 -  DV Flag (Set On VRAM DMA Transfer Complete)           1Bit/R
constant VDC_VD_FLAG($20)  // VDC Status Read: Bit 5 -  VD Flag (Set On Vertical Blank)                       1Bit/R
constant VDC_BSY_FLAG($40) // VDC Status Read: Bit 6 - BSY Flag (Set On VRAM DMA Transfer Busy)               1Bit/R
                           // VDC Status Read: Bit 7..15 - Unused                                             9Bit/R

constant VDC_ADDR($0000)   // VDC Address Register:  ST0 Opcode Can Store Immediate Value Here                  2B/W
                           // VDC Address Write: Bit 0..4 - VDC Register Address Access                       5Bit/W
                           // VDC Address Write: Bit 5..15 - Unused                                          11Bit/W

constant VDC_DATAL($0002)  // VDC Data LSB Register: ST1 Opcode Can Store Immediate Value Here                  1B/RW
constant VDC_DATAH($0003)  // VDC Data MSB Register: ST2 Opcode Can Store Immediate Value Here                  1B/RW

// VDC Memory Map (Read/Write 2 Byte VDC Data To These Register Addresses)
// VDC VRAM Registers
constant VDC_MAWR($00)     // VDC MAWR - Memory Address Write Register (VRAM Write Address)                     2B/RW
constant VDC_MARR($01)     // VDC MARR - Memory Address  Read Register (VRAM  Read Address)                     2B/RW
constant VDC_VWR($02)      // VDC  VWR - VRAM Data Write Register                                               2B/RW
constant VDC_VRR($02)      // VDC  VRR - VRAM Data  Read Register                                               2B/RW

constant VDC_CR($05)       // VDC   CR - Control Register                                                       2B/RW
                           // VDC L CR Read: Bit 0 - CR Flag (Set On Sprite #0 Collision)                     1Bit/R
                           // VDC L CR Read: Bit 1 - OR Flag (Set On Sprite Overflow)                         1Bit/R
                           // VDC L CR Read: Bit 2 - PR Flag (Set On Scanline Interrupt)                      1Bit/R
                           // VDC L CR Read: Bit 3 - VD Flag (Set On Vertical Blank)                          1Bit/R
                           // VDC L CR Read: Bit 4..15 - Unused                                              12Bit/R

constant VDC_IE0($01)      // VDC L CR Write: Bit      0 - IE Flag 0 (Interrupt Enable/Disable)               1Bit/W
constant VDC_IE1($02)      // VDC L CR Write: Bit      1 - IE Flag 1 (Interrupt Enable/Disable)               1Bit/W
constant VDC_IE2($04)      // VDC L CR Write: Bit      2 - IE Flag 2 (Interrupt Enable/Disable)               1Bit/W
constant VDC_IE3($08)      // VDC L CR Write: Bit      3 - IE Flag 3 (Interrupt Enable/Disable)               1Bit/W
constant VDC_EXH($10)      // VDC L CR Write: Bit      4 - EX Horizontal Sync (Signal Input/Output)           1Bit/W
constant VDC_EXV($20)      // VDC L CR Write: Bit      5 - EX   Vertical Sync (Signal Input/Output)           1Bit/W
constant VDC_SB($40)       // VDC L CR Write: Bit      6 - SB Flag (Sprites Enable/Disable)                   1Bit/W
constant VDC_BB($80)       // VDC L CR Write: Bit      7 - BB Flag (Background Enable/Disable)                1Bit/W
constant VDC_DISP($00)     // VDC H CR Write: Bit   8..9 - DR Selects     DISP Terminal Output (%00)          2Bit/W
constant VDC_BURST($01)    // VDC H CR Write: Bit   8..9 - DR Selects    BURST Terminal Output (%01)          2Bit/W
constant VDC_INTHSYNC($02) // VDC H CR Write: Bit   8..9 - DR Selects INTHSYNC Terminal Output (%10)          2Bit/W
                           // VDC H CR Write: Bit   8..9 - DR Selects   Unused Terminal Output (%11)          2Bit/W
constant VDC_DR($04)       // VDC H CR Write: Bit     10 - DR Flag (Dynamic RAM Refresh Enable/Disable)       1Bit/W
constant VDC_INC01($00)    // VDC H CR Write: Bit 11..12 - VRAM Read/Write Address Auto-Increment $01 (%00)   2Bit/W
constant VDC_INC20($08)    // VDC H CR Write: Bit 11..12 - VRAM Read/Write Address Auto-Increment $20 (%01)   2Bit/W
constant VDC_INC40($10)    // VDC H CR Write: Bit 11..12 - VRAM Read/Write Address Auto-Increment $40 (%10)   2Bit/W
constant VDC_INC80($18)    // VDC H CR Write: Bit 11..12 - VRAM Read/Write Address Auto-Increment $80 (%11)   2Bit/W
                           // VDC H CR Write: Bit 13..15 - Unused                                             3Bit/W

constant VDC_RCR($06)      // VDC RCR - Raster Counter Register                                                 2B/RW

constant VDC_BXR($07)      // VDC BXR - Background X-Scroll Register                                            2B/RW
                           // VDC BXR: Bit   0..9 - Screen X-Offset (In Pixels)                              10Bit/RW
                           // VDC BXR: Bit 10..15 - Unused                                                    6Bit/RW

constant VDC_BYR($08)      // VDC BYR - Background Y-Scroll Register                                            2B/RW
                           // VDC BYR: Bit  0..8 - Screen Y-Offset (In Pixels)                                9Bit/RW
                           // VDC BYR: Bit 9..15 - Unused                                                     7Bit/RW

constant VDC_MWR($09)      // VDC MWR - Memory Width Register                                                   2B/RW
constant VDC_VW0($00)      // VDC MWR: Bit  0..1 - VRAM Pixel Width 0 (%00)                                   2Bit/RW
constant VDC_VW1($01)      // VDC MWR: Bit  0..1 - VRAM Pixel Width 1 (%01)                                   2Bit/RW
constant VDC_VW2($02)      // VDC MWR: Bit  0..1 - VRAM Pixel Width 2 (%10)                                   2Bit/RW
constant VDC_VW3($03)      // VDC MWR: Bit  0..1 - VRAM Pixel Width 3 (%11)                                   2Bit/RW
constant VDC_SW0($00)      // VDC MWR: Bit  2..3 - Sprite Pixel Width 0 (%00)                                 2Bit/RW
constant VDC_SW1($04)      // VDC MWR: Bit  2..3 - Sprite Pixel Width 1 (%01)                                 2Bit/RW
constant VDC_SW2($08)      // VDC MWR: Bit  2..3 - Sprite Pixel Width 2 (%10)                                 2Bit/RW
constant VDC_SW3($0C)      // VDC MWR: Bit  2..3 - Sprite Pixel Width 3 (%11)                                 2Bit/RW
constant VDC_SCRW32($00)   // VDC MWR: Bit  4..5 - Virtual Screen Tile Width 32  (256 Pixels)  (%00)          2Bit/RW
constant VDC_SCRW64($10)   // VDC MWR: Bit  4..5 - Virtual Screen Tile Width 64  (512 Pixels)  (%01)          2Bit/RW
constant VDC_SCRW128($20)  // VDC MWR: Bit  4..5 - Virtual Screen Tile Width 128 (1024 Pixels) (%10)          2Bit/RW
constant VDC_SCRW128B($30) // VDC MWR: Bit  4..5 - Virtual Screen Tile Width 128 (1024 Pixels) (%11)          2Bit/RW
constant VDC_SCRH32($00)   // VDC MWR: Bit     6 - Virtual Screen Tile Height 32  (256 Pixels)  (%0)          1Bit/RW
constant VDC_SCRH64($40)   // VDC MWR: Bit     6 - Virtual Screen Tile Height 64  (512 Pixels)  (%1)          1Bit/RW
constant VDC_CM($80)       // VDC MWR: Bit     7 - CM (Color Mode)                                            1Bit/RW
                           // VDC MWR: Bit 8..15 - Unused                                                     8Bit/RW

// VDC Display Registers
constant VDC_HSR($0A)      // VDC   HSR - Horizontal Synchronous Register                                       2B/RW
constant VDC_HSW($1F)      // VDC L HSR: Bit  0..4 - HSW (Horizontal Synchronous Pulse Width)                 5Bit/RW
                           // VDC L HSR: Bit  5..7 - Unused                                                   3Bit/RW
constant VDC_HDS($7F)      // VDC H HSR: Bit 8..14 - HDS (Horizontal Display Starting Position)               7Bit/RW
                           // VDC H HSR: Bit    15 - Unused                                                   1Bit/RW

constant VDC_HDR($0B)      // VDC   HDR - Horizontal Display Register                                           2B/RW
constant VDC_HDW($7F)      // VDC L HDR: Bit  0..6 - HDW (Horizontal Display Width)                           7Bit/RW
                           // VDC L HDR: Bit     7 - Unused                                                   1Bit/RW
constant VDC_HDE($7F)      // VDC H HDR: Bit 8..14 - HDE (Horizontal Display End)                             7Bit/RW
                           // VDC H HDR: Bit    15 - Unused                                                   1Bit/RW

constant VDC_VSR($0C)      // VDC   VSR - Vertical Synchronous Register                                         2B/RW
constant VDC_VSW($1F)      // VDC L VSR: Bit  0..4 - VSW (Vertical Synchronous Pulse Width)                   5Bit/RW
                           // VDC L VSR: Bit  5..7 - Unused                                                   3Bit/RW
constant VDC_VDS($FF)      // VDC H VSR: Bit 8..15 - VDS (Vertical Display Starting Position)                 8Bit/RW

constant VDC_VDR($0D)      // VDC VDR - Vertical Display Register                                               2B/RW
constant VDC_VCR($0E)      // VDC VCR - Vertical Display Ending Postition Register                              2B/RW

// VDC DMA Registers
constant VDC_DCR($0F)      // VDC DCR - DMA Control Register                                                    2B/RW
constant VDC_DSC($01)      // VDC DCR: Bit 0 - DSC VRAM & Sprite Attribute Table (Interrupt Enable/Disable)   1Bit/RW
constant VDC_DVC($02)      // VDC DCR: Bit 1 - DVC VRAM To VRAM Transfer (Interrupt Enable/Disable)           1Bit/RW
constant VDC_SID($04)      // VDC DCR: Bit 2 - SID VRAM To VRAM Source Increment/Decrement (Enable/Disable)   1Bit/RW
                           // VDC DCR: Bit 3..4 - Unused                                                      2Bit/RW
constant VDC_DSR($20)      // VDC DCR: Bit 5 - DSR VRAM & Sprite Attribute Table Repetition (Enable/Disable)  1Bit/RW
                           // VDC DCR: Bit 6..15 - Unused                                                    10Bit/RW

constant VDC_SOUR($10)     // VDC SOUR - Source Address Register                                                2B/RW
constant VDC_DESR($11)     // VDC DESR - DMA Destination Address Register                                       2B/RW
constant VDC_LENR($12)     // VDC LENR - DMA Block Length Register                                              2B/RW
constant VDC_SATB($13)     // VDC SATB - Sprite Attribute Table Address Register                                2B/RW

// VCE Registers (HuC6260) (Mapped To Segment $FF:XXXX)
constant VCE_CR($0400)   // VCE CR - Control Register                                                           2B/W
constant VCE_PCC0($00)   // VCE CR: Bit  0..1 - PCC  5.3693175 MHz (Pixel Clock Control) (%00)                2Bit/W
constant VCE_PCC1($01)   // VCE CR: Bit  0..1 - PCC  7.15909   MHz (Pixel Clock Control) (%01)                2Bit/W
constant VCE_PCC2($02)   // VCE CR: Bit  0..1 - PCC 10.738635  MHz (Pixel Clock Control) (%10)                2Bit/W
constant VCE_PCC3($03)   // VCE CR: Bit  0..1 - PCC 10.738635  MHz (Pixel Clock Control) (%11)                2Bit/W
constant VCE_FC0($00)    // VCE CR: Bit     2 - FC 262 Line Frame (Frame/Field Configuration) (%0)            1Bit/W
constant VCE_FC1($04)    // VCE CR: Bit     2 - FC 263 Line Frame (Frame/Field Configuration) (%1)            1Bit/W
                         // VCE CR: Bit  3..6 - Unused                                                        4Bit/W
constant VCE_SC0($00)    // VCE CR: Bit     7 - SC Colorburst Intact (Strip Colorburst) (%0)                  1Bit/W
constant VCE_SC1($08)    // VCE CR: Bit     7 - SC Strip Colorburst  (Strip Colorburst) (%1)                  1Bit/W
                         // VCE CR: Bit 8..15 - Unused                                                        8Bit/W

constant VCE_CTA($0402)  // VCE CTA - Color Table Address Register                                              2B/W
                         // VCE CTA: Bit  0..8 - Color Table Index (0..511)                                   9Bit/W
                         // VCE CTA: Bit 9..15 - Unused                                                       7Bit/W

constant VCE_CTRW($0404) // VCE CTRW - Color Table Read/Write Register (BRG333)                                 2B/RW
                         // VCE CTRW: Bit  0..2 - Blue                                                        3Bit/RW
                         // VCE CTRW: Bit  3..5 - Red                                                         3Bit/RW
                         // VCE CTRW: Bit  6..8 - Green                                                       3Bit/RW
                         // VCE CTRW: Bit 9..15 - Unused                                                      7Bit/RW

// PSG Registers (Mapped To Segment $FF:XXXX)
constant PSG_R0($0800) // PSG Register 0                                                                        1B/RW
constant PSG_R1($0801) // PSG Register 1                                                                        1B/RW
constant PSG_R2($0802) // PSG Register 2                                                                        1B/RW
constant PSG_R3($0803) // PSG Register 3                                                                        1B/RW
constant PSG_R4($0804) // PSG Register 4                                                                        1B/RW
constant PSG_R5($0805) // PSG Register 5                                                                        1B/RW
constant PSG_R6($0806) // PSG Register 6                                                                        1B/RW
constant PSG_R7($0807) // PSG Register 7                                                                        1B/RW
constant PSG_R8($0808) // PSG Register 8                                                                        1B/RW
constant PSG_R9($0809) // PSG Register 9                                                                        1B/RW

// 8-Bit I/O Port (Mapped To Segment $FF:XXXX)
constant JOYIO($1000) // JOYIO - Joypad I/O Port Register                                                       1B/R
constant TRG1($01)    // JOYIO: Bit 0 - Joypad Trigger 1                                                      1Bit/R
constant TRG2($02)    // JOYIO: Bit 1 - Joypad Trigger 2                                                      1Bit/R
constant SEL($04)     // JOYIO: Bit 2 - Joypad Select Button                                                  1Bit/R
constant RUN($08)     // JOYIO: Bit 3 - Joypad Run Button                                                     1Bit/R
constant UP($10)      // JOYIO: Bit 4 - Joypad Direction Up                                                   1Bit/R
constant RIGHT($20)   // JOYIO: Bit 5 - Joypad Direction Right                                                1Bit/R
constant DOWN($40)    // JOYIO: Bit 6 - Joypad Direction Down                                                 1Bit/R
constant LEFT($80)    // JOYIO: Bit 7 - Joypad Direction Left                                                 1Bit/R

// PC-Engine Initialisation
macro PCE_INIT() {
  // VDC: Set VRAM Write Address To Zero
  st0 #VDC_MAWR // VDC: Set VDC Address To Set Memory Address Write (VRAM Write Address) (MAWR)
  st1 #0        // VDC: Data = 0 (Lo Byte)
  st2 #0        // VDC: Data = 0 (Hi Byte)

  // VDC: Clear 65536 VRAM Bytes To Zero
  st0 #VDC_VWR // VDC: Set VDC Address To VRAM Data Write To Control Register (VWR)
  ldx #0
  ldy #128
  -
    st1 #0 // VDC: Data = 0 (Lo Byte)
    st2 #0 // VDC: Data = 0 (Hi Byte)
    dex
    bne -
    dey
    bne -
}