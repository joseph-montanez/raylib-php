extern crate bindgen;

use std::env;
use std::path::PathBuf;
use std::process::Command;

fn main() {
    let manifest_dir = env::var("CARGO_MANIFEST_DIR").unwrap();

    // Get the path to the PHP include directory
    // let include_path = PathBuf::from(&manifest_dir).join("../../external/php-src/include");
    // let php_include_path = include_path.display();
    let php_include_path = "/usr/local/include";
    let zend_include_path = "/usr/local/include/php";

    // Generate the bindings
    let bindings = bindgen::Builder::default()
        .clang_arg(format!("-I{}/main", zend_include_path))
        .clang_arg(format!("-I{}/Zend", zend_include_path))
        .clang_arg(format!("-I{}/TSRM", zend_include_path))
        .clang_arg(format!("-I{}", zend_include_path))
        .header(format!("{}/php/main/php.h", php_include_path))
        .clang_arg("-DHAVE_SIGSETJMP")
        .allowlist_type("_zend_executor_globals")
        .generate()
        .expect("Failed to generate bindings");

    // Write the bindings to the src/bindings.rs file
    let out_path = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("zend-bindings.rs"))
        .expect("Couldn't write bindings!");


    let lib_path = PathBuf::from(&manifest_dir).join("../../external/php-src/libs");

    println!("cargo:rustc-link-search=native={}", lib_path.display());
    println!("cargo:rustc-link-lib=static=php");

    // Depending on PHP's dependencies, you may need to link additional libraries.
    println!("cargo:rustc-link-lib=dylib=xml2");
    println!("cargo:rustc-link-lib=dylib=sqlite3");
    println!("cargo:rustc-link-lib=dylib=resolv");

    // Getting libiconv path from Homebrew
    let libiconv_prefix = Command::new("brew")
        .arg("--prefix")
        .arg("libiconv")
        .output()
        .expect("Failed to get libiconv prefix")
        .stdout;
    let libiconv_prefix = String::from_utf8(libiconv_prefix).expect("Failed to convert libiconv prefix to string");
    let libiconv_path = libiconv_prefix.trim().to_owned() + "/lib";

    println!("cargo:rustc-link-search=native={}", libiconv_path);
    println!("cargo:rustc-link-lib=dylib=iconv");
}