/*
 * Copyright (C) 2017 Lore4 - MIT License.
 *
 * Example based on lab 5 example from TI which has:
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
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

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/poll.h>

#define MAX_BUFFER_SIZE		512
char readBuf[MAX_BUFFER_SIZE];

#define NUM_MESSAGES		4
#define DEVICE_NAME		"/dev/rpmsg_pru31"

int main(void)
{

    // Power ADC.
    int fdADC = open("/dev/uio/adc", O_RDONLY);

	struct pollfd pollfds[1];
	int i;
	int result = 0;
	unsigned long sampleValue = 0;
	unsigned long sampleChannel = 0;
	unsigned long sampleCount = 0;
	/* Open the rpmsg_pru character device file */
	pollfds[0].fd = open(DEVICE_NAME, O_RDWR);

	/*
	 * If the RPMsg channel doesn't exist yet the character device
	 * won't either.
	 * Make sure the PRU firmware is loaded and that the rpmsg_pru
	 * module is inserted.
	 */
	if (pollfds[0].fd < 0) {
		printf("Failed to open %s\n", DEVICE_NAME);
		return -1;
	}

	/* The RPMsg channel exists and the character device is opened */
	printf("Opened %s, sending %d messages\n\n", DEVICE_NAME, NUM_MESSAGES);

	for (i = 0; i < NUM_MESSAGES; i++) {
		/* Send 'hello world!' to the PRU through the RPMsg channel */
		result = write(pollfds[0].fd, "hello world!", 13);
		if (result > 0)
			printf("Message %d: Sent to PRU\n", i);

		/* Poll until we receive a message from the PRU and then print it */
		result = read(pollfds[0].fd, readBuf, MAX_BUFFER_SIZE);
		if (result > 0)
		{
		    // Retrieve number of samples sent.
		    unsigned int samplesNumber = readBuf[3];
		    samplesNumber = samplesNumber<<8;
		    samplesNumber = samplesNumber | readBuf[2];
		    samplesNumber = samplesNumber<<8;
		    samplesNumber = samplesNumber | readBuf[1];
		    samplesNumber = samplesNumber<<8;
		    samplesNumber = samplesNumber | readBuf[0];

		    // Extract samples from payload.
		    unsigned int sampleId;
		    printf("Message %d received from PRU: Samples # %d\n\n", i, samplesNumber);

		    for (sampleId = 0; sampleId < samplesNumber; sampleId++)
		    {
		        int payloadIndex = 4 + (sampleId * 8);

                // Conversion of message sent.
                sampleValue = readBuf[payloadIndex + 3];
                sampleValue = sampleValue<<8;
                sampleValue = sampleValue | readBuf[payloadIndex + 2];
                sampleValue = sampleValue<<8;
                sampleValue = sampleValue | readBuf[payloadIndex + 1];
                sampleValue = sampleValue<<8;
                sampleValue = sampleValue | readBuf[payloadIndex + 0];
                sampleChannel = readBuf[payloadIndex + 7];
                sampleChannel = sampleChannel<<8;
                sampleChannel = sampleChannel | readBuf[payloadIndex + 6];
                sampleChannel = sampleChannel<<8;
                sampleChannel = sampleChannel | readBuf[payloadIndex + 5];
                sampleChannel = sampleChannel<<8;
                sampleChannel = sampleChannel | readBuf[payloadIndex + 4];

                // Print.
                printf("Message %d received from PRU: Sample Id %d\n\n", i, sampleId);
                printf("Message %d received from PRU: Step ID %X\n\n", i, sampleChannel);

                // Print raw sample value.
                printf("Message %d received from PRU: value %d\n\n", i, sampleValue);

                // Print scaled sample value.
//                float sampledVoltage = ((float)sampleValue )* 1.8 / 4095;    // Scale sample.
//                printf("Message %d received from PRU: value %.3f\n\n", i, sampledVoltage);
		    }
		}
	}

	/* Received all the messages the example is complete */
	printf("Received %d messages, closing %s\n", NUM_MESSAGES, DEVICE_NAME);

	/* Close the rpmsg_pru character device file */
	close(pollfds[0].fd);

	// Power off adc.
	close(fdADC);

	return 0;
}

