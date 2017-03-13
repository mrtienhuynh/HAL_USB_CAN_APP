#ifndef HAL_XXX
#define HAL_XXX

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_uart.h"
#include "inc/hw_sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/usb.h"
#include "driverlib/rom.h"
#include "grlib/grlib.h"
#include "usblib/usblib.h"
#include "usblib/usbcdc.h"
#include "usblib/usb-ids.h"
#include "usblib/device/usbdevice.h"
#include "usblib/device/usbdcdc.h"
#include "utils/ustdlib.h"
#include "drivers/cfal96x64x16.h"
#include "usb_serial_structs.h"


// **************************************************************************************
//
// set the clocking of device 
// 
//  parameter ui32Config is the required configuration of the device clocking.
//
//
//**************************************************************************************
void HAL_SysCtlClockSet (uint32_t ui32Config);

//******************************************************************************************************

//Configures pin(s) for use as GPIO inputs.
//ui32Por t is the base address of the GPIO port
//ui8Pins is the bit-packed representation of the pin(s).

//******************************************************************************************************
void HALL_GPIOPinTypeGPIOInput(uint32_t ui32Port, uint8_t ui8Pins);

//******************************************************************************************************

//Configures pin(s) for use as GPIO inputs.
//ui32Por t is the base address of the GPIO port.
//ui8Pins is the bit-packed representation of the pin(s).

//******************************************************************************************************
void HALL_GPIOPinTypeGPIOutput(uint32_t ui32Port, uint8_t ui8Pins);


//******************************************************************************************************

//Reads the values present of the specified pin(s)
//ui32Por t is the base address of the GPIO port.
//ui8Pins is the bit-packed representation of the pin(s)

//******************************************************************************************************
int32_t HALL_GPIOPinRead(uint32_t ui32Port, uint8_t ui8Pins);

//******************************************************************************************************
//Writes a value to the specified pin(s).
//ui32Por t is the base address of the GPIO port.
//ui8Pins is the bit-packed representation of the pin(s).
//ui8Val is the value to write to the pin(s).

//******************************************************************************************************
void HAL_GPIOPinWrite (uint32_t ui32Port, uint8_t ui8Pins, uint8_t ui8Val);
//******************************************************************************************************

//Configures pin(s) for use as a CAN device.
//ui32Por t is the base address of the GPIO port.
//ui8Pins is the bit-packed representation of the pin(s)

//******************************************************************************************************
void HALL_GPIOPinTypeCAN(uint32_t ui32Port, uint8_t ui8Pins);

//******************************************************************************************************

//Configures the alternate function of a GPIO pin.
//ui32PinConfig is the pin configuration value, specified as only one of the GPIO_P??_??? values.

//******************************************************************************************************
void HALLL_GPIOPinConfigure(uint32_t ui32PinConfig);


#endif // HAL_XXX