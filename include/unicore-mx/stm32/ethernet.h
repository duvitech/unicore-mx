/* This provides unification of code over STM32F subfamilies */

/*
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

#if defined(STM32F1)
#       include <unicore-mx/ethernet/mac/stm32fxx7.h>
#elif defined(STM32F4)
#       include <unicore-mx/ethernet/mac/stm32fxx7.h>
#else
#       error "stm32 family not defined."
#endif

