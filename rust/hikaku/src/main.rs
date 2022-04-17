struct a_mystruct {
    a: i32,
    b: i64,
}

fn main() {
    let am = a_mystruct {a: 1231, b: 2512};
    println!("am.a {}\nam.b {}",am.a, am.b);
    std::io::stdin()
}
