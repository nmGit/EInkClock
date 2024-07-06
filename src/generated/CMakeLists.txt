target_compile_definitions(EInkClock PUBLIC STM32F103xB)

set(STM32_CUBE_HAL_DRIVER_FOLDER ${CMAKE_CURRENT_LIST_DIR}/eink_clock_2/Drivers/STM32F1xx_HAL_Driver)
set(CMSIS_FOLDER ${CMAKE_CURRENT_LIST_DIR}/eink_clock_2/Drivers/CMSIS)

target_include_directories(EInkClock PUBLIC eink_clock_2/Core/Inc)

target_sources(EInkClock PUBLIC
#	eink_clock_1/Core/main.c
	${CMAKE_CURRENT_LIST_DIR}/eink_clock_2/Core/Src/stm32f1xx_hal_msp.c
	${CMAKE_CURRENT_LIST_DIR}/eink_clock_2/Core/Src/stm32f1xx_it.c
	${CMAKE_CURRENT_LIST_DIR}/eink_clock_2/Core/Src/syscalls.c
	${CMAKE_CURRENT_LIST_DIR}/eink_clock_2/Core/Src/sysmem.c
	${CMAKE_CURRENT_LIST_DIR}/eink_clock_2/Core/Src/system_stm32f1xx.c
	${CMAKE_CURRENT_LIST_DIR}/eink_clock_2/startup_stm32f103xb.s

	${STM32_CUBE_HAL_DRIVER_FOLDER}/Src/stm32f1xx_hal.c
	${STM32_CUBE_HAL_DRIVER_FOLDER}/Src/stm32f1xx_hal_cortex.c
	${STM32_CUBE_HAL_DRIVER_FOLDER}/Src/stm32f1xx_hal_dma.c
	${STM32_CUBE_HAL_DRIVER_FOLDER}/Src/stm32f1xx_hal_exti.c
	${STM32_CUBE_HAL_DRIVER_FOLDER}/Src/stm32f1xx_hal_flash.c
	${STM32_CUBE_HAL_DRIVER_FOLDER}/Src/stm32f1xx_hal_flash_ex.c
	${STM32_CUBE_HAL_DRIVER_FOLDER}/Src/stm32f1xx_hal_gpio.c
	${STM32_CUBE_HAL_DRIVER_FOLDER}/Src/stm32f1xx_hal_gpio_ex.c
	${STM32_CUBE_HAL_DRIVER_FOLDER}/Src/stm32f1xx_hal_pwr.c
	${STM32_CUBE_HAL_DRIVER_FOLDER}/Src/stm32f1xx_hal_rcc.c
	${STM32_CUBE_HAL_DRIVER_FOLDER}/Src/stm32f1xx_hal_rcc_ex.c
	${STM32_CUBE_HAL_DRIVER_FOLDER}/Src/stm32f1xx_hal_rtc.c
	${STM32_CUBE_HAL_DRIVER_FOLDER}/Src/stm32f1xx_hal_rtc_ex.c
	${STM32_CUBE_HAL_DRIVER_FOLDER}/Src/stm32f1xx_hal_spi.c
	${STM32_CUBE_HAL_DRIVER_FOLDER}/Src/stm32f1xx_hal_tim.c
	${STM32_CUBE_HAL_DRIVER_FOLDER}/Src/stm32f1xx_hal_tim_ex.c
	${STM32_CUBE_HAL_DRIVER_FOLDER}/Src/stm32f1xx_hal_pcd.c
	${STM32_CUBE_HAL_DRIVER_FOLDER}/Src/stm32f1xx_hal_pcd_ex.c
	${STM32_CUBE_HAL_DRIVER_FOLDER}/Src/stm32f1xx_ll_usb.c
)

target_include_directories(EInkClock PUBLIC
	${STM32_CUBE_HAL_DRIVER_FOLDER}/Inc/
	${CMSIS_FOLDER}/Include
	${CMSIS_FOLDER}/Device/ST/STM32F1xx/Include
)