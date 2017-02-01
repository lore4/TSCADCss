/*
 * MIT license
 *
 * Copyright (c) 2017 lore4
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _SYS_TSCADCSS_H_
#define _SYS_TSCADCSS_H_

struct StepConfig {   // Based on ZMATT structures.

    // sequence config (n/a for idle and charge steps)
    unsigned continuous : 1;    // 0
    unsigned hw_sync    : 1;    // 1
    unsigned averaging  : 3;    // 2-4 log2, max 4 (= 16 samples)

    // analog config (touchscreen transistors)
    unsigned ch0_p_sw   : 1;  // 5  drive ch 0 (x+) high
    unsigned ch1_n_sw   : 1;  // 6  drive ch 1 (x-) low
    unsigned ch2_p_sw   : 1;  // 7  drive ch 2 (y+) high
    unsigned ch3_n_sw   : 1;  // 8  drive ch 3 (y-) low

    unsigned ch1_p_sw   : 1;  // 9  drive ch 1 (x-) high
    unsigned ch2_n_sw   : 1;  // 10 drive ch 2 (y+) low

    unsigned ch4_n_sw   : 1;  // 11 drive ch 4 (w) low

    // analog config (analog muxes)
    unsigned refp_sel   : 3;  // 12-14  vdda, x+, y+, vref+
    unsigned inm_sel    : 4;  // 15-18  ch0, ..., ch7, vref-
    unsigned inp_sel    : 4;  // 19-22  ch0, ..., ch7, vref-
    unsigned refm_sel   : 2;  // 23-24  vssa, x-, y-, vref-

    // analog config (adc config)
    unsigned en_diff    : 1;  // 25 differential measurement

    // data config (n/a for idle and charge step)
    unsigned dest_fifo  : 1;    // 26
    unsigned range_chk  : 1;        // 27
    unsigned reserved28_31   : 4;        // 28-31    Reserved.

    // relationship between inputs and sample value:
    //
    //    sample    single-ended    differential
    //    0x000     in+ == ref-     in+ == ref- && in- == ref+
    //    0xfff     in+ == ref+     in+ == ref+ && in- == ref-
};

struct StepDelay {
    unsigned open_delay     : 18;   // 0-17 cycles
    unsigned reserved       :  6;   // 18-23    Reserved
    unsigned sample_time    :  8;   // 24-31    cycles - 2

    // Sampling steps consist of:
    //  open_delay cycles with muxes configured (may be 0)
    //  2^averaging times
    //      2 + sample_time cycles of sampling
    //      13 cycles of conversion
    //
    // Charging step only has open_delay, which must be non-zero.
    //
    // Idle step lacks this register.
};

struct Fifo {
    uint32_t level;      //r-  number of words currently in fifo
    uint32_t irq_thr;    //rw  irq threshold (= read burst - 1)
    uint32_t dma_thr;    //rw  dma event threshold (= dma burst - 1)
};

struct FifoData {
    union {
            volatile uint32_t REGISTER;
            volatile struct {
                unsigned ADCDATA                                 : 12;  //0-11
                unsigned reserved12_15                           : 4;   //12-15
                unsigned ADCCHNLID                               : 4;   //16-19
                unsigned reserved20_31                           : 12;  //20-31
            } REGISTER_bit;
        };  // 0x000h
};

/* SYS_TSCADCSS register set */
typedef struct {

    /***************************/
    /* ADC Subsystem Registers */
    /***************************/
    // Note: before you disable the ADC, be sure to disable all steps and
    // wait for the FSM to become idle.  Disabling also resets fifos.

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
        volatile struct {
            unsigned HW_PEN_EVENT_ASYNCHRONOUS  : 1; // 0
            unsigned END_OF_SEQUENCE            : 1; // 1
            unsigned FIFO0_THRESHOLD            : 1; // 2
            unsigned FIFO0_OVERRUN              : 1; // 3
            unsigned FIFO0_UNDERFLOW            : 1; // 4
            unsigned FIFO1_THRESHOLD            : 1; // 5
            unsigned FIFO2_OVERRUN              : 1; // 6
            unsigned FIFO3_UNDERFLOW            : 1; // 7
            unsigned OUT_OF_RANGE               : 1; // 8
            unsigned PEN_UP_EVENT               : 1; // 9
            unsigned HW_PEN_EVENT_SYNCHRONOUS   : 1; // 10
            unsigned reserved21                 : 21; // 11-31
        } IRQSTATUS_RAW_bit;
    };  // 0x024h

    /* SYS_TSCADCSS_IRQSTATUS              register bit field */
    union {
        volatile uint32_t IRQSTATUS             ;
        //volatile struct {} IRQSTATUS_bit;
    };  // 0x028h

    /* SYS_TSCADCSS_IRQENABLE_SET          register bit field */
    union {
        volatile uint32_t IRQENABLE_SET;
        volatile struct {
            unsigned HW_PEN_EVENT_ASYNCHRONOUS  : 1; // 0
            unsigned END_OF_SEQUENCE            : 1; // 1
            unsigned FIFO0_THRESHOLD            : 1; // 2
            unsigned FIFO0_OVERRUN              : 1; // 3
            unsigned FIFO0_UNDERFLOW            : 1; // 4
            unsigned FIFO1_THRESHOLD            : 1; // 5
            unsigned FIFO2_OVERRUN              : 1; // 6
            unsigned FIFO3_UNDERFLOW            : 1; // 7
            unsigned OUT_OF_RANGE               : 1; // 8
            unsigned PEN_UP_EVENT               : 1; // 9
            unsigned HW_PEN_EVENT_SYNCHRONOUS   : 1; // 10
            unsigned reserved21                 : 21; // 11-31
        } IRQENABLE_SET_bit;
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
        volatile struct {
            unsigned ENABLE                                 : 1;    //0
            unsigned STEP_ID_TAG                            : 1;    //1
            unsigned STEPCONFIG_WRITEPROTECT_N_ACTIVE_LOW   : 1;    //2
            unsigned ADC_BIAS_SEELECT                       : 1;    //3
            unsigned POWER_DOWN                             : 1;    //4
            unsigned AFE_PEN_CTRL                           : 2;    //5-6
            unsigned TOUCH_SCREEN_ENABLE                    : 1;    //7
            unsigned HW_EVENT_MAPPING                       : 1;    //8
            unsigned HW_PREEMPT                             : 1;    //9
            unsigned reserved10_31                          : 1;    //10-31
        } CTRL_bit;
    };  // 0x040h

    /* SYS_TSCADCSS_ADCSTAT                register bit field */
    union {
        volatile uint32_t ADCSTAT               ;
        volatile struct {
            unsigned STEP_ID                                : 5;    // 0-4
            unsigned FSM_BUSY                               : 1;   // 5
            unsigned PEN_IRQ0                               : 1;   // 6
            unsigned PEN_IRQ1                               : 1;   // 7
        } ADCSTAT_bit;
    };  // 0x044h

    /* SYS_TSCADCSS_ADCRANGE               register bit field */
    union {
        volatile uint32_t ADCRANGE              ;
        //volatile struct {} ADCRANGE_bit;
    };  // 0x048h

    /* SYS_TSCADCSS_ADC_CLKDIV             register bit field */
    union {
        volatile uint32_t ADC_CLKDIV            ;
        volatile struct {
            unsigned ADC_CLKDIV                             : 16;   //0-15
            unsigned reserved16_31                          : 16;   //16-31
        } ADC_CLKDIV_bit;
    };  // 0x04Ch

    /* SYS_TSCADCSS_ADC_MISC               register bit field */
    union {
        volatile uint32_t ADC_MISC;
        //volatile struct {} ADC_MISC_bit;
    };  // 0x050h

    /* SYS_TSCADCSS_STEPENABLE             register bit field */
    union {
        volatile uint32_t STEPENABLE;
        volatile struct {
            unsigned TS_CHARGE                              : 1;    //0
            unsigned STEP1                                  : 1;    //1
            unsigned STEP2                                  : 1;    //2
            unsigned STEP3                                  : 1;    //3
            unsigned STEP4                                  : 1;    //4
            unsigned STEP5                                  : 1;    //5
            unsigned STEP6                                  : 1;    //6
            unsigned STEP7                                  : 1;    //7
            unsigned STEP8                                  : 1;    //8
            unsigned STEP9                                  : 1;    //9
            unsigned STEP10                                 : 1;    //10
            unsigned STEP11                                 : 1;    //11
            unsigned STEP12                                 : 1;    //12
            unsigned STEP13                                 : 1;    //13
            unsigned STEP14                                 : 1;    //14
            unsigned STEP15                                 : 1;    //15
            unsigned STEP16                                 : 1;    //16
            unsigned reserved17_31                          : 15;   //17-31
        } STEPENABLE_bit;
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
        volatile struct StepConfig STEPCONFIG1_bit;
    };  // 0x064h

    /* SYS_TSCADCSS_STEPDELAY1             register bit field */
    union {
        volatile uint32_t STEPDELAY1            ;
        volatile struct StepDelay STEPDELAY1_bit;
    };  // 0x068h

    /* SYS_TSCADCSS_STEPCONFIG2            register bit field */
    union {
        volatile uint32_t STEPCONFIG2           ;
        volatile struct StepConfig STEPCONFIG2_bit;
    };  // 0x06Ch

    /* SYS_TSCADCSS_STEPDELAY2             register bit field */
    union {
        volatile uint32_t STEPDELAY2            ;
        volatile struct StepDelay STEPDELAY2_bit;
    };  // 0x070h

    /* SYS_TSCADCSS_STEPCONFIG3            register bit field */
    union {
        volatile uint32_t STEPCONFIG3           ;
        volatile struct StepConfig STEPCONFIG3_bit;
    };  // 0x074h

    /* SYS_TSCADCSS_STEPDELAY3             register bit field */
    union {
        volatile uint32_t STEPDELAY3            ;
        volatile struct StepDelay STEPDELAY3_bit;
    };  // 0x078h

    /* SYS_TSCADCSS_STEPCONFIG4            register bit field */
    union {
        volatile uint32_t STEPCONFIG4           ;
        volatile struct StepConfig STEPCONFIG4_bit;
    };  // 0x07Ch

    /* SYS_TSCADCSS_STEPDELAY4             register bit field */
    union {
        volatile uint32_t STEPDELAY4            ;
        volatile struct StepDelay STEPDELAY4_bit;
    };  // 0x080h

    /* SYS_TSCADCSS_STEPCONFIG5            register bit field */
    union {
        volatile uint32_t STEPCONFIG5           ;
        volatile struct StepConfig STEPCONFIG5_bit;
    };  // 0x084h

    /* SYS_TSCADCSS_STEPDELAY5             register bit field */
    union {
        volatile uint32_t STEPDELAY5            ;
        volatile struct StepDelay STEPDELAY5_bit;
    };  // 0x088h

    /* SYS_TSCADCSS_STEPCONFIG6            register bit field */
    union {
        volatile uint32_t STEPCONFIG6           ;
        volatile struct StepConfig STEPCONFIG6_bit;
    };  // 0x08Ch

    /* SYS_TSCADCSS_STEPDELAY6             register bit field */
    union {
        volatile uint32_t STEPDELAY6            ;
        volatile struct StepDelay STEPDELAY6_bit;
    };  // 0x090h

    /* SYS_TSCADCSS_STEPCONFIG7            register bit field */
    union {
        volatile uint32_t STEPCONFIG7           ;
        volatile struct StepConfig STEPCONFIG7_bit;
    };  // 0x094h

    /* SYS_TSCADCSS_STEPDELAY7             register bit field */
    union {
        volatile uint32_t STEPDELAY7            ;
        volatile struct StepDelay STEPDELAY7_bit;
    };  // 0x098h

    /* SYS_TSCADCSS_STEPCONFIG8            register bit field */
    union {
        volatile uint32_t STEPCONFIG8           ;
        volatile struct StepConfig STEPCONFIG8_bit;
    };  // 0x09Ch

    /* SYS_TSCADCSS_STEPDELAY8             register bit field */
    union {
        volatile uint32_t STEPDELAY8            ;
        volatile struct StepDelay STEPDELAY8_bit;
    };  // 0x0A0h

    /* SYS_TSCADCSS_STEPCONFIG9            register bit field */
    union {
        volatile uint32_t STEPCONFIG9           ;
        volatile struct StepConfig STEPCONFIG9_bit;
    };  // 0x0A4h

    /* SYS_TSCADCSS_STEPDELAY9             register bit field */
    union {
        volatile uint32_t STEPDELAY9            ;
        volatile struct StepDelay STEPDELAY9_bit;
    };  // 0x0A8h

    /* SYS_TSCADCSS_STEPCONFIG10           register bit field */
    union {
        volatile uint32_t STEPCONFIG10          ;
        volatile struct StepConfig STEPCONFIG10_bit;
    };  // 0x0ACh

    /* SYS_TSCADCSS_STEPDELAY10            register bit field */
    union {
        volatile uint32_t STEPDELAY10           ;
        volatile struct StepDelay STEPDELAY10_bit;
    };  // 0x0B0h

    /* SYS_TSCADCSS_STEPCONFIG11           register bit field */
    union {
        volatile uint32_t STEPCONFIG11          ;
        volatile struct StepConfig STEPCONFIG11_bit;
    };  // 0x0B4h

    /* SYS_TSCADCSS_STEPDELAY11            register bit field */
    union {
        volatile uint32_t STEPDELAY11           ;
        volatile struct StepDelay STEPDELAY11_bit;
    };  // 0x0B8h

    /* SYS_TSCADCSS_STEPCONFIG12           register bit field */
    union {
        volatile uint32_t STEPCONFIG12          ;
        volatile struct StepConfig STEPCONFIG12_bit;
    };  // 0x0BCh

    /* SYS_TSCADCSS_STEPDELAY12            register bit field */
    union {
        volatile uint32_t STEPDELAY12           ;
        volatile struct StepDelay STEPDELAY12_bit;
    };  // 0x0C0h

    /* SYS_TSCADCSS_STEPCONFIG13           register bit field */
    union {
        volatile uint32_t STEPCONFIG13          ;
        volatile struct StepConfig STEPCONFIG13_bit;
    };  // 0x0C4h

    /* SYS_TSCADCSS_STEPDELAY13            register bit field */
    union {
        volatile uint32_t STEPDELAY13           ;
        volatile struct StepDelay STEPDELAY13_bit;
    };  // 0x0C8h

    /* SYS_TSCADCSS_STEPCONFIG14           register bit field */
    union {
        volatile uint32_t STEPCONFIG14          ;
        volatile struct StepConfig STEPCONFIG14_bit;
    };  // 0x0CCh

    /* SYS_TSCADCSS_STEPDELAY14            register bit field */
    union {
        volatile uint32_t STEPDELAY14           ;
        volatile struct StepDelay STEPDELAY14_bit;
    };  // 0x0D0h

    /* SYS_TSCADCSS_STEPCONFIG15           register bit field */
    union {
        volatile uint32_t STEPCONFIG15          ;
        volatile struct StepConfig STEPCONFIG15_bit;
    };  // 0x0D4h

    /* SYS_TSCADCSS_STEPDELAY15            register bit field */
    union {
        volatile uint32_t STEPDELAY15           ;
        volatile struct StepDelay STEPDELAY15_bit;
    };  // 0x0D8h

    /* SYS_TSCADCSS_STEPCONFIG16           register bit field */
    union {
        volatile uint32_t STEPCONFIG16          ;
        volatile struct StepConfig STEPCONFIG16_bit;
    };  // 0x0DCh

    /* SYS_TSCADCSS_STEPDELAY16            register bit field */
    union {
        volatile uint32_t STEPDELAY16           ;
        volatile struct StepDelay STEPDELAY16_bit;
    };  // 0x0E0h

    /* SYS_TSCADCSS_FIFO0COUNT             register bit field */
    union {
        volatile uint32_t FIFO0COUNT            ;
        volatile struct {
            unsigned WORDS_IN_FIFO0         : 7;    // 0-6
            unsigned reserved7_31           : 25;   // 7-31
        } FIFO0COUNT_bit;
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

    uint32_t rsvdFC[1];        // 0x0FC - 0x100

    /* SYS_TSCADCSS_FIFO0DATA              register bit field */
    union {
        volatile struct FifoData FIFO0DATA[64]; // Ignore index as the port returns the oldest sample.
        //volatile struct {} FIFO0DATA_bit;
    };  // 0x100h

    /* SYS_TSCADCSS_FIFO1DATA              register bit field */
    union {
        volatile struct FifoData FIFO1DATA[64]; // Ignore index as the port returns the oldest sample.
        //volatile struct {} FIFO1DATA_bit;
    };  // 0x200h

} sysTscadcss;

#define TSCADCSS (*((volatile sysTscadcss*)0x44E0D000))

#define ADCPRCM (*((volatile uint32_t*)0x44E004BC))

#endif /* _SYS_TSCADCSS_H_ */
