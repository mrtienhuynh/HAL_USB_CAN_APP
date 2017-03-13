#ifndef USB_XXX
#define USB_XXX
//
//
//
//
//
//
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

//************************************************************************************************************************************
//   configurate pin of MCU
// 	 GPIO input/ output pin
//	 USB pin 
//   UART pin
//	 clocking of MCU 
//************************************************************************************************************************************
void USB_PinConfig (void);

// ***********************************************************************************************************************************
//	Initializes a USB buffer object to be used with a given USB controller and device or host class driver.
//	psBuffer points to a structure containing information on the buffer memory to be used and the
//	underlying device or host class driver whose data is to be buffered. This structure must
//	remain accessible for as long as the buffer is in use.
//************************************************************************************************************************************]
const tUSBBuffer *USBBufferInit(tUSBBuffer *psBuffer);

//************************************************************************************************************************************
// 	configurate  usb use for USB CDC (communication device class)
//	psCDCDevice points to a structure containing parameters customizing the operation of the CDC device.
//************************************************************************************************************************************
void USB_CDC_Config (tUSBDCDCDevice g_sCDCDevice);

//*****************************************************************************
//
// This function is called whenever serial data is received from the UART.
// It is passed the accumulated error flags from each character received in
// this interrupt and determines from them whether or not an interrupt
// notification to the host is required.
//
// If a notification is required and the control interrupt endpoint is idle,
// we send the notification immediately.  If the endpoint is not idle, we
// accumulate the errors in a global variable which will be checked on
// completion of the previous notification and used to send a second one
// if necessary.
//
//*****************************************************************************
static void
CheckForSerialStateChange(const tUSBDCDCDevice *psDevice, int32_t i32Errors);

//*****************************************************************************
//
// Interrupt handler for the UART which we are redirecting via USB.
//
//*****************************************************************************
void USBUARTIntHandler(void);

//*****************************************************************************
//
// Interrupt handler for the UART which we are redirecting via USB.
//
//*****************************************************************************
void
USBUARTIntHandler(void);

//*****************************************************************************
//
// Set the communication parameters to use on the UART.
// set databit, parti bit, stop bit,... use for UART transmit
// psLineCoding parameters to use on the UART.
//
//*****************************************************************************
static bool SetLineCoding(tLineCoding *psLineCoding);

//*****************************************************************************
//
// Get the communication parameters in use on the UART.
//
//*****************************************************************************
static void
GetLineCoding(tLineCoding *psLineCoding);

//*****************************************************************************
//
// This function sets or clears a break condition on the redirected UART RX
// line.  A break is started when the function is called with \e bSend set to
// \b true and persists until the function is called again with \e bSend set
// to \b false.
//
//*****************************************************************************
static void
SendBreak(bool bSend);

//*****************************************************************************
//
// Handles CDC driver notifications related to control and setup of the device.
//
// \param pvCBData is the client-supplied callback pointer for this channel.
// \param ui32Event identifies the event we are being notified about.
// \param ui32MsgValue is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the CDC driver to perform control-related
// operations on behalf of the USB host.  These functions include setting
// and querying the serial communication parameters, setting handshake line
// states and sending break conditions.
//
// \return The return value is event-specific.
//
//*****************************************************************************
uint32_tControlHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue, void *pvMsgData);

//*****************************************************************************
//
// Handles CDC driver notifications related to the transmit channel (data to
// the USB host).
//
// \param ui32CBData is the client-supplied callback pointer for this channel.
// \param ui32Event identifies the event we are being notified about.
// \param ui32MsgValue is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the CDC driver to notify us of any events
// related to operation of the transmit data channel (the IN channel carrying
// data to the USB host).
//
// \return The return value is event-specific.
//
//*****************************************************************************
uint32_t TxHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue,  void *pvMsgData);

 //*****************************************************************************
//
// Handles CDC driver notifications related to the receive channel (data from
// the USB host).
//
// \param ui32CBData is the client-supplied callback data value for this channel.
// \param ui32Event identifies the event we are being notified about.
// \param ui32MsgValue is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the CDC driver to notify us of any events
// related to operation of the receive data channel (the OUT channel carrying
// data from the USB host).
//
// \return The return value is event-specific.
//
//*****************************************************************************
uint32_t
RxHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue, void *pvMsgData);

//*****************************************************************************
//
// Read as many characters from the UART FIFO as we can and move them into
// the CDC transmit buffer.
//
// \return Returns UART error flags read during data reception.
//
//*****************************************************************************
static int32_t ReadUARTData(void);

//*****************************************************************************
//
// Take as many bytes from the transmit buffer as we have space for and move
// them into the USB UART's transmit FIFO.
//
//*****************************************************************************
static void
USBUARTPrimeTransmit(uint32_t ui32Base);
#endif //USB_XXX