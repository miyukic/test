#![allow(non_snake_case)]
#![allow(unused_variables)]
#![allow(unused_imports)]
#![allow(dead_code)]

fn hoge<T>(h: &T) {
}

fn main() {
    let a = 3;
    let b: &i32 = &a;
    let c: &i32 = &a;
    //println!("a={}", &a);
    println!("b={}", &b);
    println!("c={}", &c);
    //hoge(&a);
}
