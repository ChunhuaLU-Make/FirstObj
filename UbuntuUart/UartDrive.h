#ifndef __UBUNTU_UART_H_
#define __UBUNTU_UART_H_

#define DRIVER_DESC		"WCH CH34x USB to serial adaptor driver"
#define DRIVER_AUTHOR	"<tech@wch.cn>"

#define CH34x_VENDOR_ID		0x1A86
#define CH340_PRODUCT_ID	0x7523
#define CH341_PRODUCT_ID	0x5523

#define CH34x_CLOSING_WAIT	(30 * HZ)

#define CH34x_BUF_SIZE		1024
#define CH34x_TMP_BUF_SIZE	1024

//Vendor define
#define VENDOR_WRITE_TYPE		0x40
#define VENDOR_READ_TYPE		0xC0

#define VENDOR_READ				0x95
#define VENDOR_WRITE			0x9A
#define VENDOR_SERIAL_INIT		0xA1
#define VENDOR_MODEM_OUT		0xA4
#define VENDOR_VERSION			0x5F

//For CMD 0xA4
#define UART_CTS		0x01
#define UART_DSR		0x02
#define UART_RING		0x04
#define UART_DCD		0x08
#define CONTROL_OUT		0x10
#define CONTROL_DTR		0x20
#define	CONTROL_RTS		0x40

//Uart state
#define UART_STATE			0x00
#define UART_OVERRUN_ERROR	0x01
#define UART_BREAK_ERROR	//no define
#define UART_PARITY_ERROR	0x02
#define UART_FRAME_ERROR	0x06
#define UART_RECV_ERROR		0x02
#define UART_STATE_TRANSIENT_MASK	0x07

//Port state
#define PORTA_STATE		0x01
#define PORTB_STATE		0x02
#define PORTC_STATE		0x03

//CH34x Baud Rate
#define CH34x_BAUDRATE_FACTOR	1532620800
#define CH34x_BAUDRATE_DIVMAX	3

//#define DEBUG_CH34x
#undef  DEBUG_CH34x

#ifdef DEBUG_CH34x
#define dbg_ch34x( format, arg... )		\
	printk( KERN_DEBUG "%d: " format "\n", __LINE__, ##arg )
#else
#define dbg_ch34x( format, arg... )		\
do{									\
	if(0)							\
		printk(KERN_DEBUG "%d: " format "\n", __LINE__, ##arg);	\
} while (0)
#endif

#ifdef DEBUG_CH34x
#define err_ch34x( format, arg... )		\
	printk(KERN_ERR KBUILD_MODNAME ": " format "\n", ##arg)
#else
#define err_ch34x( format, arg... )   \
do{								\
	if(0)						\
	printk( KERN_ERR KBUILD_MODNAME ": " format "\n", ##arg)\
}while(0)						
#endif

// For debug
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3,7,1))
static int debug = 1;
#endif

static DECLARE_WAIT_QUEUE_HEAD(wq);
static int wait_flag = 0;

struct ch34x_buf {
	unsigned int buf_size;
	char *buf_buf;
	char *buf_get;
	char *buf_put;
};

struct ch34x_private {
	spinlock_t	lock;	//access lock
	struct ch34x_buf	*buf;
	int	write_urb_in_use;
	unsigned baud_rate;
	wait_queue_head_t	delta_msr_wait;
	u8	line_control;
	u8	line_status;
	u8	termios_initialized;
};

static struct usb_device_id	id_table [] = {
	{ USB_DEVICE(CH34x_VENDOR_ID, CH340_PRODUCT_ID) },
	{ USB_DEVICE(CH34x_VENDOR_ID, CH341_PRODUCT_ID) },
	{ } //End
};
MODULE_DEVICE_TABLE( usb, id_table );

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3,5,2))
static struct usb_driver ch34x_driver = {
	.name		   = "ch34x",
	.probe		   = usb_serial_probe,
	.disconnect	   = usb_serial_disconnect,
	.id_table	   = id_table,
	.suspend	   = usb_serial_suspend,
	.resume		   = usb_serial_resume,
	.no_dynamic_id = 1,
	.supports_autosuspend = 1,
};
#endif



#endif

