; -------------------------------------------------
;       boot.asm
;       APEX BIOS Entry
;
;       Based on GPL-3.0 open source agreement
;       Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
; -------------------------------------------------

BITS 16
ORG 0xF0000

ENTRY:
    MOV     AX, CS
    MOV     DS, AX
    XOR     AX, AX
    MOV     ES, AX

    MOV     SI, GDT
    MOV     DI, 0x400
    MOV     CX, GDTEnd - GDT
    REP     MOVSB

    LGDT    [GDTDescriptor]

    MOV     EAX, CR0
    OR      AL, 1
    MOV     CR0, EAX

    MOV     AX, 0x10
    MOV     DS, AX
    MOV     ES, AX
    MOV     FS, AX
    MOV     GS, AX
    MOV     SS, AX
    MOV     ESP, 0x3000

    JMP     DWORD 0x08:C_ENTRY_Bin

GDT:
    DQ      0x0000000000000000
    DQ      0x00cf9a000000ffff
    DQ      0x00cf93000000ffff
GDTEnd:

GDTDescriptor:
    DW      GDTEnd - GDT - 1
    DD      0x400
    TIMES   0x60 - ($ - $$) DB 0x00

C_ENTRY_Bin:
    INCBIN  "build/c_entry.bin" 
    BITS    16

    TIMES   (0x10000 - 16) - ($ - $$) DB 0x00

ResetVector:
    CLI
    CLD
    JMP     0xF000:ENTRY
    TIMES   0x10000 - ($ - $$) DB 0x00
