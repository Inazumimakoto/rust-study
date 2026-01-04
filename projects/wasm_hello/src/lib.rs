use wasm_bindgen::prelude::*;

// JavaScript から呼べる関数！
#[wasm_bindgen]
pub fn add(a: i32, b: i32) -> i32 {
    a + b
}

#[wasm_bindgen]
pub fn greet(name: &str) -> String {
    format!("Hello, {}! From Rust WASM! 🦀", name)
}
