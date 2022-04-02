enum IpAddrKind {
    V4,
    V6,
}

fn sub() {
    let four = IpAddrKind::V4;
    println!("Hello Sub!!");
}

fn main() {
    sub();
}
