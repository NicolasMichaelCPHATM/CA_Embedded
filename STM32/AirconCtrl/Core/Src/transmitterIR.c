/*
 * transmitterIR.c
 *
 *  Created on: Jun 28, 2022
 *      Author: matias
 */

#include "transmitterIR.h"
#include <stdbool.h>
#include "StmGpio.h"
#include "main.h"
#include "USBprint.h"

static TIM_HandleTypeDef* timFreqCarrier = NULL;
static TIM_HandleTypeDef* timSignal = NULL;

static struct {
	bool isCommandIssued;
	bool isAddressSent;
	bool isCommReady;
} commandState = {false, false, false};

static union IRCommand {
    struct {
        uint32_t address;
        uint32_t tempData;
        uint32_t miscStates;
        uint32_t unknown;
    }; // struct used for altering data
    uint32_t command[4]; // command used for sending
} IRCommand= {.address = IR_ADDRESS, .tempData = TEMP_18, .miscStates = FAN_HIGH, .unknown = 0x20000};

static void sendCommand()
{
	static int sendBitIdx = 0;
	static int wordIdx = 0;

	if (!commandState.isAddressSent)
	{
		commandState.isAddressSent = true;
		TIM3->ARR = START_BIT_ARR;
		TIM3->CCR2 = START_BIT_CCR;
		return;
	}

	// End of message
	if (wordIdx == 3 && sendBitIdx == 17)
	{
		turnOffLED();

		commandState.isCommandIssued = false;
		commandState.isAddressSent = false;
		commandState.isCommReady = false;

		wordIdx = 0;
		sendBitIdx = 0;

		TIM3->ARR = START_BIT_ARR;
		TIM3->CCR2 = 0;
		return;
	}

	// After overload of counter the new PWM settings will be set
	// that codes for a logical 1 and 0 respectively.
	if (IRCommand.command[wordIdx] & (1 << (31-sendBitIdx)))
	{
		TIM3->ARR = HIGH_BIT_ARR;
		TIM3->CCR2 = HIGH_BIT_CCR;
	}
	else
	{
		TIM3->ARR = LOW_BIT_ARR;
		TIM3->CCR2 = LOW_BIT_CCR;
	}

	sendBitIdx++;
	if (sendBitIdx % 32 == 0)
	{
		sendBitIdx = 0;
		wordIdx++;
	}
}

void pwmGPIO()
{
	if (!commandState.isCommReady)
		return;

	if (TIM3->CNT < TIM3->CCR2)
	{
		turnOnLED();
	}
	else
	{
		turnOffLED();
	}
}

static uint32_t tempCodes[8] = {TEMP_18, TEMP_19, TEMP_20, TEMP_21, TEMP_22, TEMP_23, TEMP_24, TEMP_25};
static uint32_t crcCodes[8] = {CRC18, CRC19, CRC20, CRC21, CRC22, CRC23, CRC24, CRC25};
void updateTemperatureIR(int temp)
{
	if (temp < 18 || temp > 25)
		return;

	IRCommand.tempData = tempCodes[temp-18];
	IRCommand.unknown = crcCodes[temp-18];

	commandState.isCommandIssued = true;
}

void turnOnLED()
{
	HAL_TIM_PWM_Start(timFreqCarrier, TIM_CHANNEL_1);
}

void turnOffLED()
{
	HAL_TIM_PWM_Stop(timFreqCarrier, TIM_CHANNEL_1);
}
// Callback: timer has rolled over
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if (!commandState.isCommandIssued)
		return;

	if (commandState.isAddressSent && !commandState.isCommReady)
	{
		commandState.isCommReady = true;
		return;
	}

    if (htim == timSignal)
    {
        sendCommand();
    }
}


void initTransmitterIR(TIM_HandleTypeDef *timFreqCarrier_, TIM_HandleTypeDef *timSignal_)
{
	HAL_TIM_PWM_Start_IT(timSignal_, TIM_CHANNEL_2);
	timSignal = timSignal_;
	timFreqCarrier = timFreqCarrier_;
}

