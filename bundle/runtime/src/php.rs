#[allow(non_camel_case_types,non_snake_case,non_upper_case_globals,dead_code)]
mod zend {
    include!(concat!(env!("CARGO_MANIFEST_DIR"), "/zend-bindings.rs"));
}

use libc::{c_int, c_char};
use std::os::raw::c_void;
use std::mem::ManuallyDrop;

type JmpBuf = [libc::c_int; 49];

type ZendStreamFsizerT = extern "C" fn(handle: *mut libc::c_void) -> libc::size_t;
type ZendStreamReaderT = extern "C" fn(handle: *mut libc::c_void, buf: *mut libc::c_char, len: libc::size_t) -> libc::ssize_t;
type ZendStreamCloserT = extern "C" fn(handle: *mut libc::c_void);

#[repr(C)]
pub struct zend_stream {
    handle: *mut c_void,
    isatty: c_int,
    reader: Option<ZendStreamReaderT>,
    fsizer: Option<ZendStreamFsizerT>,
    closer: Option<ZendStreamCloserT>,
}

#[repr(C)]
pub union Handle {
    fp: *mut std::ffi::c_void,
    stream: ManuallyDrop<zend_stream>,
}

#[repr(C)]
pub struct zend_file_handle {
    handle: Handle,
    filename: *mut libc::c_char,
    opened_path: *mut libc::c_char,
    type_: u8,
    primary_script: bool,
    in_list: bool,
    buf: *mut libc::c_char,
    len: usize,
}

extern "C" {
    // Assuming these functions and types are defined in your FFI bindings
    pub(crate) fn php_embed_init(argc: c_int, argv: *mut *mut c_char);
    pub(crate) fn php_embed_shutdown();
    pub(crate) fn zend_stream_init_filename(file_handle: *mut zend_file_handle, filename: *const c_char);
    pub(crate) fn php_execute_script(file_handle: *mut zend_file_handle) -> c_int;
    pub(crate) fn php_printf(format: *const c_char, ...);

    pub(crate) fn sigsetjmp(env: *mut JmpBuf, savesigs: libc::c_int) -> libc::c_int;

    // Executor globals and jump buffer types
    pub(crate) static mut executor_globals: zend::_zend_executor_globals;
}