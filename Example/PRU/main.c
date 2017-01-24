/*
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
#define FROM_ARM_HOST			19

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
 * ADC defines.
 */
#define ADC_BASE 0x44e0d000

#define CONTROL 0x0040
#define SPEED   0x004c
#define STEP1   0x0064
#define DELAY1  0x0068
#define STATUS  0x0044
#define STEPCONFIG  0x0054
#define FIFO0COUNT  0x00e4

#define ADC_FIFO0DATA   (ADC_BASE + 0x0100)


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

			    // Retrieve revision value. Default value = 0x47300001.
			    uint32_t temp2 = TSCADCSS.REVISION;

			    // Check default value.
			    if (temp2 == 0x47300001)
			    {

			        // Configure continous sampling on channel 0.
			        TSCADCSS.STEPCONFIG1_bit.continuous = 1;
			        TSCADCSS.STEPCONFIG1_bit.inp_sel = 1;
			        TSCADCSS.STEPCONFIG1_bit.inm_sel = 9;

			        // Enable sampling on step1 (i.e. channel 0 with continous sampling).
			        TSCADCSS.STEPENABLE = 2;

			        // Enable sampling.
			        TSCADCSS.CTRL = 3;

			        // Wait one sample.
			        if (TSCADCSS.ADCSTAT_bit.FSM_BUSY != 0)
			        {
                        while (TSCADCSS.ADCSTAT_bit.FSM_BUSY != 0)
                        {
                            // wait.
                        }
			        }
			        // Read data of first element in FIFO.
			        if (TSCADCSS.FIFO0COUNT_bit.WORDS_IN_FIFO0 != 0)
			        {
			            temp2 = TSCADCSS.FIFO0DATA[TSCADCSS.FIFO0COUNT_bit.WORDS_IN_FIFO0-1].REGISTER_bit.ADCDATA;
			        }
			        else
			        {
			            temp2 = TSCADCSS.FIFO0DATA[0].REGISTER_bit.ADCDATA;
			        }

			        // Send sample to ARM.
                    payload[0] = temp2 & 0x000000FF;
                    payload[1] = (temp2>>8) & 0x000000FF;
                    payload[2] = (temp2>>16) & 0x000000FF;
                    payload[3] = (temp2>>24) & 0x000000FF;

                    pru_rpmsg_send(&transport, dst, src, payload, len);

                    // Disable sampling.
                    TSCADCSS.STEPENABLE = 0;

                    if (TSCADCSS.ADCSTAT_bit.FSM_BUSY != 0)
                    {
                        while (TSCADCSS.ADCSTAT_bit.FSM_BUSY != 0)
                        {
                            ;
                        }
                    }

                    TSCADCSS.CTRL = 0;
			    }
			}
		}
	}
}
