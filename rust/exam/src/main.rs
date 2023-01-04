#![allow(non_snake_case)]
#![allow(unused_variables)]
#![allow(unused_imports)]
#![allow(dead_code)]

use std::rc::Rc;

#[derive(Copy, Clone)]
struct Hoge {
    x: f64,
    y: f64
}


fn main() {
    let hoge = Hoge {
        x: 1.0,
        y: 2.0
    };
    let hoge2 = hoge.clone();
    println!("{}", hoge.x);


}
