#include "pch.h"
#include "board_overrides.h"

Gpio getCommsLedPin() {
	return Gpio::C13;
}

Gpio getRunningLedPin() {
	return Gpio::C14;
}

Gpio getWarningLedPin() {
	return Gpio::C15;
}

// board-specific configuration setup
static void customBoardDefaultConfiguration() {
//	engineConfiguration->injectionPins[0] = Gpio::A0;
//	engineConfiguration->injectionPins[1] = Gpio::A1;
//	engineConfiguration->injectionPins[2] = Gpio::A2;
//	engineConfiguration->injectionPins[3] = Gpio::A3;
	//engineConfiguration->injectionPins[0] = Gpio::B0;
	//engineConfiguration->injectionPins[0] = Gpio::B0;
//	engineConfiguration->ignitionPins[0] = Gpio::B0;
//	engineConfiguration->ignitionPins[1] = Gpio::B1;
//	engineConfiguration->ignitionPins[2] = Gpio::B4;
//	engineConfiguration->ignitionPins[3] = Gpio::B5;
//	engineConfiguration->ignitionPins[4] = Gpio::B6;
//	engineConfiguration->ignitionPins[5] = Gpio::B7;

	engineConfiguration->triggerInputPins[0] = Gpio::B10;
	engineConfiguration->triggerInputPins[1] = Gpio::B11;

	engineConfiguration->map.sensor.hwChannel = EFI_ADC_13;
	engineConfiguration->clt.adcChannel = EFI_ADC_11;
	engineConfiguration->iat.adcChannel = EFI_ADC_12;
}

static void setupVbatt() {
	// 5.6k high side/10k low side = 1.56 ratio divider
	engineConfiguration->analogInputDividerCoefficient = 1.56f;

	// 10k high side/ 1k low side
	engineConfiguration->vbattDividerCoeff = (10 + 1) / 1;

	// Battery sense on PC0
	engineConfiguration->vbattAdcChannel = EFI_ADC_10;

	engineConfiguration->adcVcc = 3.3f;
}

void setBoardConfigOverrides() {
	setupVbatt();
//	setEtbConfig();
//	setStepperConfig();

	engineConfiguration->clt.config.bias_resistor = 2490;
	engineConfiguration->iat.config.bias_resistor = 2490;

	//CAN 1 bus overwrites
	engineConfiguration->canRxPin = Gpio::B9;
	engineConfiguration->canTxPin = Gpio::B8;
}

static Gpio OUTPUTS[] = {
	Gpio::A0,
	Gpio::A1,
	Gpio::A2,
	Gpio::A3,
	Gpio::A9,
	Gpio::A10,
	Gpio::B0,
	Gpio::B1,
	Gpio::B4,
	Gpio::B5,
	Gpio::B6,
	Gpio::B7,
	Gpio::B12,
};

int getBoardMetaOutputsCount() {
	    return efi::size(OUTPUTS);
}

Gpio* getBoardMetaOutputs() {
	    return OUTPUTS;
}

void setup_custom_board_overrides() {
    custom_board_DefaultConfiguration = customBoardDefaultConfiguration;
}
