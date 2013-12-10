 (*
  * AUTO-GENERATED FILE DO NOT EDIT
  * Generated from xentoollog.mli.in and _xtl_levels.mli.in
  *)

(*
 * Copyright (C) 2012      Citrix Ltd.
 * Author Ian Campbell <ian.campbell@citrix.com>
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
 *)

(* @@XTL_LEVELS@@ *)
(* AUTO-GENERATED FILE DO NOT EDIT *)
(* autogenerated by 
   genlevels.py _xtl_levels.mli.in _xtl_levels.ml.in _xtl_levels.inc
 *)

type level = 
	| Debug
	| Verbose
	| Detail
	| Progress
	| Info
	| Notice
	| Warn
	| Error
	| Critical

(* END OF AUTO-GENERATED CODE *)

val level_to_string : level -> string
val compare_level : level -> level -> int

type handle

(** call back arguments. See xentoollog.h for more info.
    vmessage:
      level: level as above
      errno: Some <errno> or None
      context: Some <string> or None
      message: The log message (already formatted)
    progress:
      context: Some <string> or None
      doing_what: string
      percent, done, total.
*)
type logger_cbs = {
	vmessage : level -> int option -> string option -> string -> unit;
	progress : string option -> string -> int -> int64 -> int64 -> unit;
	(*destroy : handle -> unit*)
}

external test: handle -> unit = "stub_xtl_test"

val create : string -> logger_cbs -> handle

