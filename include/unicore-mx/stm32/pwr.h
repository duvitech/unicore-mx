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

#include <unicore-mx/cm3/common.h>
#include <unicore-mx/stm32/memorymap.h>

#if defined(STM32F0)
#       include <unicore-mx/stm32/f0/pwr.h>
#elif defined(STM32F1)
#       include <unicore-mx/stm32/f1/pwr.h>
#elif defined(STM32F2)
#       include <unicore-mx/stm32/f2/pwr.h>
#elif defined(STM32F3)
#       include <unicore-mx/stm32/f3/pwr.h>
#elif defined(STM32F4)
#       include <unicore-mx/stm32/f4/pwr.h>
#elif defined(STM32F7)
#       include <unicore-mx/stm32/f7/pwr.h>
#elif defined(STM32L1)
#       include <unicore-mx/stm32/l1/pwr.h>
#elif defined(STM32L0)
#       include <unicore-mx/stm32/l0/pwr.h>
#elif defined(STM32L4)
#       include <unicore-mx/stm32/l4/pwr.h>
#else
#       error "stm32 family not defined."
#endif

