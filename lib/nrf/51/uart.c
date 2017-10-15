    /** @addtogroup uart_defines
 *
 * @brief <b>Access functions for the NRF51 UART </b>
 * @ingroup NRF51_defines
 * LGPL License Terms @ref lgpl_license
 * @author @htmlonly &copy; @endhtmlonly 2016
 * Maxim Sloyko <maxims@google.com>
 *
 */

/*
 * This file is part of the unicore-mx project.
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <unicore-mx/nrf/uart.h>
#include <unicore-mx/nrf/gpio.h>

/** @brief Enable the peripheral
 *
 * @param[in] uart uint32_t uart base
 */
void uart_enable(uint32_t uart)
{
    UART_ENABLE(uart) = UART_ENABLE_ENABLED;
}

/** @brief Disable the peripheral
 *
 * @param[in] uart uint32_t uart base
 */
void uart_disable(uint32_t uart)
{
    UART_ENABLE(uart) = UART_ENABLE_DISABLED;
}

/** @brief Configure UART parameters in single call
 *
 * @details Any pin number can be set to 0xff (or any number larger than UART_MAX_PIN)
 *  to disconnect that pin.
 *
 * @param[in] uart uint32_t uart base
 * @param[in] tx_pin uint8_t TX pin number
 * @param[in] rx_pin uint8_t RX pin number
 * @param[in] rts_pin uint8_t RTS pin number
 * @param[in] cts_pin uint8_t CTS pin number
 * @param[in] baud enum uart_baud baud rate
 * @param[in] enable_parity bool If true, enable parity bit
 */
void uart_configure(uint32_t uart,
        uint32_t tx_pin, uint32_t rx_pin, uint32_t rts_pin, uint32_t cts_pin,
        enum uart_baud br, bool enable_parity)
{
    UART_PSELTXD(uart) = UART_PSEL_VAL(GPIO2PIN(tx_pin));
    UART_PSELRXD(uart) = UART_PSEL_VAL(GPIO2PIN(rx_pin));
    UART_PSELRTS(uart) = UART_PSEL_VAL(GPIO2PIN(rts_pin));
    UART_PSELCTS(uart) = UART_PSEL_VAL(GPIO2PIN(cts_pin));

    uint32_t reg_config = enable_parity ? UART_CONFIG_PARITY : 0;
    if (rts_pin <= UART_MAX_PIN || cts_pin <= UART_MAX_PIN) {
        reg_config |= UART_CONFIG_HWFC;
    }

    UART_CONFIG(uart) = reg_config;
    UART_BAUDRATE(uart) = br;
}

void uart_set_pins(uint32_t uart, uint32_t rx, uint32_t tx)
{
    UART_PSELTXD(uart) = UART_PSEL_VAL(GPIO2PIN(tx));
    UART_PSELRXD(uart) = UART_PSEL_VAL(GPIO2PIN(rx));
}

void uart_set_baudrate(uint32_t uart, enum uart_baud br)
{
    UART_BAUDRATE(uart) = br;
}

void uart_set_databits(uint32_t uart, int bits)
{

}

void uart_set_stopbits(uint32_t uart, int bits)
{

}

void uart_set_parity(uint32_t uart, int parity)
{
}

void uart_set_flow_control(uint32_t uart, int flow)
{
}

#define __uart_send_byte_sync(uart, byte) do {\
    UART_TXD((uart)) = byte;\
    periph_wait_event(UART_EVENT_TXDRDY(uart));\
} while (0)

#define __uart_tx_start(uart) do {\
    periph_clear_event(UART_EVENT_TXDRDY((uart)));\
    periph_trigger_task(UART_TASK_STARTTX((uart)));\
} while (0)

#define __uart_tx_stop(uart) periph_trigger_task(UART_TASK_STOPTX((uart)))

void uart_send(uint32_t uart, uint16_t byte) {
    __uart_tx_start(uart);
    __uart_send_byte_sync(uart, byte);
    __uart_tx_stop(uart);
}

/** @brief Send buffer synchronously.
 *
 * @param[in] uart uint32_t uart base
 * @param[in] buffer const uint8_t* buffer to send
 * @param[in] len uint16_t length of the buffer
 */
void uart_send_buffer_blocking(uint32_t uart, const uint8_t *buffer, uint16_t len)
{
    __uart_tx_start(uart);
    for (; len; --len, ++buffer) {
        __uart_send_byte_sync(uart, *buffer);
    }
    __uart_tx_stop(uart);
}

/** @brief Send zero terminated string synchronously.
 *
 * @param[in] uart uint32_t uart base
 * @param[in] buffer const char* string to send
 */
void uart_send_string_blocking(uint32_t uart, const char *str)
{
    __uart_tx_start(uart);
    for (; *str; ++str) {
        __uart_send_byte_sync(uart, *str);
    }
    __uart_tx_stop(uart);
}

