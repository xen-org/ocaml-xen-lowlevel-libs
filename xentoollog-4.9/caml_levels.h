/* AUTO-GENERATED FILE DO NOT EDIT */
/* autogenerated by 
   genlevels.py _xtl_levels.mli.in _xtl_levels.ml.in _xtl_levels.inc
 */

static value Val_level(xentoollog_level c_level)
{
	switch (c_level) {
	case XTL_NONE: /* Not a real value */
		caml_raise_sys_error(caml_copy_string("Val_level XTL_NONE"));
		break;
	case XTL_DEBUG:
		return Val_int(0);
	case XTL_VERBOSE:
		return Val_int(1);
	case XTL_DETAIL:
		return Val_int(2);
	case XTL_PROGRESS:
		return Val_int(3);
	case XTL_INFO:
		return Val_int(4);
	case XTL_NOTICE:
		return Val_int(5);
	case XTL_WARN:
		return Val_int(6);
	case XTL_ERROR:
		return Val_int(7);
	case XTL_CRITICAL:
		return Val_int(8);
	case XTL_NUM_LEVELS: /* Not a real value! */
			caml_raise_sys_error(
				caml_copy_string("Val_level XTL_NUM_LEVELS"));
	#if 0 /* Let the compiler catch this */
		default:
			caml_raise_sys_error(caml_copy_string("Val_level Unknown"));
			break;
	#endif
		}
		abort();
	}
	
