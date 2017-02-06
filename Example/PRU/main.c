/*
 * Copyright (C) 2017 Lore4 - MIT License.
 *
 * Example based on lab 5 example from TI which has:
 * Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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

#include <stdint.h>
#include <stdio.h>
#include <pru_cfg.h>
#include <pru_intc.h>
#include <rsc_types.h>
#include <pru_rpmsg.h>
#include "resource_table_1.h"
#include "sys_tscadcss.h"

volatile register uint32_t __R31;

/* Host-1 Interrupt sets bit 31 in register R31 */
#define HOST_INT			((uint32_t) 1 << 31)	

/* The PRU-ICSS system events used for RPMsg are defined in the Linux device tree
 * PRU0 uses system event 16 (To ARM) and 17 (From ARM)
 * PRU1 uses system event 18 (To ARM) and 19 (From ARM)
 */
#define TO_ARM_HOST			18	
#define FROM_ARM_HOST	    19

/*
 * Using the name 'rpmsg-client-sample' will probe the RPMsg sample driver
 * found at linux-x.y.z/samples/rpmsg/rpmsg_client_sample.c
 *
 * Using the name 'rpmsg-pru' will probe the rpmsg_pru driver found
 * at linux-x.y.z/drivers/rpmsg/rpmsg_pru.c
 */
//#define CHAN_NAME			"rpmsg-client-sample"
#define CHAN_NAME			"rpmsg-pru"

#define CHAN_DESC			"Channel 31"
#define CHAN_PORT			31

/*
 * Used to make sure the Linux drivers are ready for RPMsg communication
 * Found at linux-x.y.z/include/uapi/linux/virtio_config.h
 */
#define VIRTIO_CONFIG_S_DRIVER_OK	4

uint8_t payload[RPMSG_BUF_SIZE];

/*
 * main.c
 */
void main(void)
{
	struct pru_rpmsg_transport transport;
	uint16_t src, dst, len;
	volatile uint8_t *status;

	/* Allow OCP master port access by the PRU so the PRU can read external memories */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	/* Clear the status of the PRU-ICSS system event that the ARM will use to 'kick' us */
	CT_INTC.SICR_bit.STS_CLR_IDX = FROM_ARM_HOST;

	/* Make sure the Linux drivers are ready for RPMsg communication */
	status = &resourceTable.rpmsg_vdev.status;
	while (!(*status & VIRTIO_CONFIG_S_DRIVER_OK));

	/* Initialize the RPMsg transport structure */
	pru_rpmsg_init(&transport, &resourceTable.rpmsg_vring0, &resourceTable.rpmsg_vring1, TO_ARM_HOST, FROM_ARM_HOST);

	/* Create the RPMsg channel between the PRU and ARM user space using the transport structure. */
	while (pru_rpmsg_channel(RPMSG_NS_CREATE, &transport, CHAN_NAME, CHAN_DESC, CHAN_PORT) != PRU_RPMSG_SUCCESS);

	while (1) {
		/* Check bit 30 of register R31 to see if the ARM has kicked us */
		if (__R31 & HOST_INT) {
			/* Clear the event status */
			CT_INTC.SICR_bit.STS_CLR_IDX = FROM_ARM_HOST;

			/* Receive all available messages, multiple messages can be sent per kick */
			while (pru_rpmsg_receive(&transport, &src, &dst, payload, &len) == PRU_RPMSG_SUCCESS) {
				/* Echo the message back to the same address from which we just received */

			    /////////////////////////////////////////
			    //  Init ADC
			    /////////////////////////////////////////

			    // Fifo elements counter.
                uint32_t fifoCount = 0;
                // Channel Id container.
                uint32_t stepId = TSCADCSS.REVISION; // Retrieve revision value. Default value = 0x47300001.
                // Define sample container.
                uint32_t channelSample = 0;
                // Enable Channel ID and Write on stepconfigs.
                TSCADCSS.CTRL = 6;

                TSCADCSS.ADC_CLKDIV = 1999;     // Divide default ADC frequency by 2000 (i.e. 1999 + 1).
                                                // Note: at high frequencies samples may be incorrect.

                // Enable ADC Steps.
                TSCADCSS.STEPCONFIG1_bit.inp_sel = 0;
                TSCADCSS.STEPCONFIG2_bit.inp_sel = 1;
                TSCADCSS.STEPCONFIG3_bit.inp_sel = 2;
                TSCADCSS.STEPCONFIG4_bit.inp_sel = 3;
                TSCADCSS.STEPCONFIG5_bit.inp_sel = 4;
                TSCADCSS.STEPCONFIG6_bit.inp_sel = 5;
                TSCADCSS.STEPCONFIG7_bit.inp_sel = 6;
                TSCADCSS.STEPCONFIG8_bit.inp_sel = 7;

                TSCADCSS.STEPCONFIG1_bit.inm_sel = 0;
                TSCADCSS.STEPCONFIG2_bit.inm_sel = 0;
                TSCADCSS.STEPCONFIG3_bit.inm_sel = 0;
                TSCADCSS.STEPCONFIG4_bit.inm_sel = 0;
                TSCADCSS.STEPCONFIG5_bit.inm_sel = 0;
                TSCADCSS.STEPCONFIG6_bit.inm_sel = 0;
                TSCADCSS.STEPCONFIG7_bit.inm_sel = 0;
                TSCADCSS.STEPCONFIG8_bit.inm_sel = 0;

                TSCADCSS.STEPCONFIG1_bit.en_diff = 0;
                TSCADCSS.STEPCONFIG2_bit.en_diff = 0;
                TSCADCSS.STEPCONFIG3_bit.en_diff = 0;
                TSCADCSS.STEPCONFIG4_bit.en_diff = 0;
                TSCADCSS.STEPCONFIG5_bit.en_diff = 0;
                TSCADCSS.STEPCONFIG6_bit.en_diff = 0;
                TSCADCSS.STEPCONFIG7_bit.en_diff = 0;
                TSCADCSS.STEPCONFIG8_bit.en_diff = 0;

                TSCADCSS.STEPCONFIG1_bit.averaging = 4;
                TSCADCSS.STEPCONFIG2_bit.averaging = 4;
                TSCADCSS.STEPCONFIG3_bit.averaging = 4;
                TSCADCSS.STEPCONFIG4_bit.averaging = 4;
                TSCADCSS.STEPCONFIG5_bit.averaging = 4;
                TSCADCSS.STEPCONFIG6_bit.averaging = 4;
                TSCADCSS.STEPCONFIG7_bit.averaging = 4;
                TSCADCSS.STEPCONFIG8_bit.averaging = 4;

                // Configure step1 delay.
                TSCADCSS.STEPDELAY1 = 0;
//                TSCADCSS.STEPDELAY2 = 0;
//                TSCADCSS.STEPDELAY3 = 0;
//                TSCADCSS.STEPDELAY4 = 0;
//                TSCADCSS.STEPDELAY5 = 0;
//                TSCADCSS.STEPDELAY6 = 0;
//                TSCADCSS.STEPDELAY7 = 0;
//                TSCADCSS.STEPDELAY8 = 0;

                // Enable sampling on step1 (i.e. channel 0 sampling).
                TSCADCSS.STEPENABLE_bit.STEP1 = 1;
//                TSCADCSS.STEPENABLE_bit.STEP2 = 1;
//                TSCADCSS.STEPENABLE_bit.STEP3 = 1;
//                TSCADCSS.STEPENABLE_bit.STEP4 = 1;
//                TSCADCSS.STEPENABLE_bit.STEP5 = 1;
//                TSCADCSS.STEPENABLE_bit.STEP6 = 1;
//                TSCADCSS.STEPENABLE_bit.STEP7 = 1;
//                TSCADCSS.STEPENABLE_bit.STEP8 = 1;

                // Enable sampling.
                TSCADCSS.CTRL = 7;

                // Prepare message index.
                uint8_t payloadOffset = 4;   // Get current position of payload in message.

			    // Check default value.
			    if (stepId == 0x47300001)
			    {
                    struct FifoData currentFifoElement;
                    uint32_t sampleId = 0;

                    __delay_cycles(20000000);  // wait (10000 * 200Mhz).

			        while (fifoCount < 1)
			        {
			            fifoCount = TSCADCSS.FIFO0COUNT;
			        }

			        // Update message header with the number of samples.
			        payload[0] = (fifoCount) & 0x000000FF;    // Update payload with # of samples.
                    payload[1] = (fifoCount>>8) & 0x000000FF;
                    payload[2] = (fifoCount>>16) & 0x000000FF;
                    payload[3] = (fifoCount>>24) & 0x000000FF;

			        for (sampleId = 0; sampleId < fifoCount; sampleId++)
			        {
                        // Retrieve data.
                        currentFifoElement = TSCADCSS.FIFO0DATA[0];
                        stepId = currentFifoElement.REGISTER_bit.ADCCHNLID + 1;      // Retrieve sample step ID.

//                        channelSample = currentFifoElement.REGISTER_bit.ADCDATA;    // Retrieve sample value (easy way).
                        channelSample = currentFifoElement.REGISTER;                // Retrieve sample value (hard way).
                        channelSample &= 0x00000fff;

                        // Prepare sample for ARM (hardway).
                        uint32_t commodoChannelSample = channelSample;
                        payload[payloadOffset] = channelSample & 0x000000FF;
                        commodoChannelSample = commodoChannelSample >> 8;
                        payload[payloadOffset + 1] = commodoChannelSample & 0x000000FF;
                        commodoChannelSample = commodoChannelSample >> 8;
                        payload[payloadOffset + 2] = commodoChannelSample & 0x000000FF;
                        commodoChannelSample = commodoChannelSample >> 8;
                        payload[payloadOffset + 3] = commodoChannelSample & 0x000000FF;

                        payload[payloadOffset + 4] = stepId & 0x000000FF;
                        payload[payloadOffset + 5] = (stepId>>8) & 0x000000FF;
                        payload[payloadOffset + 6] = (stepId>>16) & 0x000000FF;
                        payload[payloadOffset + 7] = (stepId>>24) & 0x000000FF;

                        payloadOffset += 8;
                    }

			    }

                pru_rpmsg_send(&transport, dst, src, payload, payloadOffset );// len);

                /////////////////////////////////////////
                //  Release ADC
                /////////////////////////////////////////
                // Disable sampling.
                TSCADCSS.STEPENABLE = 0;

                // Empty fifo.
                while (TSCADCSS.FIFO0COUNT_bit.WORDS_IN_FIFO0 != 0)//(TSCADCSS.ADCSTAT_bit.FSM_BUSY != 0)
                {
                    channelSample = TSCADCSS.FIFO0DATA[TSCADCSS.FIFO0COUNT_bit.WORDS_IN_FIFO0-1].REGISTER_bit.ADCDATA;
                }

                // Wait until ADC's FSM has finished, otherwise there are issues with ADC.
                if (TSCADCSS.ADCSTAT_bit.FSM_BUSY != 0)
                {
                    while (TSCADCSS.ADCSTAT_bit.FSM_BUSY != 0)
                    {
                        ;
                    }
                }

                TSCADCSS.CTRL = 6;
			}
		}
	}
}
