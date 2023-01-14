#![allow(non_snake_case)]
#![allow(unused_variables)]
#![allow(unused_imports)]
#![allow(dead_code)]

use std::fmt::*;

fn hoge<T>(h: &T) where T: Display {
    println!("hoge {}", h);
}

fn main() {
    let mut a = 3;
    let b: &mut i32 = &mut a;
    *b = 5;
    hoge(b);
    println!("b={}", b);
    println!("a={}", a);
    //hoge(&a);
}
