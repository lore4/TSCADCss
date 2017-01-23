/*
 * Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *	* Redistributions of source code must retain the above copyright
 *	  notice, this list of conditions and the following disclaimer.
 *
 *	* Redistributions in binary form must reproduce the above copyright
 *	  notice, this list of conditions and the following disclaimer in the
 *	  documentation and/or other materials provided with the
 *	  distribution.
 *
 *	* Neither the name of Texas Instruments Incorporated nor the names of
 *	  its contributors may be used to endorse or promote products derived
 *	  from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _SYS_TSCADCSS_H_
#define _SYS_TSCADCSS_H_

/* SYS_TSCADCSS register set */
typedef struct {

    /***************************/
    /* ADC Subsystem Registers */
    /***************************/
    /* SYS_TSCADCSS_REVISION               register bit field */
    union {
        volatile uint32_t REVISION;
        //volatile struct {} REVISION_bit;
    };  // 0x000h

    uint32_t rsvd4[3];        // 0x004 - 0x010

    /* SYS_TSCADCSS_SYSCONFIG              register bit field */
    union {
        volatile uint32_t SYSCONFIG;
        //volatile struct {} SYSCONFIG_bit;
    };  // 0x010h

    uint32_t rsvd14[4];        // 0x014 - 0x024

    /* SYS_TSCADCSS_IRQSTATUS_RAW          register bit field */
    union {
        volatile uint32_t IRQSTATUS_RAW;
        //volatile struct {} IRQSTATUS_RAW_bit;
    };  // 0x024h

    /* SYS_TSCADCSS_IRQSTATUS              register bit field */
    union {
        volatile uint32_t IRQSTATUS             ;
        //volatile struct {} IRQSTATUS_bit;
    };  // 0x028h

    /* SYS_TSCADCSS_IRQENABLE_SET          register bit field */
    union {
        volatile uint32_t IRQENABLE_SET;
        //volatile struct {} IRQENABLE_SET_bit;
    };  // 0x02Ch

    /* SYS_TSCADCSS_IRQENABLE_CLR          register bit field */
    union {
        volatile uint32_t IRQENABLE_CLR         ;
        //volatile struct {} IRQENABLE_CLR_bit;
    };  // 0x030h

    /* SYS_TSCADCSS_IRQWAKEUP              register bit field */
    union {
        volatile uint32_t IRQWAKEUP             ;
        //volatile struct {} IRQWAKEUP_bit;
    };  // 0x034h

    /* SYS_TSCADCSS_DMAENABLE_SET          register bit field */
    union {
        volatile uint32_t DMAENABLE_SET         ;
        //volatile struct {} DMAENABLE_SET_bit;
    };  // 0x038h

    /* SYS_TSCADCSS_DMAENABLE_CLR          register bit field */
    union {
        volatile uint32_t DMAENABLE_CLR         ;
        //volatile struct {} DMAENABLE_CLR_bit;
    };  // 0x03Ch

    /* SYS_TSCADCSS_CTRL                   register bit field */
    union {
        volatile uint32_t CTRL                  ;
        //volatile struct {} CTRL_bit;
    };  // 0x040h

    /* SYS_TSCADCSS_ADCSTAT                register bit field */
    union {
        volatile uint32_t ADCSTAT               ;
        //volatile struct {} ADCSTAT_bit;
    };  // 0x044h

    /* SYS_TSCADCSS_ADCRANGE               register bit field */
    union {
        volatile uint32_t ADCRANGE              ;
        //volatile struct {} ADCRANGE_bit;
    };  // 0x048h

    /* SYS_TSCADCSS_ADC_CLKDIV             register bit field */
    union {
        volatile uint32_t ADC_CLKDIV            ;
        //volatile struct {} ADC_CLKDIV_bit;
    };  // 0x04Ch

    /* SYS_TSCADCSS_ADC_MISC               register bit field */
    union {
        volatile uint32_t ADC_MISC              ;
        //volatile struct {} ADC_MISC_bit;
    };  // 0x050h

    /* SYS_TSCADCSS_STEPENABLE             register bit field */
    union {
        volatile uint32_t STEPENABLE            ;
        //volatile struct {} STEPENABLE_bit;
    };  // 0x054h

    /* SYS_TSCADCSS_IDLECONFIG             register bit field */
    union {
        volatile uint32_t IDLECONFIG            ;
        //volatile struct {} IDLECONFIG_bit;
    };  // 0x058h

    /* SYS_TSCADCSS_TS_CHARGE_STEPCONFIG   register bit field */
    union {
        volatile uint32_t TS_CHARGE_STEPCONFIG  ;
        //volatile struct {} TS_CHARGE_STEPCONFIG_bit;
    };  // 0x05Ch

    /* SYS_TSCADCSS_TS_CHARGE_DELAY        register bit field */
    union {
        volatile uint32_t TS_CHARGE_DELAY       ;
        //volatile struct {} TS_CHARGE_DELAY_bit;
    };  // 0x060h

    /* SYS_TSCADCSS_STEPCONFIG1            register bit field */
    union {
        volatile uint32_t STEPCONFIG1           ;
        //volatile struct {} STEPCONFIG1_bit;
    };  // 0x064h

    /* SYS_TSCADCSS_STEPDELAY1             register bit field */
    union {
        volatile uint32_t STEPDELAY1            ;
        //volatile struct {} STEPDELAY1_bit;
    };  // 0x068h

    /* SYS_TSCADCSS_STEPCONFIG2            register bit field */
    union {
        volatile uint32_t STEPCONFIG2           ;
        //volatile struct {} STEPCONFIG2_bit;
    };  // 0x06Ch

    /* SYS_TSCADCSS_STEPDELAY2             register bit field */
    union {
        volatile uint32_t STEPDELAY2            ;
        //volatile struct {} STEPDELAY2_bit;
    };  // 0x070h

    /* SYS_TSCADCSS_STEPCONFIG3            register bit field */
    union {
        volatile uint32_t STEPCONFIG3           ;
        //volatile struct {} STEPCONFIG3_bit;
    };  // 0x074h

    /* SYS_TSCADCSS_STEPDELAY3             register bit field */
    union {
        volatile uint32_t STEPDELAY3            ;
        //volatile struct {} STEPDELAY3_bit;
    };  // 0x078h

    /* SYS_TSCADCSS_STEPCONFIG4            register bit field */
    union {
        volatile uint32_t STEPCONFIG4           ;
        //volatile struct {} STEPCONFIG4_bit;
    };  // 0x07Ch

    /* SYS_TSCADCSS_STEPDELAY4             register bit field */
    union {
        volatile uint32_t STEPDELAY4            ;
        //volatile struct {} STEPDELAY4_bit;
    };  // 0x080h

    /* SYS_TSCADCSS_STEPCONFIG5            register bit field */
    union {
        volatile uint32_t STEPCONFIG5           ;
        //volatile struct {} STEPCONFIG5_bit;
    };  // 0x084h

    /* SYS_TSCADCSS_STEPDELAY5             register bit field */
    union {
        volatile uint32_t STEPDELAY5            ;
        //volatile struct {} STEPDELAY5_bit;
    };  // 0x088h

    /* SYS_TSCADCSS_STEPCONFIG6            register bit field */
    union {
        volatile uint32_t STEPCONFIG6           ;
        //volatile struct {} STEPCONFIG6_bit;
    };  // 0x08Ch

    /* SYS_TSCADCSS_STEPDELAY6             register bit field */
    union {
        volatile uint32_t STEPDELAY6            ;
        //volatile struct {} STEPDELAY6_bit;
    };  // 0x090h

    /* SYS_TSCADCSS_STEPCONFIG7            register bit field */
    union {
        volatile uint32_t STEPCONFIG7           ;
        //volatile struct {} STEPCONFIG7_bit;
    };  // 0x094h

    /* SYS_TSCADCSS_STEPDELAY7             register bit field */
    union {
        volatile uint32_t STEPDELAY7            ;
        //volatile struct {} STEPDELAY7_bit;
    };  // 0x098h

    /* SYS_TSCADCSS_STEPCONFIG8            register bit field */
    union {
        volatile uint32_t STEPCONFIG8           ;
        //volatile struct {} STEPCONFIG8_bit;
    };  // 0x09Ch

    /* SYS_TSCADCSS_STEPDELAY8             register bit field */
    union {
        volatile uint32_t STEPDELAY8            ;
        //volatile struct {} STEPDELAY8_bit;
    };  // 0x0A0h

    /* SYS_TSCADCSS_STEPCONFIG9            register bit field */
    union {
        volatile uint32_t STEPCONFIG9           ;
        //volatile struct {} STEPCONFIG9_bit;
    };  // 0x0A4h

    /* SYS_TSCADCSS_STEPDELAY9             register bit field */
    union {
        volatile uint32_t STEPDELAY9            ;
        //volatile struct {} STEPDELAY9_bit;
    };  // 0x0A8h

    /* SYS_TSCADCSS_STEPCONFIG10           register bit field */
    union {
        volatile uint32_t STEPCONFIG10          ;
        //volatile struct {} STEPCONFIG10_bit;
    };  // 0x0ACh

    /* SYS_TSCADCSS_STEPDELAY10            register bit field */
    union {
        volatile uint32_t STEPDELAY10           ;
        //volatile struct {} STEPDELAY10_bit;
    };  // 0x0B0h

    /* SYS_TSCADCSS_STEPCONFIG11           register bit field */
    union {
        volatile uint32_t STEPCONFIG11          ;
        //volatile struct {} STEPCONFIG11_bit;
    };  // 0x0B4h

    /* SYS_TSCADCSS_STEPDELAY11            register bit field */
    union {
        volatile uint32_t STEPDELAY11           ;
        //volatile struct {} STEPDELAY11_bit;
    };  // 0x0B8h

    /* SYS_TSCADCSS_STEPCONFIG12           register bit field */
    union {
        volatile uint32_t STEPCONFIG12          ;
        //volatile struct {} STEPCONFIG12_bit;
    };  // 0x0BCh

    /* SYS_TSCADCSS_STEPDELAY12            register bit field */
    union {
        volatile uint32_t STEPDELAY12           ;
        //volatile struct {} STEPDELAY12_bit;
    };  // 0x0C0h

    /* SYS_TSCADCSS_STEPCONFIG13           register bit field */
    union {
        volatile uint32_t STEPCONFIG13          ;
        //volatile struct {} STEPCONFIG13_bit;
    };  // 0x0C4h

    /* SYS_TSCADCSS_STEPDELAY13            register bit field */
    union {
        volatile uint32_t STEPDELAY13           ;
        //volatile struct {} STEPDELAY13_bit;
    };  // 0x0C8h

    /* SYS_TSCADCSS_STEPCONFIG14           register bit field */
    union {
        volatile uint32_t STEPCONFIG14          ;
        //volatile struct {} STEPCONFIG14_bit;
    };  // 0x0CCh

    /* SYS_TSCADCSS_STEPDELAY14            register bit field */
    union {
        volatile uint32_t STEPDELAY14           ;
        //volatile struct {} STEPDELAY14_bit;
    };  // 0x0D0h

    /* SYS_TSCADCSS_STEPCONFIG15           register bit field */
    union {
        volatile uint32_t STEPCONFIG15          ;
        //volatile struct {} STEPCONFIG15_bit;
    };  // 0x0D4h

    /* SYS_TSCADCSS_STEPDELAY15            register bit field */
    union {
        volatile uint32_t STEPDELAY15           ;
        //volatile struct {} STEPDELAY15_bit;
    };  // 0x0D8h

    /* SYS_TSCADCSS_STEPCONFIG16           register bit field */
    union {
        volatile uint32_t STEPCONFIG16          ;
        //volatile struct {} STEPCONFIG16_bit;
    };  // 0x0DCh

    /* SYS_TSCADCSS_STEPDELAY16            register bit field */
    union {
        volatile uint32_t STEPDELAY16           ;
        //volatile struct {} STEPDELAY16_bit;
    };  // 0x0E0h

    /* SYS_TSCADCSS_FIFO0COUNT             register bit field */
    union {
        volatile uint32_t FIFO0COUNT            ;
        //volatile struct {} FIFO0COUNT_bit;
    };  // 0x0E4h

    /* SYS_TSCADCSS_FIFO0THRESHOLD         register bit field */
    union {
        volatile uint32_t FIFO0THRESHOLD        ;
        //volatile struct {} FIFO0THRESHOLD_bit;
    };  // 0x0E8h

    /* SYS_TSCADCSS_DMA0REQ                register bit field */
    union {
        volatile uint32_t DMA0REQ               ;
        //volatile struct {} DMA0REQ_bit;
    };  // 0x0ECh

    /* SYS_TSCADCSS_FIFO1COUNT             register bit field */
    union {
        volatile uint32_t FIFO1COUNT            ;
        //volatile struct {} FIFO1COUNT_bit;
    };  // 0x0F0h

    /* SYS_TSCADCSS_FIFO1THRESHOLD         register bit field */
    union {
        volatile uint32_t FIFO1THRESHOLD        ;
        //volatile struct {} FIFO1THRESHOLD_bit;
    };  // 0x0F4h

    /* SYS_TSCADCSS_DMA1REQ                register bit field */
    union {
        volatile uint32_t DMA1REQ               ;
        //volatile struct {} DMA1REQ_bit;
    };  // 0x0F8h

    uint32_t rsvdFC[2];        // 0x0FC - 0x100

    /* SYS_TSCADCSS_FIFO0DATA              register bit field */
    union {
        volatile uint32_t FIFO0DATA             ;
        //volatile struct {} FIFO0DATA_bit;
    };  // 0x100h

    /* SYS_TSCADCSS_FIFO1DATA              register bit field */
    union {
        volatile uint32_t FIFO1DATA             ;
        //volatile struct {} FIFO1DATA_bit;
    };  // 0x200h

} sysTscadcss;

//volatile __far sysTscadcss TSCADCSS __attribute((location(0x44E0D000)))
//#define TSCADCSS (*((volatile sysTscadcss*)0x44E0D000))

volatile __far sysTscadcss TSCADCSS __attribute__((cregister("TSCADCSS", far), peripheral));
//volatile __far sysTscadcss TSCADCSS __attribute__((cregister("TSCADCSS", far), peripheral));

#endif /* _SYS_TSCADCSS_H_ */
