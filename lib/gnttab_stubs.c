/*
 * Copyright (C) 2012-2013 Citrix Inc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; version 2.1 only. with the special
 * exception on linking described in file LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

/* For PROT_READ | PROT_WRITE */
#include <sys/mman.h>

#define CAML_NAME_SPACE
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/signals.h>
#include <caml/fail.h>
#include <caml/callback.h>
#include <caml/bigarray.h>

#include <xenctrl.h>

#define _G(__g) ((xc_gnttab *)(__g))

CAMLprim value stub_xc_gnttab_open(void)
{
	CAMLparam0();
	xc_gnttab *xgh;
	xgh = xc_gnttab_open(NULL, 0);
	if (xgh == NULL)
		caml_failwith("Failed to open interface");
	CAMLreturn((value)xgh);
}

CAMLprim value stub_xc_gnttab_close(value xgh)
{
	CAMLparam1(xgh);

	xc_gnttab_close(_G(xgh));

	CAMLreturn(Val_unit);
}

int caml_perms_to_c_perms(int perm)
{
	switch (perm) {
	case 0:
		return PROT_NONE;
	case 1:
		return PROT_READ;
	case 2:
		return PROT_WRITE;
  case 3:
    return PROT_READ | PROT_WRITE;
	}

  return -1;
}

#define XC_GNTTAB_BIGARRAY (CAML_BA_UINT8 | CAML_BA_C_LAYOUT | CAML_BA_EXTERNAL)

CAMLprim value stub_xc_gnttab_map_grant_ref(
	value xgh,
	value domid,
	value reference,
	value perms
	)
{
	CAMLparam4(xgh, domid, reference, perms);
	CAMLlocal1(contents);

	void *map =
    xc_gnttab_map_grant_ref(_G(xgh), Int_val(domid), Int_val(reference),
                            caml_perms_to_c_perms(Int_val(perms)));

	if(map==NULL) {
		caml_failwith("Failed to map grant ref");
	}

	contents = caml_ba_alloc_dims(XC_GNTTAB_BIGARRAY, 1,
		map, 1 << XC_PAGE_SHIFT);
	CAMLreturn(contents);
}

CAMLprim value stub_xc_gnttab_map_grant_refs(
	value xgh,
	value array,
	value perms)
{
	CAMLparam3(xgh, array, perms);
	CAMLlocal3(domid, reference, contents);
	int count = Wosize_val(array) / 2;
	uint32_t domids[count];
	uint32_t refs[count];
	int i;

	for (i = 0; i < count; i++){
		domids[i] = Int_val(Field(array, i * 2 + 0));
		refs[i] = Int_val(Field(array, i * 2 + 1));
	}
	void *map =
    xc_gnttab_map_grant_refs(_G(xgh),
                             count,
                             domids,
                             refs,
                             caml_perms_to_c_perms(Int_val(perms))
	);

	if(map==NULL) {
		caml_failwith("Failed to map grant ref");
	}

	contents = caml_ba_alloc_dims(XC_GNTTAB_BIGARRAY, 1,
		map, count << XC_PAGE_SHIFT);
	CAMLreturn(contents);
}

CAMLprim value stub_xc_gnttab_unmap(value xgh, value array) 
{
	CAMLparam2(xgh, array);

	int size = Caml_ba_array_val(array)->dim[0];
	int pages = size >> XC_PAGE_SHIFT;
	int result = xc_gnttab_munmap(_G(xgh), Caml_ba_data_val(array), pages);
	if(result!=0) {
		caml_failwith("Failed to unmap grant");
	}

	CAMLreturn(Val_unit);
}
