#include "Display.h"
#include "main.h"
#include "stm32f1xx_hal_spi.h"
#include "stm32f1xx_hal_gpio.h"
extern SPI_HandleTypeDef hspi1;
enum epd_regs : uint8_t
{
	OTP_MEMORY = 0xA1,
	IMAGE_DATA = 0x10
};

enum epd_otp_memory : uint16_t
{
	CHECK_CODE             = 0x1500,
	LAYOUT_REV             = 0x1501,
	COG_TYPE               = 0x1502,
	VENDOR                 = 0x1503,
	WAVEFORM_REV           = 0x1504,
	COLOR                  = 0x150B,
	COG_INITIAL_DATA_START = 0x1510,
	COG_INITIAL_DATA_END   = 0x152F
};

constexpr size_t chipId_size = 2;
uint8_t chipID[chipId_size] = { 0 };
constexpr size_t dat_size = 49;
uint8_t dat[dat_size] = { 0 };

static volatile int test = 0;



static void delay()
{
	
	
	for (int i = 0; i < 1000; i++)
	{
		test++;
	}
}

static void delay_long()
{
	
	for (int i = 0; i < 10; i++)
	{
		delay();
	}
	
}

static void error_state()
{
	while (true)
	{
		
	
	}
}

void wait_for_busy(uint8_t val)
{

	while (val != HAL_GPIO_ReadPin(EPD_NBUSY_GPIO_Port, EPD_NBUSY_Pin)) ;
	
}
void display_spi_write(uint8_t addr, uint8_t* buf, size_t len)
{
	
	// D/C = 0
	HAL_GPIO_WritePin(EPD_DC_GPIO_Port, EPD_DC_Pin, GPIO_PIN_RESET);
	
	// CS = 0
	//HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
	
	// Register Index
	HAL_SPI_Transmit(&hspi1, &addr, 1, -1);
	
	// CS = 1
	//HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
	
	// D/C = 1
	HAL_GPIO_WritePin(EPD_DC_GPIO_Port, EPD_DC_Pin, GPIO_PIN_SET);
	delay();
	
	// SDIN_D1 to Hi-z
	
	// Bytes need to be read one at a time with cs going high between each byte
	for (int byte = 0; byte < len; byte++)
	{
	
		// CS = 0
		// Done as part of HAL_SPI_Recieve
	
		//HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
		
		// SCLK_D0 = 0
	
		// SCLK_D0 = 1
	
		
		// Read bit (MSB First)
		HAL_SPI_Transmit(&hspi1, buf + byte, 1, -1);

		// Make sure a complete byte was read
	
		// SCLK_D0 = 0
	
		// CS = 1
		//HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
		
		delay();
	}
	
	// Make sure data read is complete
	
}

void display_spi_read_byte(uint8_t addr, uint8_t offset, uint8_t& val)
{
	// D/C = 0
	HAL_GPIO_WritePin(EPD_DC_GPIO_Port, EPD_DC_Pin, GPIO_PIN_RESET);
	
	// CS = 0
	//HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
	
	// Register Index
	HAL_SPI_Transmit(&hspi1, &addr, 1, -1);
	
	// CS = 1
	//HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
	
	// D/C = 1
	HAL_GPIO_WritePin(EPD_DC_GPIO_Port, EPD_DC_Pin, GPIO_PIN_SET);
	delay();
	
	// SDIN_D1 to Hi-z
	
	// Bytes need to be read one at a time with cs going high between each byte
	for (int byte = 0; byte < offset; byte++)
	{
	
		// CS = 0
		// Done as part of HAL_SPI_Recieve
	
		//HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
		
		// SCLK_D0 = 0
	
		// SCLK_D0 = 1
	
		
		// Read bit (MSB First)
		HAL_SPI_Receive(&hspi1, &val, 1, -1);
	
		// Make sure a complete byte was read
	
		// SCLK_D0 = 0
	
		// CS = 1
		//HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
		
		delay();
	}
}

void display_spi_read(uint8_t addr, uint8_t* buf, size_t len)
{
	// D/C = 0
	HAL_GPIO_WritePin(EPD_DC_GPIO_Port, EPD_DC_Pin, GPIO_PIN_RESET);
	
	// CS = 0
	//HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
	
	// Register Index
	HAL_SPI_Transmit(&hspi1, &addr, 1, -1);
	
	// CS = 1
	//HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
	
	// D/C = 1
	HAL_GPIO_WritePin(EPD_DC_GPIO_Port, EPD_DC_Pin, GPIO_PIN_SET);
	delay();
	
	// SDIN_D1 to Hi-z
	
	// Bytes need to be read one at a time with cs going high between each byte
	for (int byte = 0; byte < len; byte++)
	{
	
		// CS = 0
		// Done as part of HAL_SPI_Recieve
	
		//HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
		
		// SCLK_D0 = 0
	
		// SCLK_D0 = 1
	
		
		// Read bit (MSB First)
		HAL_SPI_Receive(&hspi1, buf + byte, 1, -1);
	
		// Make sure a complete byte was read
	
		// SCLK_D0 = 0
	
		// CS = 1
		//HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
		
		delay();
	}
	
	// Make sure data read is complete
}


void display_soft_reset()
{
	uint8_t buffer[1] = { 0x0E };
	
	display_spi_write(0x00, buffer, 1);
}

// step 2
void power_cog_driver()
{
	// Turn on VCC
	
	// RES = 1 & delay 10ms
	HAL_GPIO_WritePin(EPD_NRESET_GPIO_Port, EPD_NRESET_Pin, GPIO_PIN_SET);
	delay_long();
	
	// RES = 0 & delay 20ms
	HAL_GPIO_WritePin(EPD_NRESET_GPIO_Port, EPD_NRESET_Pin, GPIO_PIN_RESET);
	delay_long();
	
	// RES = 1 & delay 40ms
	HAL_GPIO_WritePin(EPD_NRESET_GPIO_Port, EPD_NRESET_Pin, GPIO_PIN_SET);
	delay_long();
	
	display_soft_reset();
	
	// Wait until busy goes high
	wait_for_busy(1);
}


int get_temperature()
{
	return 65;
}

void display_fast_update()
{
	uint8_t buffer[2] = { 0 };
	
	// Input temperature SPI(0xE5, TSSET+0x40)
	buffer[0] = get_temperature() + 0x40;
	display_spi_write(0xE5, &buffer[0], 1);
	
	// Active Temperature SPI(0xE0, 0x02)
	buffer[0] = 0x02;
	display_spi_write(0xE0, &buffer[0], 1);
	
	// Read OTP SPI Read(0xA1, dummy, dat[0] ... dat[47]). This is the same as reading OTP 0x1500-0x152F
	display_spi_read(0xA2, dat, dat_size);
	
	// Panel Settings SPI(0x00, PSR[0] | 0x10, PSR[1] | 0x02)
	uint16_t psr0_addr = 0;
	uint16_t psr1_addr = 0;
	if (dat[1] == 0xA5)
	{
		psr0_addr = 0xB1B;
		psr1_addr = 0xB1C;
	}
	else
	{
		psr0_addr = 0x171B;
		psr1_addr = 0x171C;
	}
	
	// read psr 0
	uint8_t psr0_val = 0;
	uint8_t psr1_val = 0;
	display_spi_read_byte(0xA2, psr0_addr, psr0_val);
	display_spi_read_byte(0xA2, psr1_addr, psr1_val);
	
	buffer[0] = psr0_val | 0x10;
	buffer[1] = psr1_val | 0x02;
	display_spi_write(0x00, buffer, 2);
	
	// Vcom and data interval setting SPI(0x50, CDI)
	buffer[0] = 0x07;
	display_spi_write(0x50, buffer, 1);
}

// step 4
void initialize_cog()
{
	display_fast_update();
}

// First byte of dat is dummy data
constexpr unsigned dat_offset = 1;
void _initialize_cog()
{
	uint8_t buffer[4] = { 0 };
	
	// Read chip ID
	// SPI Read(0x70, chipID[0], chipID[1])
	display_spi_read(0x70, chipID, chipId_size);
	
	if (!(chipID[0] == 0 && chipID[1] == 8))
	{
		error_state();
	}
	// SPI Write (I think?) (0xA4, 0x15, 0x00, 0x01)
	buffer[0] = 0x15;
	buffer[1] = 0x00;
	buffer[2] = 0x01;
	display_spi_write(0xA4, buffer, 3);
	
	// Wait for busy to go high
	wait_for_busy(1);
	
	// Read OTP SPI Read(0xA1, dummy, dat[0] ... dat[47]). This is the same as reading OTP 0x1500-0x152F
	display_spi_read(0xA1, dat, dat_size);
	
	// RES = 0
	
	// RES = 1
	display_reset();
	
	// Wait for busy to go high
	wait_for_busy(1);
	
	// SPI(0x01, dat[16]). PWR
	display_spi_write(0x01, &dat[16 + dat_offset], 1);
		
	// SPI(0x00, dat[17], dat[18]). PSR
	display_spi_write(0x00, &dat[17 + dat_offset], 2);
	
	// SPI(0x03, dat[30], dat[31], dat[32]). PFS
	display_spi_write(0x03, &dat[30 + dat_offset], 3);
	
	// SPI(0x06, dat[23] ... dat[29]). BTST
	display_spi_write(0x06, &dat[23 + dat_offset], 7);
	
	// SPI(0x50, dat[39]). CDI
	display_spi_write(0x50, &dat[39 + dat_offset], 1);
	
	// SPI(0x60, dat[40], dat[41]). TCON
	display_spi_write(0x60, &dat[40 + dat_offset], 2);
	
	// SPI(0x61, dat[19], ... dat[22]) TRES
	display_spi_write(0x61, &dat[19 + dat_offset], 4);
	
	// SPI(0xE7, dat[33])
	display_spi_write(0xE7, &dat[33 + dat_offset], 1);
	
	// SPI(0xE3, dat[42])
	display_spi_write(0xE3, &dat[42 + dat_offset], 1);
	
	// SPI(0x4D, dat[43])
	display_spi_write(0x4D, &dat[43 + dat_offset], 1);
	
	// SPI(0xB4, dat[44])
	display_spi_write(0xB4, &dat[44 + dat_offset], 1);
	
	// SPI(0xB5, dat[45])
	display_spi_write(0xB5, &dat[45 + dat_offset], 1);
	
	// SPI(0xE9, 0x01)
	buffer[0] = 0x01;
	display_spi_write(0xE9, &buffer[0], 1);
	
	// SPI(0x30, 0x08)
	buffer[0] = 0x08;
	display_spi_write(0x30, &buffer[0], 1);
	
}

constexpr unsigned pixels_per_byte = 8;
constexpr unsigned bytes_per_display = (display_height * display_width) / pixels_per_byte;
uint8_t display_buf_1[bytes_per_display] = { 1 };
uint8_t display_buf_2[bytes_per_display] = { 0 };

uint8_t * new_buf = display_buf_1;
uint8_t * old_buf = display_buf_2;

// Step 4
void send_image()
{

	// Fast update scheme
	display_spi_write(0x10, new_buf, bytes_per_display);
	display_spi_write(0x13, old_buf, bytes_per_display);
	
	if (new_buf == display_buf_1)
	{
		new_buf = display_buf_2;
		old_buf = display_buf_1;
	}
	else
	{
		new_buf = display_buf_1;
		old_buf = display_buf_2;
	}
	
}

// Steps 6-9
void update_display()
{
	uint8_t buffer[4] = { 0 };
	
	// Step 6: Power on DC/DC converter
	// SPI(0x04). Power on command
	display_spi_write(0x04, &buffer[0], 1);
	
	// Step 7: Wait
	// Wait for busy high
	wait_for_busy(1);
	
	// Step 8: Tell the display to refresh
	// SPI(0x12, 0x00). Display refresh
	buffer[0] = 0;
	display_spi_write(0x12, &buffer[0], 1);
	
	// Step 9: Wait
	// Wait for busy high
	wait_for_busy(1);

}

// Step 6
void power_off()
{
	// This is described in the manual, but not something I need to do right now.
}




void display_reset()
{
	// RES = 1 & delay 10ms
	HAL_GPIO_WritePin(EPD_NRESET_GPIO_Port, EPD_NRESET_Pin, GPIO_PIN_SET);
	delay_long();
	
	// RES = 0 & delay 20ms
	HAL_GPIO_WritePin(EPD_NRESET_GPIO_Port, EPD_NRESET_Pin, GPIO_PIN_RESET);
	delay_long();
	
	// RES = 1 & delay 40ms
	HAL_GPIO_WritePin(EPD_NRESET_GPIO_Port, EPD_NRESET_Pin, GPIO_PIN_SET);
	delay_long();
	
	// Soft Reset
	display_soft_reset();
	
	// Wait until busy goes high
	wait_for_busy(1);
}
void write_buf_raw(int x, int y, color c)
{
	
}
void write_buf(int x, int y, color c)
{
	int pixel = (x*display_height + y);
	int index = pixel / 8;
	int offset = (pixel % 8);
	
	offset = 7 - offset;
	uint8_t mask = ~(0x01 << offset);
	
	int byte = new_buf[index];
	byte &= mask;
	byte |= (c << offset);
	
	new_buf[index] = byte;
	
}

void invert_buf(int x, int y)
{
	int pixel = (x*display_height + y);
	int index = pixel / 8;
	int offset = (pixel % 8);
	
	offset = 7 - offset;
	uint8_t mask = (0x01 << offset);
	
	int byte = new_buf[index];
	byte ^= mask;
	
	new_buf[index] = byte;
}




void send_temperature_to_cog(int temp)
{
	// TODO
}

void do_display()
{
	NVIC_SetPriority(SPI1_IRQn, 3);
	NVIC_EnableIRQ(SPI1_IRQn);
	
	// Step 1: Get the temperature
	int temp = get_temperature();
	
	// Step 2: Power on Tcon (COG)
	power_cog_driver();
	
	// Step 3: Set temperature to COG
	send_temperature_to_cog(temp);
	
	// Step 4: Initialize COG
	initialize_cog();
	
}

void refresh_display()
{
	// Step 5: Send Image
	send_image();
	
	// Steps 6-9
	update_display();
}

void clear_screen()
{
	int index = 0;
	for (int x = 0; x < display_width; x++)
	{
		for (int y = 0; y < display_height; y+=2)
		{
			index = (x* display_height + y) / 8;
			old_buf[index] = 0;
			//write_buf(x, y, WHITE);
			// write_buf(x, y+1, BLACK);
		}
	}
}