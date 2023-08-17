#[allow(non_camel_case_types,non_snake_case,non_upper_case_globals,dead_code)]
mod zend {
    include!(concat!(env!("CARGO_MANIFEST_DIR"), "/zend-bindings.rs"));
}

extern crate libc;
use libc::{c_int, c_char};
use std::ffi::CString;

mod php;

fn main() {
    let args: Vec<CString> = std::env::args().map(|arg| CString::new(arg).unwrap()).collect();
    let mut c_args: Vec<*mut c_char> = args.iter().map(|arg| arg.as_ptr() as *mut c_char).collect();

    unsafe {
        php::php_embed_init(c_args.len() as c_int, c_args.as_mut_ptr());
        php::executor_globals.bailout = std::ptr::null_mut();

        let __orig_bailout = php::executor_globals.bailout;
        let mut __bailout: zend::sigjmp_buf = [0; 49]; // Initializing with zeroes
        php::executor_globals.bailout = &mut __bailout;

        if php::sigsetjmp(&mut __bailout, 0) == 0 {
            let mut file_handle_uninit: std::mem::MaybeUninit<php::zend_file_handle> = std::mem::MaybeUninit::uninit();
            let filename = CString::new("example.php").unwrap();
            let file_handle_ptr = file_handle_uninit.as_mut_ptr();

            php::zend_stream_init_filename(file_handle_ptr, filename.as_ptr());
            let mut file_handle: php::zend_file_handle = file_handle_uninit.assume_init();

            if php::php_execute_script(&mut file_handle) == -1 {
                let error_message = CString::new("Failed to execute PHP script.\n").unwrap(); // Added extra newline

                php::php_printf(error_message.as_ptr());
            }
        } else {
            php::executor_globals.bailout = __orig_bailout;
        }

        php::executor_globals.bailout = __orig_bailout;
        php::php_embed_shutdown();
    }
}