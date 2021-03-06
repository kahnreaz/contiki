/*
 * Copyright (c) 2014, Konrad-Felix Krentz.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         Helpers for accessing external flash memory.
 * \author
 *         Konrad Krentz <konrad.krentz@gmail.com>
 */

#include "net/llsec/coresec/apkes-flash.h"
#include "contiki-conf.h"
#include "dev/xmem.h"
#include "net/llsec/coresec/neighbor.h"

static unsigned short keying_material_offset;

/*---------------------------------------------------------------------------*/
void
apkes_flash_erase_keying_material(void)
{
  xmem_erase(XMEM_ERASE_UNIT_SIZE, APKES_FLASH_KEYING_MATERIAL_OFFSET);
  keying_material_offset = 0;
}
/*---------------------------------------------------------------------------*/
void
apkes_flash_append_keying_material(void *keying_material, uint16_t len)
{
  xmem_pwrite(keying_material, len, APKES_FLASH_KEYING_MATERIAL_OFFSET + keying_material_offset);
  keying_material_offset += len;
}
/*---------------------------------------------------------------------------*/
void
apkes_flash_restore_keying_material(void *keying_material, uint16_t len, uint16_t offset)
{
  xmem_pread(keying_material, len, APKES_FLASH_KEYING_MATERIAL_OFFSET + offset);
}
/*---------------------------------------------------------------------------*/
